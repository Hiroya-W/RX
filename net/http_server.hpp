#pragma once
//=====================================================================//
/*!	@file
	@brief	HTTP サーバー・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include <functional>
#include "common/sdc_io.hpp"
#include "common/fixed_string.hpp"
#include "graphics/color.hpp"
#include "socket.hpp"

#define HTTP_DEBUG

extern "C" {
	time_t get_time(void);
};

namespace net {

	typedef graphics::color_t color;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  http_server class テンプレート
		@param[in]	SDC	ＳＤカードファイル操作インスタンス
		@param[in]	MAX_LINK	登録リンクの最大数
		@param[in]	MAX_SIZE	文字列、一時バッファの最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETH, class SDC, uint32_t MAX_LINK = 16, uint32_t MAX_SIZE = 4096>
	class http_server {
	public:
		typedef utils::line_manage<2048, 20> LINE_MAN;
		typedef utils::basic_format<socket_string<MAX_SIZE> > http_format;

		typedef std::function< void () > http_task_type;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アライメント属性
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class align {
			left,	///< 左寄せ
			center,	///< 中央
			right	///< 右寄せ
		};


	private:
		// デバッグ以外で出力を無効にする
#ifdef HTTP_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		SDC&			sdc_;

		ETH&			eth_;

		socket<ETH>		sock_;

		LINE_MAN		line_man_;

		time_t			last_modified_;
		char			server_name_[32];
		uint32_t		timeout_;
		uint32_t		max_;

		uint32_t		count_;
		uint32_t		disconnect_loop_;

		struct link_t {
			const char*	path_;
			const char* title_;

			const char* file_;	// link file path.

			http_task_type	task_;
			bool			cgi_;
			link_t() : path_(nullptr), title_(nullptr), file_(nullptr),
				task_(), cgi_(false) { }
		};
		uint32_t		link_num_;
		link_t			link_[MAX_LINK];

		char			post_body_[2048];

		enum class task : uint8_t {
			none,
			begin_http,
			wait_http,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		task		task_;

		color			back_color_;
		color			fore_color_;


		static void get_path_(const char* src, char* dst) {
			int n = 0;
			char ch;
			while((ch = src[n]) != 0) {
				if(ch == ' ') break;
				dst[n] = ch;
				++n;
			}
			dst[n] = 0;
		}


		void render_404page(const char* path)
		{
			exec_link(path);
		}


		int set_link_(const char* path)
		{
			if(link_num_ >= MAX_LINK) {
				debug_format("HTTP Server: set link empty '%s'\n") % path;
				return -1;
			}
			// 既に登録があるか検査
			for(int i = 0; i < static_cast<int>(link_num_); ++i) {
				if(std::strcmp(link_[i].path_, path) == 0) {
					return i;
				}
			}

			int n = link_num_;
			++link_num_;
			return n;
		}


		int find_link_(const char* path, bool cgi)
		{
			for(int i = 0; i < static_cast<int>(link_num_); ++i) {
				if(std::strcmp(link_[i].path_, path) == 0 && link_[i].cgi_ == cgi) {
					return i;
				}
			}
			return -1;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		http_server(ETH& eth, SDC& sdc) : sdc_(sdc), eth_(eth), sock_(eth), line_man_(0x0a),
			last_modified_(0), server_name_{ 0 }, timeout_(15), max_(60),
			count_(0), disconnect_loop_(0),
			link_num_(0), link_{ },
			task_(task::none),
			back_color_(255, 255, 255), fore_color_(0, 0, 0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief POST ボディーを取得
			@return POST ボディー
		*/
		//-----------------------------------------------------------------//
		const char* get_post_body() const { return post_body_; }


		//-----------------------------------------------------------------//
		/*!
			@brief クライアントからの応答を解析して終端（空行）があったら行数を返す
			@return 行数
		*/
		//-----------------------------------------------------------------//
		int analize_request(const char* tmp, int len)
		{
			for(int i = 0; i < len; ++i) {
				char ch = tmp[i];
				if(ch == 0 || ch == 0x0d) continue;
				if(!line_man_.add(ch)) {
					debug_format("HTTP Server: line_man:- memory over\n");
					return -1;
				}
			}
			if(len > 0) {
				line_man_.set_term();
				if(!line_man_.empty()) {
					for(uint32_t i = 0; i < line_man_.size(); ++i) {
						const char* p = line_man_[i];
						if(p[0] == 0) {  // 応答の終端！（空行）
							return i;
						}
					}
				}
			}
			return -1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  スタート
			@param[in]	server_name	サーバー名
		*/
		//-----------------------------------------------------------------//
		void start(const char* server_name)
		{
			std::strncpy(server_name_, server_name, sizeof(server_name_) - 1);

			last_modified_ = get_time();

			http_format::chaout().set_fd(-1);

			count_ = 0;
			disconnect_loop_ = 0;

			task_ = task::begin_http;

			debug_format("HTTP Server: format capacity: %d\n") % http_format::chaout().at_str().capacity();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  応答メッセージの生成
			@param[in]	status	ステータスコード
			@param[in]	length	コンテンツ長（バイト）
			@param[in]	keep	セッション・キープの場合「true」
			@return 「Content-Length: 」後の位置
		*/
		//-----------------------------------------------------------------//
		uint32_t make_info(int status, int length, bool keep = false)
		{
			uint32_t lp = 0;
			http_format("HTTP/1.1 %d OK\n") % status;

			time_t t = get_time();
			struct tm *m = gmtime(&t);
			// Sun, 11 Jan 2004 16:06:23 GMT
			http_format("Date: %s, %02d %s %4d %02d:%02d:%02d GMT\n")
				% get_wday(m->tm_wday)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
			http_format("Server: %s\n") % server_name_;

			http_format("Last-Modified: %s,%02d %s %4d %02d:%02d:%02d GMT\n")
				% get_wday(m->tm_wday)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
			http_format("Accept_ranges: bytes\n");
			if(length >= 0) {
				http_format("Content-Length: %d\n") % length;
			} else {
				http_format("Content-Length: ");
				lp = http_format::chaout().size();
				// % http_format::chaout().at_str().capacity();
				http_format("     \n");
			}
			if(keep) {
				http_format("Keep-Alive: timeout=%u,max=%u\n") % timeout_ % max_;
			}
			http_format("Connection: %s\n") % (keep == true ? "keep-alive" : "close");
			http_format("Content-Type: text/html\n\n");
			return lp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンテンツ・ヘッドの生成
			@param[in]	title	コンテンツのタイトル
		*/
		//-----------------------------------------------------------------//
		void make_head(const char* title)
		{
			http_format("<head>\n");
			http_format("<title>%s %s</title>\n") % server_name_ % title;
			http_format("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
			http_format("<meta http-equiv=\"Pragma\" content=\"no-cache\">\n");
			http_format("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">\n");
			http_format("<meta http-equiv=\"Expires\" content=\"0\">\n");
			http_format("</head>\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リンクの実行
			@param[in]	path	ページのパス
			@param[in]	cgi		CGI ページの場合「true」
			@return 有効なパスなら「true」
		*/
		//-----------------------------------------------------------------//
		bool exec_link(const char* path, bool cgi = false)
		{
			if(std::strcmp(path, "/favicon.ico") == 0) {
				make_info(404, -1, false);
				http_format::chaout().flush();  // 最終的な書き込み
				return true;
			}

			int idx = find_link_(path, cgi);
			if(idx < 0) return false;

			link_t& t = link_[idx];

			uint32_t clp = 0;
			uint32_t org = 0;
			if(!cgi) {
				http_format::chaout().clear();

				clp = make_info(200, -1, true);
				org = http_format::chaout().size();
				http_format("<!DOCTYPE HTML>\n");
				http_format("<html>\n");

				make_head(t.title_);
			}

			if(t.task_) {
				t.task_();
			}

			if(cgi) {
				return true;
			}

			http_format("</html>\n");
			uint32_t end = http_format::chaout().size();

			debug_format("HTTP Server: body size: %d\n") % (end - org);

			char tmp[5 + 1];  // 数字５文字＋終端
			utils::sformat("%5d", tmp, sizeof(tmp)) % (end - org);
			strncpy(&http_format::chaout().at_str()[clp], tmp, 5); // 数字部のみコピー

///			debug_format("HTTP Server: body: -----\n%s\n-----\n") % http_format::chaout().at_str().c_str();

			http_format::chaout().flush();  // 最終的な書き込み

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  URL エンコードとパース
			@param[in]	pos		データの行位置
		*/
		//-----------------------------------------------------------------//
		void parse_cgi(int pos)
		{
			int len = 0;
			for(int i = 0; i < static_cast<int>(line_man_.size()); ++i) {
				const char* p = line_man_[i];
				static const char* key = { "Content-Length: " };
				if(strncmp(p, key, strlen(key)) == 0) {
					utils::input("%d", p + strlen(key)) % len;
					break;
				}
			}

			int lines = static_cast<int>(line_man_.size());
			++pos;
			post_body_[0] = 0;
			if(pos >= lines) {
				debug_format("CGI No Body\n");
			} else {
//				utils::format("CGI param (URL enocde): '%s'\n") % line_man_[pos];
				utils::str::url_encode_to_str(line_man_[pos], post_body_);
//				debug_format("CGI param (str): '%s'\n") % post_body_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リンク登録全クリア
		*/
		//-----------------------------------------------------------------//
		void clear_link() { link_num_ = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  リンクの登録（タスク）
			@param[in]	path	ページ・パス
			@param[in]	title	ページ・タイトル
			@param[in]	task	レンダリング・タスク
			@return ページ・登録したら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_link(const char* path, const char*title, http_task_type task)
		{
			int idx = set_link_(path);
			if(idx < 0) return false;

			link_[idx].path_  = path;
			link_[idx].title_ = title;
			link_[idx].file_  = nullptr;
			link_[idx].task_  = task;
			link_[idx].cgi_   = false;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CGI の登録
			@param[in]	path	ページ・パス
			@param[in]	title	ページ・タイトル
			@param[in]	task	レンダリング・タスク
			@return ページ・登録したら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_cgi(const char* path, const char*title, http_task_type task)
		{
			int idx = set_link_(path);
			if(idx < 0) return false;

			link_[idx].path_  = path;
			link_[idx].title_ = title;
			link_[idx].file_  = nullptr;
			link_[idx].task_  = task;
			link_[idx].cgi_   = true;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファイルの登録
			@param[in]	path	ページ・パス
			@param[in]	title	ページ・タイトル
			@param[in]	file	ファイル・パス
			@return ページ・登録したら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_file(const char* path, const char*title, const char* file)
		{
			int idx = set_link_(path);
			if(idx < 0) return false;

			link_[idx].path_  = path;
			link_[idx].title_ = title;
			link_[idx].file_  = file;
			link_[idx].task_  = nullptr;
			link_[idx].cgi_   = false;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ファイル送信
			@param[in]	path	ファイル・パス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool send_file(const char* path)
		{
			FILE* fp = fopen(path, "rb");
			if(fp == nullptr) {
				return false;
			}
			uint32_t fsz = sdc_.size(path);

			http_format::chaout().clear();
			http_format("HTTP/1.1 200 OK\n");
			http_format("Content-Type: ");
			const char* ext = strrchr(path, '.');
			if(ext != nullptr) {
				++ext;
				if(strcmp(ext, "png") == 0 || strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
					http_format("image/%s\n") % ext;
				} else {
					http_format("text/%s\n") % ext;
				}
			} else {
				http_format("text/plain\n");
			}
			http_format("Content-Length: %u\n") % fsz;
			http_format("Connection: close\n\n");
			http_format::chaout().flush();				
			uint8_t tmp[512];
			uint32_t total = 0;
			uint32_t len;
			while((len = fread(tmp, 1, sizeof(tmp), fp)) == sizeof(tmp)) {
				sock_.write(tmp, sizeof(tmp));
				total += len;
			}
			if(len > 0) {
				sock_.write(tmp, len);
				total += len;
			}
			fclose(fp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	http_port	HTTP ポート番号（通常８０番）
		*/
		//-----------------------------------------------------------------//
		void service(uint16_t http_port = 80)
		{
			sock_.service();

			switch(task_) {

			case task::begin_http:
				if(!sock_.open(http_port)) {
					debug_format("HTTP Socket open error\n");
					break;
				}
				debug_format("HTTP Start Server: '%s' port(%d), desc(%d)\n")
					% sock_.get_src_adrs().c_str()
					% static_cast<int>(sock_.get_src_port())
					% sock_.get_desc();
				task_ = task::wait_http;
				break;

			case task::wait_http:
				if(sock_.connected()) {
					debug_format("HTTP Server: New connected, form: %s\n") % sock_.get_dst_adrs().c_str();
					++count_;
					line_man_.clear();
					http_format::chaout().set_fd(sock_.get_desc());
					task_ = task::main_loop;
				}
				break;

			case task::main_loop:
				if(sock_.connected()) {
					char tmp[2048];  // 大きな POST データに備えた大きさ
					int len = sock_.recv(tmp, sizeof(tmp));
					if(len == 0) break;
					auto pos = analize_request(tmp, len);
					if(pos > 0) {
						tmp[len] = 0;
///						debug_format("HTTP Server: client -----\n%s-----\n") % tmp;
						char path[256];
						path[0] = 0;
						if(!line_man_.empty()) {
							const char* t = line_man_[0];
							if(strncmp(t, "GET ", 4) == 0) {
								get_path_(t + 4, path);
								debug_format("HTTP Server: GET '%s'\n") % path;

								bool find = exec_link(path, false);
								if(!find) {
									debug_format("HTTP Server: can't find GET: '%s'\n") % path;
									make_info(404, -1, false);
									http_format::chaout().flush();
								}

							} else if(strncmp(t, "POST ", 5) == 0) {
								get_path_(t + 5, path);
								debug_format("HTTP Server: POST '%s'\n") % path;
								parse_cgi(pos);
								bool find = exec_link(path, true);
								if(!find) {
									debug_format("HTTP Server: can't find POST: '%s'\n") % path;
									make_info(404, -1, false);
									http_format::chaout().flush();
								}

							} else {
								debug_format("HTTP Server: request fail command '%s'\n") % t;
							}
						} else {
							debug_format("HTTP Server: request fail section.\n");
						}

						task_ = task::disconnect_delay;
						disconnect_loop_ = 5;
					}
				} else {
					task_ = task::disconnect_delay;
					disconnect_loop_ = 5;
				}
				break;

			case task::disconnect_delay:
				if(disconnect_loop_ > 0) {
					--disconnect_loop_;
				} else {
					sock_.close();
					http_format::chaout().set_fd(-1);
					task_ = task::disconnect;
				}
				break;

			case task::disconnect:
			default:
				debug_format("HTTP Server: disconnected\n");
				task_ = task::begin_http;
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バック・カラーの設定
			@param[in]	r	赤
			@param[in]	g	緑
			@param[in]	b	青
		*/
		//-----------------------------------------------------------------//
		void set_back_color(uint8_t r, uint8_t g, uint8_t b)
		{
			back_color_.unit.r = r;
			back_color_.unit.g = g;
			back_color_.unit.b = b;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バック・カラーの設定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void set_back_color(const color& c)
		{
			back_color_ = c;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バック・カラーの設定
			@param[in]	t	カラー属性
		*/
		//-----------------------------------------------------------------//
//		void set_back_color(utils::color::type t)
//		{
//			back_color_.set(t);
//		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フォア・カラーの設定
			@param[in]	r	赤
			@param[in]	g	緑
			@param[in]	b	青
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(uint8_t r, uint8_t g, uint8_t b)
		{
			fore_color_.unit.r = r;
			fore_color_.unit.g = g;
			fore_color_.unit.b = b;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フォア・カラーの設定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(const color& c)
		{
			fore_color_ = c;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フォア・カラーの設定
			@param[in]	t	カラー属性
		*/
		//-----------------------------------------------------------------//
//		void set_fore_color(utils::color::type t)
//		{
//			fore_color_.set(t);
//		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フォア・カラーとバックカラーの交換
		*/
		//-----------------------------------------------------------------//
		void swap_color()
		{
			std::swap(back_color_, fore_color_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  カラーの文字列生成
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		static void insert_color_str(const color& c)
		{
			http_format("color=\"#%02X%02X%02X\"")
				% static_cast<uint32_t>(c.unit.r)
				% static_cast<uint32_t>(c.unit.g)
				% static_cast<uint32_t>(c.unit.b);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アライメント・文字列の取得
			@param[in]	type	アライメント属性
		*/
		//-----------------------------------------------------------------//
		static const char* get_align_str(align type)
		{
			static const char* align_str[] = { "left", "center", "right" };
			return align_str[static_cast<uint32_t>(type)];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  Horizontal Rule（水平線）
			@param[in]	width	横幅
			@param[in]	size	高さ（デフォルト１）
			@param[in	type	アライメント属性（デフォルト「left」）
			@param[in]	col		カラーを適用する場合「true」
			@param[in]	nos		シンプルな概観の場合「true」
		*/
		//-----------------------------------------------------------------//
		void tag_hr(uint16_t width, uint16_t size = 1, align type = align::left, bool col = false, bool nos = false)
		{
			http_format("<hr ");
			if(col) {
				insert_color_str(fore_color_);
			}
			http_format(" align=\"%s\" width=\"%d\" size=\"%d\" %s>")
				% get_align_str(type)
				% width
				% size
				% (nos ? "noshade" : "");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  input 形式の生成
			@param[in]	type	タイプ
			@param[in]	link	リンク先
			@param[in]	text	文字列
		*/
		//-----------------------------------------------------------------//
		void tag_input()
		{
//			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"戻る\">");
		}
	};
}
