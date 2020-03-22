#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cmath>
#include "main.hpp"
#include "common/string_utils.hpp"
#include "chip/NTCTH.hpp"

#include "write_file.hpp"
#include "client.hpp"

#include "r_net/ethernet.hpp"
#include "r_net/ethernet_client.hpp"

#include "net_tools.hpp"
#include "setup.hpp"

// プリファレンスの書き込みをＳＤカードに行う場合有効にする
//#define PREFER_SD

#include "preference.hpp"

extern "C" {
	void INT_Excep_ICU_GROUPAL1(void);
}

// #define NETS_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class nets {

#ifdef NETS_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		static const uint16_t WATCHDOG_MIN = 1;  ///< WatchDog の最低時間（分）

#ifdef SEEDA
		typedef device::PORT<device::PORT7, device::bitpos::B0> LAN_RESN;
		typedef device::PORT<device::PORT7, device::bitpos::B3> LAN_PDN;
#endif

		net::ethernet	ethernet_;

		HTTP			http_;
		FTPS			ftps_;
		TELNETS			telnets_;

		client			client_;

		uint32_t		count_;

		uint32_t		item_;

		// サーミスタ定義
		// A/D: 12 bits, NT103_41G, 分圧抵抗: 10K オーム、サーミスタ: ＶＣＣ側
		typedef chip::NTCTH<4095, chip::thermistor::NT103_41G, 10000, true> THMISTER;
		THMISTER	thmister_;

		write_file	write_file_;

		setup	setup_;

		preference	pre_;

		uint32_t	startup_delay_;

		bool 	develope_;

		//-------------------------------------------------------------------------//

		void write_pre_()
		{
			pre_.at().client_enable_ = client_.get_enable();
			for(int i = 0; i < 4; ++i) pre_.at().client_ip_[i] = (client_.get_ip())[i];
			pre_.at().client_port_ = client_.get_port();

			for(int ch = 0; ch < 8; ++ch) {
				pre_.at().mode_[ch] = static_cast<uint8_t>(at_sample(ch).mode_);
				pre_.at().gain_[ch] = at_sample(ch).gain_;
				pre_.at().center_[ch] = at_sample(ch).center_;
				pre_.at().limit_lo_level_[ch] = at_sample(ch).limit_lo_level_;
				pre_.at().limit_hi_level_[ch] = at_sample(ch).limit_hi_level_;
			}

			strcpy(pre_.at().write_path_, write_file_.get_path());
			pre_.at().write_enable_ = write_file_.get_enable();

			pre_.write();
		}


		void make_adc_csv_(const char* tail)
		{
			for(uint32_t ch = 0; ch < get_channel_num(); ++ch) {
				const auto& t = get_sample_data().smp_[ch];
				char tmp[256];
				t.make_csv(tmp, sizeof(tmp), false);
				if(tail != nullptr) {
					utils::sformat("%s", tmp, sizeof(tmp), true) % tail;
				}
				http_format("%s") % tmp;
			}
		}


		void render_data_()
		{
			http_format("<font size=\"4\">\n");
			++count_;
			http_format("Conection: %d<br>\n") % count_;

			net_tools::render_date_time();

			http_format("サンプリング周期： 1[ms]<br>\n");

			http_format("</font>\n");

			if(0) {  // 内臓 A/D 表示（湿度、温度）
				auto v = get_adc(6);
				http_format("温度： %5.2f [度]\n") % thmister_(v);
				http_.tag_hr(600, 3);
			}

			http_format("<style type=\"text/css\">");
			http_format(".table5 {");
			http_format("  border-collapse: collapse;");
			http_format("  width: 600px;");
			http_format("}");
			http_format(".table5 th {");
			http_format("  background-color: #cccccc;\n");
			http_format("}");
			http_format(".table5 td {");
			http_format("  text-align: center;");
			http_format("}");
			http_format("</style>\n");

			http_format("<table class=\"table5\" border=1>");
			http_format(" <tr><th>チャネル</th><th>表示</th><th>最小値</th><th>最大値</th><th>平均</th>"
				"<th>下限</th><th>下限数</th>"
				"<th>上限</th><th>上限数</th><th>Median</th></tr>\n");

			static const char* modes[] = { "数値", "係数", "絶対" };
			for(uint32_t ch = 0; ch < get_channel_num(); ++ch) {
				const auto& t = get_sample_data().smp_[ch];
				char min[16];
				t.value_convert(t.min_,     min, sizeof(min));
				char max[16];
				t.value_convert(t.max_,     max, sizeof(max));
				char ave[16];
				t.value_convert(t.average_, ave, sizeof(ave));
				char med[16];
				t.value_convert(t.median_,  med, sizeof(med));
				http_format("<tr>"
					"<td>%d</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%s</td>"
					"</tr>\n")
					% ch
					% modes[static_cast<uint32_t>(t.mode_)]
					% min
					% max
					% ave
					% static_cast<uint32_t>(t.limit_lo_level_)
					% static_cast<uint32_t>(t.limit_lo_count_)
					% static_cast<uint32_t>(t.limit_hi_level_)
					% static_cast<uint32_t>(t.limit_hi_count_)
					% med;
			}
			http_format("</table>\n");
			http_format("<br>\n");

			http_.tag_hr(600, 3);
			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
		}


		void set_rtc_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_RTC;
			CGI_RTC cgi;
			cgi.parse(http_.get_post_body());
			const char* date = nullptr;
			const char* time = nullptr;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				if(t.key == nullptr) {
					break;
				} else if(strcmp(t.key, "date") == 0) {
					date = t.val;
				} else if(strcmp(t.key, "time") == 0) {
					time = t.val;
				} else {
					break;
				}
			}
			if(date != nullptr && time != nullptr) {
				time_t t = seeda::make_time(date, time);
				if(t != 0) {
					seeda::set_time(t);
					seeda::set_org_time(t);  // 稼動時間の起点変更
				}
			}
