#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCI I/O 制御 @n
			・DMAC による転送をサポートしていませんが、必要性を感じていません。@n
			・同期通信で、ブロック転送を行うような場合は、必要かもしれません。@n
			・RS-485 半二重通信用ポート制御を追加。(作業中) @n
			Ex: 定義例 @n
			・受信バッファ、送信バッファの大きさは、最低１６バイトは必要でしょう。@n
			・ボーレート、サービスする内容に応じて適切に設定して下さい。@n
			  typedef utils::fixed_fifo<char, 512>  RBF;  // 受信バッファ定義 @n
			  typedef utils::fixed_fifo<char, 1024> SBF;  // 送信バッファ定義 @n
			  typedef device::sci_io<device::SCI1, RBF, SBF> SCI;  // SCI1 の場合 @n
			  SCI	sci_; // 実態の宣言 @n
			Ex: 開始例 @n
			  uint8_t intr_level = 2;    // 割り込みレベル(2) @n
			  uint32_t baud = 115200;    // ボーレート設定(115200) @n
			  sci_.start(baud, intr_level); @n  
			Ex: POSIX 関数 (printf など) への通路設定 @n
              C の関数「sci_putch(), sci_getch()」を定義してリンク可能にする。@n
			  POSIX read, write 関数が、stdout ディスクリプタに対してアクセスする。 @n
			  extern "C" { @n
				void sci_putch(char ch) @n
				{ @n
					sci_.putch(ch); @n
				} @n
				char sci_getch(void) @n
				{ @n
					return sci_.getch(); @n
				} @n
			  }; @n
			// 上記関数を定義しておけば、syscalls.c との連携で、printf が使えるようになる。@n
			// ※ C++ では printf は推奨しないし使う理由が無い、utils::format を使って下さい。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/fixed_fifo.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class sci_io_base {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI 通信プロトコル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PROTOCOL : uint8_t {
			B7_N_1S,	///< 7 ビット、No-Parity、1 Stop Bit
			B7_E_1S,	///< 7 ビット、Even(偶数)、1 Stop Bit
			B7_O_1S,	///< 7 ビット、Odd (奇数)、1 Stop Bit
			B7_N_2S,	///< 7 ビット、No-Parity、2 Stop Bits
			B7_E_2S,	///< 7 ビット、Even(偶数)、2 Stop Bits
			B7_O_2S,	///< 7 ビット、Odd (奇数)、2 Stop Bits
			B8_N_1S,	///< 8 ビット、No-Parity、1 Stop Bit
			B8_E_1S,	///< 8 ビット、Even(偶数)、1 Stop Bit
			B8_O_1S,	///< 8 ビット、Odd (奇数)、1 Stop Bit
			B8_N_2S,	///< 8 ビット、No-Parity、2 Stop Bits
			B8_E_2S,	///< 8 ビット、Even(偶数)、2 Stop Bits
			B8_O_2S,	///< 8 ビット、Odd (奇数)、2 Stop Bits
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI ボーレート型（シリアル通信で標準的に指定する定型値）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BAUDRATE : uint32_t {
			B110    =    110,	///<    110 B.P.S.
			B150    =    150,	///<    150 B.P.S.
			B300    =    300,	///<    300 B.P.S.
			B600    =    600,	///<    600 B.P.S.
			B1200   =   1200,	///<   1200 B.P.S.
			B2400   =   2400,	///<   2400 B.P.S.
			B4800   =   4800,	///<   4800 B.P.S.
			B9600   =   9600,	///<   9600 B.P.S.
			B19200  =  19200,	///<  19200 B.P.S.
			B38400  =  38400,	///<  38400 B.P.S.
			B57600  =  57600,	///<  57600 B.P.S.
			B76800  =  76800,	///<  76800 B.P.S.
			B96000  =  96000,	///<  96000 B.P.S.
			B115200 = 115200,	///< 115200 B.P.S.
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O 制御クラス
		@param[in]	SCI		SCI 型
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポートマップ選択
		@param[in]	HCTL	半二重通信制御ポート（for RS-485）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::ORDER PSEL = port_map::ORDER::FIRST, class HCTL = NULL_PORT>
	class sci_io : public sci_io_base {
	public:
		typedef SCI sci_type;
		typedef RBF rbf_type;
		typedef SBF sbf_type;

	private:

		static constexpr char XON  = 0x11;
		static constexpr char XOFF = 0x13;

		const port_map_order::sci_port_t&	port_map_;

		static RBF	recv_;
		static SBF	send_;

		uint8_t		level_;
		bool		auto_crlf_;
		uint32_t	baud_;
		static bool		soft_flow_;
		static volatile bool		stop_;
		static volatile uint16_t	errc_;

		// ※マルチタスクの場合適切な実装をする
		void sleep_() noexcept { asm("nop"); }


		static INTERRUPT_FUNC void recv_task_()
		{
			bool err = false;
			if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
				SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				err = true;
			}
			///< フレーミングエラー/パリティエラー状態確認
			if(SCI::SSR() & (SCI::SSR.FER.b() | SCI::SSR.PER.b())) {
				// エラーフラグの消去
				SCI::SSR.FER = 0;
				SCI::SSR.PER = 0;
				err = true;
			}
			volatile uint8_t data = SCI::RDR();
			if(err) {
				++errc_;
			} else {
				if(soft_flow_) {
					if(recv_.length() >= (recv_.size() - recv_.size() / 8)) {
						stop_ = true;
					}
				}
				recv_.put(data);
			}
		}


		static INTERRUPT_FUNC void send_task_()
		{
			if(send_.length() > 0) {
//				if(stop_) {
//					SCI::TDR = XON;
//					stop_ = false;
//				} else {
					SCI::TDR = send_.get();
//				}
			} else {
				SCI::SCR.TIE = 0;
				HCTL::P = 0;
			}
		}


		void set_intr_(uint8_t level) noexcept
		{
			if(level > 0) {
				icu_mgr::set_task(SCI::RX_VEC, recv_task_);
				icu_mgr::set_task(SCI::TX_VEC, send_task_);
			} else {
				icu_mgr::set_task(SCI::RX_VEC, nullptr);
				icu_mgr::set_task(SCI::TX_VEC, nullptr);
			}
			icu_mgr::set_level(SCI::RX_VEC, level);
			icu_mgr::set_level(SCI::TX_VEC, level);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	autocrlf	LF 時、自動で CR の送出をしない場合「false」
			@param[in]	softflow	ソフトフロー制御を無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		sci_io(bool autocrlf = true, bool softflow = true, const port_map_order::sci_port_t& sci_port = port_map_order::sci_port_t()) noexcept :
			port_map_(sci_port),
			level_(0),
			auto_crlf_(autocrlf), baud_(0) {
			soft_flow_ = softflow;
			stop_ = false;
			errc_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー数の取得
			@return エラー数
		 */
		//-----------------------------------------------------------------//
		static uint16_t get_error_count() noexcept { return errc_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	LF 時、CR 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) noexcept { auto_crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフト・フロー制御設定
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		static void soft_flow(bool f = true) noexcept { soft_flow_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする @n
					※RX63T では、ポーリングはサポート外
			@param[in]	baud	ボーレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（標準は、８ビット、パリティ無し、１ストップ）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, uint8_t level = 0, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
#if defined(SIG_RX63T)
			if(level == 0) return false;
#endif
			level_ = level;
			stop_ = false;
			recv_.clear();
			send_.clear();

			if(!power_mgr::turn(SCI::PERIPHERAL)) {
				return false;
			}
			// PSEL に、BYPASS が選択された場合、個別のポート設定が有効になる。
			if(PSEL == port_map_order::ORDER::BYPASS) {
// この仕組みは、現在開発中・・・
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72T)
				uint8_t ok = 0;
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::CTS, true, port_map_.cts_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::RTS, true, port_map_.rts_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::RXD, true, port_map_.rxd_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::SCK, true, port_map_.sck_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::TXD, true, port_map_.txd_);
				if(ok != 5) {
					power_mgr::turn(SCI::PERIPHERAL, false);
					return false;
				}
#endif
			} else {
				if(!port_map::turn(SCI::PERIPHERAL, true, PSEL)) {
					power_mgr::turn(SCI::PERIPHERAL, false);
					return false;
				}
			}

			set_intr_(0);

			SCI::SCR = 0x00;			// TE, RE disable.
			{
				auto tmp = SCI::SSR();
				if(tmp & (SCI::SSR.ORER.b() | SCI::SSR.FER.b() | SCI::SSR.PER.b())) {
					SCI::SSR = 0x00;
				}
			}

			// RS-484 半二重制御ポート
			HCTL::DIR = 1;
			HCTL::P = 0;  // disable send driver

			baud_ = baud;
			uint32_t brr = SCI::PCLK / 8 / baud;
			uint8_t cks = 0;
			while(brr > 1024) {
				brr >>= 2;
				++cks;
			}
			uint32_t mtx = 8;
			bool bgdm = true;
			if(brr >= 512) { brr >>= 1; bgdm = false; mtx <<= 1; }
			bool abcs = true;
			if(brr >= 256) { brr >>= 1; abcs = false; mtx <<= 1;}
			uint32_t rate = SCI::PCLK / mtx / brr / (1 << (cks * 2));
			uint32_t mddr = (baud_ << 9) / rate;
			++mddr;
			mddr >>= 1;

			set_intr_(level_);

			bool stop = 0;
			bool pm = 0;
			bool pe = 0;
			switch(prot) {
			case PROTOCOL::B7_N_1S:
			case PROTOCOL::B8_N_1S:
				stop = 0;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_1S:
			case PROTOCOL::B8_E_1S:
				stop = 0;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_1S:
			case PROTOCOL::B8_O_1S:
				stop = 0;
				pm = 1;
				pe = 1;
				break;
			case PROTOCOL::B7_N_2S:
			case PROTOCOL::B8_N_2S:
				stop = 1;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_2S:
			case PROTOCOL::B8_E_2S:
				stop = 1;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_2S:
			case PROTOCOL::B8_O_2S:
				stop = 1;
				pm = 1;
				pe = 1;
				break;
			default:
				return false;
			}
			bool seven = 0;
			if(static_cast<uint8_t>(prot) < 6) seven = 1;
			SCI::SMR = SCI::SMR.CKS.b(cks) | SCI::SMR.STOP.b(stop)
					 | SCI::SMR.PM.b(pm) | SCI::SMR.PE.b(pe) | SCI::SMR.CHR.b(seven);
			bool brme = false;
			if(mddr >= 128 && mddr < 256) brme = true;
			SCI::SEMR = SCI::SEMR.ABCS.b(abcs) | SCI::SEMR.BRME.b(brme) | SCI::SEMR.BGDM.b(bgdm);
			if(brr) --brr;
			SCI::BRR = brr;
			SCI::MDDR = mddr;

			if(level > 0) {
				SCI::SCR = SCI::SCR.RIE.b() | SCI::SCR.TE.b() | SCI::SCR.RE.b();
			} else {
				SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする
			@param[in]	baud	ボーレート型
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（標準は、８ビット、パリティ無し、１ストップ）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(BAUDRATE baud, uint8_t level = 0, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
			return start(static_cast<uint32_t>(baud), level, prot);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BRR レジスタ値を取得
			@return BRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_brr() const noexcept { return SCI::BRR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	ボーレートを取得
			@param[in]	real	「true」にした場合、内部で計算されたリアルな値
			@return ボーレート
		 */
		//-----------------------------------------------------------------//
		uint32_t get_baud_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t brr = SCI::BRR();
				uint32_t cks = 1 << (SCI::SMR.CKS() * 2);
				uint32_t mtx = 8;
				if(!SCI::SEMR.BGDM()) mtx <<= 1;
				if(!SCI::SEMR.ABCS()) mtx <<= 1;
				auto baud = SCI::PCLK / mtx / cks / (brr + 1);
				if(SCI::SEMR.BRME()) {
					baud *= SCI::MDDR();
					baud /= 256;
				}
				return baud;
			} else {
				return baud_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	MDDR レジスタ値を取得（ボーレート周期補正）
			@return MDRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_mdrr() const noexcept { return SCI::MDDR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 出力バッファのサイズを返す
			@return　バッファのサイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t send_length() const noexcept
		{
			if(level_) {
				return send_.length();
			} else {
				return 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字出力
			@param[in]	ch	文字コード
		 */
		//-----------------------------------------------------------------//
		void putch(char ch)  noexcept
		{
			if(auto_crlf_ && ch == '\n') {
				putch('\r');
			}
			if(level_ > 0) {
				volatile bool b = SCI::SSR.ORER();
				if(b) {
					SCI::SSR.ORER = 0;
				}
				/// 送信バッファの容量が７／８以上の場合は、空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
				if(SCI::SCR.TIE() == 0) {
/// この部分を取り除いても問題無いか評価中・・・
///					while(SCI::SSR.TEND() == 0) sleep_();
					HCTL::P = 1;
					SCI::SCR.TIE = 1;
//					if(stop_) {
//						SCI::TDR = XON;
//						stop_ = false;
//					} else {
						SCI::TDR = send_.get();
//					}
				}
			} else {
				while(SCI::SSR.TEND() == 0) sleep_();
				HCTL::P = 1;
				SCI::TDR = ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t recv_length() noexcept
		{
			if(level_ > 0) {
				return recv_.length();
			} else {
				if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
					SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				}
				return SCI::SSR.RDRF();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力文字を捨てる
		 */
		//-----------------------------------------------------------------//
		void flush_recv() noexcept
		{
			if(recv_length() > 0) {
				recv_.clear();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字入力（ブロック関数）
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() noexcept
		{
			if(level_ > 0) {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			} else {
				while(recv_length() == 0) sleep_();
				return SCI::RDR();	///< 受信データ読み出し
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字列出力
			@param[in]	s	出力文字列
		 */
		//-----------------------------------------------------------------//
		void puts(const char* s)  noexcept
		{
			if(s == nullptr) return;
			char ch;
			while((ch = *s++) != 0) {
				putch(ch);
			}
		}
	};

	// テンプレート関数、実態の定義
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class HCTL>
		RBF sci_io<SCI, RBF, SBF, PSEL, HCTL>::recv_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class HCTL>
		SBF sci_io<SCI, RBF, SBF, PSEL, HCTL>::send_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class HCTL>
		bool sci_io<SCI, RBF, SBF, PSEL, HCTL>::soft_flow_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class HCTL>
		volatile bool sci_io<SCI, RBF, SBF, PSEL, HCTL>::stop_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class HCTL>
		volatile uint16_t sci_io<SCI, RBF, SBF, PSEL, HCTL>::errc_;
}
