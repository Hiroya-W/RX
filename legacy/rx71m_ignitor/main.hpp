#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター・コントローラー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#define HTTP_DEBUG

#include "r_net/ethernet.hpp"
#include "r_net/http_server_.hpp"
#include "r_net/telnet_server.hpp"

extern "C" {

	void INT_Excep_ICU_GROUPAL1(void);


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time();


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字出力
		@param[in]	ch	文字
	*/
	//-----------------------------------------------------------------//
	void sci_putch(char ch);


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s);


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void);


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void);

}

namespace {

#if 0
	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SDC_RSPI;
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出
#endif
	typedef net::http_server<16, 8192> HTTP_SERVER;
	typedef net::telnet_server<4096, 4096> TELNETS;
//	typedef utils::sdc_io<SDC_RSPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の作成
		@param[in]	date	日付
		@param[in]	time	時間
	*/
	//-----------------------------------------------------------------//
	size_t make_time(const char* date, const char* time);


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t);


	void crm_out(const char* out);
	uint32_t crm_len();
	char crm_inp();


	void dc2_out(const char* out);
	uint32_t dc2_len();
	char dc2_inp();


	void dc1_out(const char* out);


	void wgm_out(const char* out);


	void icm_out(const char* out);


	void wdm_out(uint32_t cmd);
}