//			cgi.list();
		}


		void dev_adc_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_ADC;
			CGI_ADC cgi;
			cgi.parse(http_.get_post_body());
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				if(t.key == nullptr || t.val == nullptr) {
					break;
				} else if(std::strcmp(t.key, "mode") == 0) {
					if(std::strcmp(t.val, "normal") == 0) {  // 通常
						setup_.at_signal() = false;
						debug_format("Turn Normal\n");
					} else if(std::strcmp(t.val, "signal") == 0) {  // 信号生成
						setup_.at_signal() = true;
						debug_format("Turn Signal\n");
					}
				}
			}
		}


		void set_adc_()
		{
			typedef utils::parse_cgi_post<2048, 6 * 8> CGI_ADC;
			CGI_ADC cgi;
			cgi.parse(http_.get_post_body());
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				int ch = 0;
				bool err = true;
				if(t.key == nullptr || t.val == nullptr) {

				} else if((utils::input("mode%d", t.key) % ch).status()) {
					if(strcmp(t.val, "none") == 0) {  // 数値（無変換）
						at_sample(ch).mode_ = seeda::sample_t::mode::none;
						err = false;
					} else if(strcmp(t.val, "real") == 0) {  // 係数値変換
						at_sample(ch).mode_ = seeda::sample_t::mode::real;
						err = false;
					} else if(strcmp(t.val, "abs") == 0) {  // 絶対値変換
						at_sample(ch).mode_ = seeda::sample_t::mode::abs;
						err = false;
					}
				} else if((utils::input("gain%d", t.key) % ch).status()) {
					float v = 0.0f;
					if((utils::input("%f", t.val) % v).status()) {
						at_sample(ch).gain_ = v;
						err = false;
					}
				} else if((utils::input("center%d", t.key) % ch).status()) {
					int v = 0;
					if((utils::input("%d", t.val) % v).status()) {
						if(v >= 0 && v <= 65535) {
							at_sample(ch).center_ = v;
							err = false;
						}
					}
				} else if((utils::input("level_lo%d", t.key) % ch).status()) {
					int v = 0;
					if((utils::input("%d", t.val) % v).status()) {
						if(v >= 0 && v <= 65535) {
							at_sample(ch).limit_lo_level_ = v;
							err = false;
						}
					}
				} else if((utils::input("level_hi%d", t.key) % ch).status()) {
					int v = 0;
					if((utils::input("%d", t.val) % v).status()) {
						if(v >= 0 && v <= 65535) {
							at_sample(ch).limit_hi_level_ = v;
							err = false;
						}
					}
				}
				if(err) {
					return;
				}
			}
			write_pre_();
