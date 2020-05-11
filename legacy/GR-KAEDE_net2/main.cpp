//=====================================================================//
/*! @file
    @brief  GR-KAEDE_net (RX64M) メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/rspi_io.hpp"
#include "common/sdc_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/fixed_string.hpp"

#include "chip/phy_base.hpp"
#include "net2/net_main.hpp"
#include "net2/test_udp.hpp"
#include "net2/test_tcp.hpp"
#include "net2/http_server.hpp"
#include "net2/ftp_server.hpp"

namespace {

	typedef device::ETHERC0 ETHERC;      // Ethernet Controller
	typedef device::EDMAC0 EDMAC;        // Ethernet DMA Controller
	typedef chip::phy_base<ETHERC> PHY;  // Ethernet PHY (LAN8720)
	typedef device::ether_io<ETHERC, EDMAC, PHY> ETHD;  // EthernetDriver
	ETHD 	ethd_;

	volatile bool tcpip_flag_ = false;
	volatile uint32_t net_int_cnt_ = 0;

	typedef device::cmt_io<device::CMT0> CMT0;
	CMT0	cmt_;

	typedef utils::fixed_fifo<char, 4096> BUFFER;
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
	SCI		sci_;

	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
	SPI		spi_;

	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出

	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
	SDC		sdc_(spi_, 20000000);

	typedef utils::rtc_io RTC;
	RTC		rtc_;

	static const uint32_t UDPN = 4;  // UDP の経路数
 	static const uint32_t TCPN = 6;  // TCP の経路数
	typedef net::net_main<ETHD, UDPN, TCPN> NET_MAIN;
	NET_MAIN	net_(ethd_);

	typedef net::test_udp TEST_UDP;
	TEST_UDP	test_udp_;
	typedef net::test_tcp<NET_MAIN::ETHERNET> TEST_TCP;
	TEST_TCP	test_tcp_(net_.at_ethernet());

	typedef net::http_server<NET_MAIN::ETHERNET, SDC> HTTP;
	HTTP		http_(net_.at_ethernet(), sdc_);

	typedef net::ftp_server<NET_MAIN::ETHERNET, SDC> FTPS;
	FTPS		ftps_(net_.at_ethernet(), sdc_);

	volatile bool putch_lock_ = false;
	utils::fixed_fifo<char, 1024> putch_tmp_;

	void service_putch_tmp_()
	{
		ethd_.enable_interrupt(false);
		while(putch_tmp_.length() > 0) {
			sci_.putch(putch_tmp_.get());
		}
		ethd_.enable_interrupt();
	}
}

extern "C" {

	int tcp_send(uint32_t desc, const void* src, uint32_t len)
	{
		auto& ipv4 = net_.at_ethernet().at_ipv4();
		auto& tcp  = ipv4.at_tcp();
		return tcp.send(desc, src, len);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	割り込みタイマーカウンタの取得（10ms 単位）
		@return 割り込みタイマーカウンタ
	 */
	//-----------------------------------------------------------------//
	uint32_t get_counter() { return cmt_.get_counter(); }


	//-----------------------------------------------------------------//
	/*!
		@brief	イーサーネット・ドライバー・プロセス（割り込みタスク）
	 */
	//-----------------------------------------------------------------//
	void ethd_process_(void)
	{
		net_.process();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字出力 @n
				※割り込み対応
		@param[in]	ch	文字
	*/
	//-----------------------------------------------------------------//
	void sci_putch(char ch)
	{
		if(putch_lock_) {
			if((putch_tmp_.size() - putch_tmp_.length()) >= 2) {
				putch_tmp_.put(ch);
			}
			return;
		}
		putch_lock_ = true;
		sci_.putch(ch);
		putch_lock_ = false;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s)
	{
		sci_.puts(s);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void)
	{
		return sci_.getch();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time()
	{
		time_t t = 0;
		rtc_.get_time(t);
		return t;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ初期化関数を提供
		@param[in]	drv		Physical drive nmuber (0)
		@return ステータス
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.at_mmc().disk_initialize(drv);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へステータスを提供
		@param[in]	drv		Physical drive nmuber (0)
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_status(BYTE drv) {
		return sdc_.at_mmc().disk_status(drv);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へリード・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[out]	buff	Pointer to the data buffer to store read data
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へライト・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	buff	Pointer to the data to be written	
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へI/O コントロールを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	ctrl	Control code
		@param[in]	buff	Buffer to send/receive control data
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ時間を提供
		@return FatFs 時間
	 */
	//-----------------------------------------------------------------//
	DWORD get_fattime(void) {
		auto t = get_time();
		return utils::str::get_fattime(t);
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
//	device::init_port();

	device::PORTC::PDR.B0 = 1; // output
	device::PORTC::PDR.B1 = 1; // output
	device::PORT0::PDR.B2 = 1; // output
	device::PORT0::PDR.B3 = 1; // output


	{  // GR-KAEDE の SPI 端子のハードバグ回避
	   // ※PC3 から、PC7 へ １K オームで接続
		device::PORTC::PDR.B3 = 1; // output
		device::PORTC::PODR.B3 = 1;
	}

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定、１００Ｈｚ（１０ｍｓ）
		uint8_t int_level = 1;
		cmt_.start(100, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("\nStart GR-KAEDE Net2 Stack Sample\n");

	// SD カード・クラスの初期化
	sdc_.start();

	{  // Ethernet の開始
		uint8_t intr_level = 4;
		ethd_.start(intr_level);

		static uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net_.start(mac);

		ethd_.set_intr_task(ethd_process_);
	}

	// UDP test の許可
//	test_udp_.enable();

	// TCP test の許可
//	test_tcp_.set_type(TEST_TCP::type::client_recv_first);
//	test_tcp_.set_type(TEST_TCP::type::client_send_first);
	test_tcp_.set_ip(net::ip_adrs(192, 168, 3, 7));  // クライアント接続の場合設定が必要

//	bool test_http = true;
	bool test_http = false;

	bool test_ftps = true;
//	bool test_ftps = false;

#if 0
	HTTP::http_format::chaout().set_desc(0);
	FTPS::ctrl_format::chaout().set_desc(1);
	FTPS::data_format::chaout().set_desc(2);

	utils::format("http desc: %d\n") % HTTP::http_format::chaout().get_desc();
	utils::format("ftps ctrl desc: %d\n") % FTPS::ctrl_format::chaout().get_desc();
	utils::format("ftps data desc: %d\n") % FTPS::data_format::chaout().get_desc();
#endif

	if(test_http) {  // HTTP サーバーの設定
		http_.start("GR-KAEDE_net2 HTTP Server");

		// ルート・ページ設定
		http_.set_link("/", "", [=](void) {
			time_t t = get_time();
			struct tm *m = localtime(&t);
			HTTP::http_format("%s %s %d %02d:%02d:%02d  %4d<br>\n")
				% get_wday(m->tm_wday)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec)
				% static_cast<uint32_t>(m->tm_year + 1900);

			http_.tag_hr(500, 3);
		} );
	}

	if(test_ftps) {  // FTP サーバーの設定
		static const char* user = { "KAEDE" };
		static const char* pass = { "KAEDE" };
		ftps_.start("GR-KAEDE", "Renesas_RX64M", user, pass);
	}

	uint32_t cnt = 0;
	while(1) {  // 100Hz (10ms interval)
		cmt_.sync();

		sdc_.service();

		service_putch_tmp_();

		net_.service();

		if(net_.check_main()) {
			test_udp_.service(net_.at_ethernet());
			test_tcp_.service();

			if(test_http) {
				http_.service();
			}
			if(test_ftps) {
				ftps_.service();
			}
		}

		device::PORTC::PODR.B0 = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		device::PORTC::PODR.B1 = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B2 = (((cnt + 16) & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B3 = (((cnt + 24) & 31) < 8) ? 1 : 0;
		++cnt;
	}
}