//			cgi.list();
		}


		void set_client_()
		{
			typedef utils::parse_cgi_post<256, 3> CGI_IP;
			CGI_IP cgi;
			cgi.parse(http_.get_post_body());

			bool enable = false;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				bool err = true;
				if(t.key == nullptr || t.val == nullptr) {

				} else if(strcmp(t.key, "enable") == 0) {
					if(strcmp(t.val, "on") == 0) {
						enable = true;
						err = false;
					}
				} else if(strcmp(t.key, "ip") == 0) {
					debug_format("Set client IP: '%s'\n") % t.val;
					if(client_.at_ip().from_string(t.val)) {
						err = false;
					}
				} else if(strcmp(t.key, "port") == 0) {
					int port;
					if((utils::input("%d", t.val) % port).status()) {
						debug_format("Set client PORT: %d\n") % port;
						client_.set_port(port);
						err = false;
					}
				}
				if(err) {
					return;
				}
			}
			debug_format("Set client %s\n") % (enable ? "ENABLE" : "DISABLE");
			client_.set_enable(enable);
			write_pre_();
///			client_.re_start();
		}


		bool set_write_()
		{
			if(!write_file_.get_enable()) {
///				typedef utils::parse_cgi_post<256, 2> CGI_IP;
				typedef utils::parse_cgi_post<256, 1> CGI_IP;
				CGI_IP cgi;
				cgi.parse(http_.get_post_body());
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					bool err = true;
					if(t.key == nullptr || t.val == nullptr) {

					} else if(strcmp(t.key, "fname") == 0) {
						auto len = std::strlen(t.val);
						if(len > 0 && len < preference::WRITE_FILE_MAX_PATH) {
							write_file_.set_path(t.val);
							err = false;
						} else {
							debug_format("Write file path length error: '%s'\n") % t.val;
						}
///					} else if(strcmp(t.key, "count") == 0) {
///						int n = 0;
///						if((utils::input("%d", t.val) % n).status()) {
///							if(n > 0) {
///								write_file_.set_limit(n);
///								err = false;
///							}
///						}
					}
					if(err) {
						return false;
					}
				}
				write_file_.enable();
			} else {
				write_file_.enable(false);
			}
			write_pre_();
			return true;
		}


		void set_ip_()
		{
			typedef utils::parse_cgi_post<512, 13> CGI_IP;
			CGI_IP cgi;
			cgi.parse(http_.get_post_body());
			bool dhcp = false;
			net::ip_address ip;
 			net::ip_address gw;
			net::ip_address mask;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				int n = 0;
				bool err = true;
				if(t.key == nullptr || t.val == nullptr) {

				} else if(strcmp(t.key, "dhcp") == 0) {
					if(strcmp(t.val, "on") == 0) {
						dhcp = true;
						err = false;
					}
				} else if((utils::input("ip%d", t.key) % n).status()) {
					if(n >= 0 && n <= 3) {
						int v = 0;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 255) {
								ip[n] = v;
								err = false;
							}
						}
					}
				} else if((utils::input("gw%d", t.key) % n).status()) {
					if(n >= 0 && n <= 3) {
						int v = 0;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 255) {
								gw[n] = v;
								err = false;
							}
						}
					}
				} else if((utils::input("mask%d", t.key) % n).status()) {
					if(n >= 0 && n <= 3) {
						int v = 0;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 255) {
								mask[n] = v;
								err = false;
							}
						}
					}
				}

				if(err) {
					utils::format("IP/GW/MASK NG\n");
					return;
				}
			}

			uint32_t mm = static_cast<uint32_t>(mask);
			if(!net::ip_address::check_mask(mm)) {
				utils::format("NG Mask: %d.%d.%d.%d\n")
					% static_cast<uint16_t>(mask[0])
					% static_cast<uint16_t>(mask[1])
					% static_cast<uint16_t>(mask[2])
					% static_cast<uint16_t>(mask[3]);
				return;
			}
			if(!net::ip_address::check_adrs(static_cast<uint32_t>(ip), mm)) {
				utils::format("NG IP: %d.%d.%d.%d\n")
					% static_cast<uint16_t>(ip[0])
					% static_cast<uint16_t>(ip[1])
					% static_cast<uint16_t>(ip[2])
					% static_cast<uint16_t>(ip[3]);
				return;
			}
			if(!net::ip_address::check_adrs(static_cast<uint32_t>(gw), mm)) {
				utils::format("NG GW: %d.%d.%d.%d\n")
					% static_cast<uint16_t>(gw[0])
					% static_cast<uint16_t>(gw[1])
					% static_cast<uint16_t>(gw[2])
					% static_cast<uint16_t>(gw[3]);
				return;
			}
			if(ip == gw) {
				utils::format("NG IP/GW: even address\n");
				return;
			}
			setup_.at_ipt().dhcp_ = dhcp;
			for(uint32_t i = 0; i < 4; ++i) {
				setup_.at_ipt().ip_[i] = ip[i];
				setup_.at_ipt().gw_[i] = gw[i];
				setup_.at_ipt().mask_[i] = mask[i];
			}
			setup_.write_eui();
		}

#ifdef WATCH_DOG
		void set_watchdog_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_REST;
			CGI_REST cgi;
			cgi.parse(http_.get_post_body());
			bool enable = false;
			bool err = true;
			uint32_t time = 5;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				if(t.key == nullptr || t.val == nullptr) {

				} else if(strcmp(t.key, "enable") == 0) {
					if(strcmp(t.val, "on") == 0) {
						enable = true;
					}
				} else if(strcmp(t.key, "wdtime") == 0) {
					int n = 0;
					if((utils::input("%d", t.val) % n).status()) {
						if(n >= WATCHDOG_MIN) {
							time = n;
							err = false;
						}
					}
				}
			}
			if(!err) {
				pre_.at().watchdog_enable_ = enable;
				pre_.at().watchdog_time_ = time;
				write_pre_();
				set_watchdog(static_cast<uint32_t>(time) * 60 * 100, enable);
			}
		}
#endif

		void set_restart_()
		{
			typedef utils::parse_cgi_post<256, 3> CGI_REST;
			CGI_REST cgi;
			cgi.parse(http_.get_post_body());
			bool err = false;
			int delay = 0;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				if(t.key == nullptr || t.val == nullptr) {
					err = true;
				} else if(strcmp(t.key, "restime") == 0) {
					int n = 0;
					if((utils::input("%d", t.val) % n).status()) {
						delay = n;
					} else {
						err = true;
					}
				} else if(strcmp(t.key, "reskey") == 0) {
					if(strcmp(t.val, setup_.get_restart_key()) == 0) {
					} else {
						err = true;
					}
				} else {
					err = true;
				}
			}
			if(!err && delay >= 1) {
				utils::format("Restart: %d after, key: %s\n") % delay % setup_.get_restart_key();
				set_restart_delay(delay * 100);
			}
		}


		void startup_()
		{
			pre_.start();

			setup_.init_eui(develope_);
			const setup::ip_t& ipt = setup_.get_ipt();
			const uint8_t* mac = setup_.get_mac();

			net::ip_address ipa(ipt.ip_[0], ipt.ip_[1], ipt.ip_[2], ipt.ip_[3]);
			net::ip_address mask(ipt.mask_[0], ipt.mask_[1], ipt.mask_[2], ipt.mask_[3]);
			net::ip_address gw(ipt.gw_[0], ipt.gw_[1], ipt.gw_[2], ipt.gw_[3]);
			if(setup_.get_ipt().dhcp_) {
				if(ethernet_.begin(mac) == 0) {
					debug_format("Ethernet Fail: begin (DHCP)...\n");
					utils::format("Direct IP:  ");
					ethernet_.begin(mac, ipa, gw, gw, mask);
				} else {
					utils::format("GetDHCP IP: ");
				}
			} else {
				ethernet_.begin(mac, ipa);
				utils::format("Direct IP:  ");
			}
			utils::format("%s\n") % ethernet_.get_local_ip().c_str();
			utils::format("SubnetMask: %s\n") % ethernet_.get_subnet_mask().c_str();
			utils::format("Gateway IP: %s\n\n") % ethernet_.get_gateway_ip().c_str();

			// HTTP Server
			http_.start("Seeda03 HTTP Server");

			http_.set_link("/", "SimpleData", [=](void) {
				++count_;
				http_format("Conection: %d<br>\n") % count_;
				net_tools::render_date_time();
				http_format("Sampling: 1[ms]<br>\n");
				make_adc_csv_("<br>\n");
			} );

			http_.set_link("/data", "RichData", [=](void) {
				render_data_();
			} );

			http_.set_link("/setup", "SetupMain", [=](void) {
				setup_.render_main(develope_);
			} );

			http_.set_link("/client", "SetupClient", [=](void) {
				setup_.render_client(develope_);
			} );

			http_.set_link("/preference", "DeletePreference", [=](void) {
				net_tools::render_version();
				net_tools::render_date_time();
				http_.tag_hr(600, 3);
				if(pre_.remove()) {
#ifdef PREFER_SD
					http_format("Succeeded in the removal of the 'seeda03.pre'<br>\n");
#else
					http_format("Succeeded in the removal of the 'preference'<br>\n");
#endif
				} else {
#ifdef PREFER_SD
					http_format("Failed in the removal of the 'seeda03.pre'<br>\n");
#else
					http_format("Failed in the removal of the 'preference'<br>\n");
#endif
				}
				http_.tag_hr(600, 3);
				http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"戻る\">\n");
			} );

			http_.set_link("/sdc_state", "SD CARD State", [=](void) {
				net_tools::render_version();
				net_tools::render_date_time();
				http_.tag_hr(600, 3);
				if(write_file_.get_enable()) {
					http_format("ファイル書き込み中は実行できません。<br>\n");
				} else {
					uint32_t fspc;
					uint32_t capa;
					bool ret = at_sdc().get_disk_space(fspc, capa);
					if(ret) {
						if(develope_) {  // 開発モードでは、バイト表示
							http_format("ＳＤカード全容量： %u [Bytes]<br>\n") % capa;
							http_format("ＳＤカード空容量： %u [Bytes]<br>\n") % fspc;
						} else {
							http_format("ＳＤカード全容量： %3.2f [GBytes]<br>\n")
								% (static_cast<float>(capa) / (1024.0f * 1024.0f));
							http_format("ＳＤカード空容量： %3.2f [GBytes]<br>\n")
								% (static_cast<float>(fspc) / (1024.0f * 1024.0f));
						}

						sd_speed_t t;
						create_test_file("/write_test.bin", 1024 * 1024, t);
						http_format("ライト・オープン： %d [ms]<br>\n") % t.w_open_;
						http_format("ライト： %3.2f [KB/Sec]<br>\n") 
							% (1024.0f * 1000.0f / static_cast<float>(t.write_));
						http_format("ライト・クローズ： %d [ms]<br>\n") % t.w_close_;

						http_format("リード・オープン： %d [ms]<br>\n") % t.r_open_;
						http_format("リード： %3.2f [KB/Sec]<br>\n") 
							% (1024.0f * 1000.0f / static_cast<float>(t.read_));
						http_format("リード・クローズ： %d [ms]<br>\n") % t.r_close_;

						http_format("ファイルリスト： %d [ms] / %d<br>\n") % t.dirlist_ % t.dirlist_num_;
					} else {
						http_format("ＳＤカードがありません。<br>\n");
					}
				}
				http_.tag_hr(600, 3);
				http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
			} );

			http_.set_link("/sdc_elog", "SD CARD Error Log", [=](void) {
				net_tools::render_version();
				net_tools::render_date_time();
				http_.tag_hr(600, 3);
				http_format("<table>");
				uint32_t ofs = 0;
				if(at_logs().size() > 0) {
					ofs = at_logs().current();
				}
				for(uint32_t i = 0; i < at_logs().size(); ++i) {
					uint32_t n = (i + ofs) % at_logs().size();
					const auto& l = at_logs().get(n);
					char tmp[64];
					disp_time(l.time_, tmp, sizeof(tmp));
					http_format("<tr><td>%s: </td>") % tmp;
					http_format("<td>%s</td></tr>") % l.msg_;
				}
				http_format("</table>");
				http_.tag_hr(600, 3);
				http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定画面\">\n");
			} );

			http_.set_cgi("/cgi/set_rtc.cgi", "SetRTC", [=](void) {
				set_rtc_();
				http_.exec_link("/setup");
			} );

			if(develope_) {
				http_.set_cgi("/cgi/dev_adc.cgi", "DevADC", [=](void) {
					dev_adc_();
					http_.exec_link("/setup");
				} );
			}

			http_.set_cgi("/cgi/set_adc.cgi", "SetADC", [=](void) {
				set_adc_();
				http_.exec_link("/setup");
			} );

			http_.set_cgi("/cgi/set_client.cgi", "SetClient", [=](void) {
				set_client_();
				http_.exec_link("/setup");
			} );

			http_.set_cgi("/cgi/set_write.cgi", "SetWrite", [=](void) {
				if(set_write_()) {
					http_.exec_link("/setup");
				} else {
					http_.exec_link("/error");
				}
			} );

			http_.set_cgi("/cgi/set_ip.cgi", "SetIP", [=](void) {
				set_ip_();
				http_.exec_link("/setup");
			} );
#ifdef WATCH_DOG
			http_.set_cgi("/cgi/watchdog.cgi", "RestartTime", [=](void) {
				set_watchdog_();
				http_.exec_link("/setup");
			} );
#endif
			http_.set_cgi("/cgi/restart.cgi", "RestartTime", [=](void) {
				set_restart_();
				http_.exec_link("/setup");
			} );

			http_.set_link("/system", "SystemSetup", [=](void) {
				setup_.render_system();
			} );

			http_.set_link("/error", "SystemError", [=](void) {
				setup_.render_system_error();
			} );

			// FTP Server
			ftps_.start("SEEDA03", "Renesas_RX64M", "SEEDA03", "SEEDA03");

			telnets_.start("SEEDA03");
		}


		void service_startup_()
		{
			if(startup_delay_ == 0) {
				return;
			}
			--startup_delay_;
			if(startup_delay_ == 0) {
				if(pre_.read()) {
					for(int ch = 0; ch < 8; ++ch) {
						at_sample(ch).mode_ = static_cast<sample_t::mode>(pre_.get().mode_[ch]);
						at_sample(ch).gain_ = pre_.get().gain_[ch];
						at_sample(ch).center_ = pre_.get().center_[ch];
						at_sample(ch).limit_lo_level_ = pre_.get().limit_lo_level_[ch];
						at_sample(ch).limit_hi_level_ = pre_.get().limit_hi_level_[ch];
					}
					client_.set_enable(pre_.get().client_enable_);
					for(int i = 0; i < 4; ++i) client_.at_ip()[i] = pre_.get().client_ip_[i];
					client_.set_port(pre_.get().client_port_);

					write_file_.set_path(pre_.get().write_path_);
					write_file_.enable(pre_.get().write_enable_); 
#ifdef WATCH_DOG
					uint32_t time = pre_.get().watchdog_time_;
					if(time >= WATCHDOG_MIN) {
						set_watchdog(time * 60 * 100, pre_.get().watchdog_enable_);
					}
#endif
				}
				client_.start_connect();
			}
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nets() : http_(ethernet_, at_sdc()),
			ftps_(ethernet_, at_sdc()),
			telnets_(ethernet_),
			client_(ethernet_),
			count_(0), item_(0),
			write_file_(),
			setup_(write_file_, client_),
			startup_delay_(100),
			develope_(true)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  プリファレンスへの参照
			@return プリファレンス
		*/
		//-----------------------------------------------------------------//
		const preference& get_pre() const { return pre_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  プリファレンスへの参照
			@return プリファレンス
		*/
		//-----------------------------------------------------------------//
		preference& at_pre() { return pre_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  setup への参照
			@return setup
		*/
		//-----------------------------------------------------------------//
		setup& at_setup() { return setup_; }		


		//-----------------------------------------------------------------//
		/*!
			@brief  setup への参照(RO)
			@return setup
		*/
		//-----------------------------------------------------------------//
		const setup& get_setup() const { return setup_; }		


		//-----------------------------------------------------------------//
		/*!
			@brief  開発用信号生成フラグの取得
			@return 開発用信号生成フラグ
		*/
		//-----------------------------------------------------------------//
		bool get_dev_signal() const { return setup_.get_signal(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
#ifdef SEEDA
			// LAN initialize (PHY reset, PHY POWER-DOWN
			LAN_PDN::DIR = 1;  // output;
			LAN_PDN::P = 1;    // Not Power Down Mode..
			LAN_RESN::DIR = 1; // output;
			LAN_RESN::P = 0;
			utils::delay::milli_second(200); /// reset rise time
			LAN_RESN::P = 1;

			device::power_mgr::turn(device::peripheral::ETHERCA);
			device::port_map::turn(device::peripheral::ETHERCA);
#else
			device::power_cfg::turn(device::peripheral::ETHERC0);
			device::port_map::turn(device::peripheral::ETHERC0);
#endif
			set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

			ethernet_.start();

#ifdef SEEDA
			develope_ = get_develope();
#endif
			startup_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  telnet 文字出力
			@param[in]	ch	文字
		*/
		//-----------------------------------------------------------------//
		void telnet_putch(char ch)
		{
			telnets_.putch(ch);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  telnet 文字列出力
			@param[in]	str	文字列
		*/
		//-----------------------------------------------------------------//
		void telnet_puts(const char* str)
		{
			telnets_.puts(str);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイトル表示（ネット関係）
		*/
		//-----------------------------------------------------------------//
		void title()
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			++item_;

#ifdef SEEDA
			develope_ = get_develope();
#endif

			ethernet_.service();

			if(item_ & 1) {
				http_.service(50);
				write_file_.service(50);
			} else {
				ftps_.service(50);
				client_.service(50);

				if(telnets_.service(50, true)) {
					const char* line = telnets_.get_line();
					if(line == nullptr) ;
					else if(line[0] == 0) ;
					else if(std::strcmp(line, "restart") == 0) {
						utils::format("Restart 5 sec\n");
						set_restart_delay(5 * 100);
					} else if(std::strcmp(line, "arp") == 0) {
						net_tools::list_arp();
					} else {
						utils::format("Command: '%s' error\n") % line;
					}
				}
			}

			if(write_file_.get_enable() || client_.probe()) {
				ftps_.set_rw_limit(512);
			} else {
				ftps_.set_rw_limit();
			}

			service_startup_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  write_file クラスへの参照
			@return write_file クラス
		*/
		//-----------------------------------------------------------------//
		write_file& at_write_file() { return write_file_; }


#ifdef SEEDA
		//-----------------------------------------------------------------//
		/*!
			@brief  PHY リセット信号制御
			@param[in]	cmd		コマンド入力インスタンス
		*/
		//-----------------------------------------------------------------//
		bool reset_signal(CMD cmd)
		{
			uint8_t cmdn = cmd.get_words();
			bool f = false;
			if(cmdn == 1) {
				bool v = LAN_RESN::P();
				debug_format("LAN-RESN: %d\n") % static_cast<int>(v);
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd.get_word(1, tmp, sizeof(tmp))) {
					// Reset signal
					if(strcmp(tmp, "0") == 0) {
						device::PORT7::PODR.B0 = 0;
						f = true;
					} else if(strcmp(tmp, "1") == 0) {
						device::PORT7::PODR.B0 = 1;
						f = true;
					} else {
						debug_format("reset param error: '%s'\n") % tmp;
					}
				}
			}
			return f;
		}
#endif
	};
}
