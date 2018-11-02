#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/system.hpp"

#ifndef F_ICLK
#  error "system_io.hpp requires F_ICLK to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	BASE_CLOCK	ベース・クロック周波数（１２ＭＨｚ）
		@param[in]	EXT_CLOCK	外部クロックに入力を行う場合「true」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t BASE_CLOCK = 12000000, bool EXT_CLOCK = false>
	struct system_io {

		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
		*/
		//-------------------------------------------------------------//
		static void setup_system_clock()
		{
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
			// メインクロック強制発振とドライブ能力設定
			uint8_t modrv2 = 0b11;
			if(BASE_CLOCK > 20000000) modrv2 = 0b00;
			else if(BASE_CLOCK > 16000000) modrv2 = 0b01;
			else if(BASE_CLOCK > 8000000) modrv2 = 0b10;
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2)
						  | device::SYSTEM::MOFCR.MOSEL.b(EXT_CLOCK);
///						  device::SYSTEM::MOFCR.MOFXIN.b(1)
			device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }

			// RX71M、240MHz 時の MEMWAIT はスーパーバイザモードでの設定が必須なので、
			// device::SYSTEM::MEMWAIT = 1; は、start.s で設定される。

#if defined(SIG_RX65N)
			// RX65N の場合、120MHz 動作が標準
			device::SYSTEM::ROMWT = 0b10;
#endif
			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			uint32_t n = F_ICLK * 2 / BASE_CLOCK;
			if(n < 20) n = 20;
			else if(n > 60) n = 60;
			n -= 20;
			device::SYSTEM::PLLCR.STC = n + 0b010011;  // base 240MHz(12MHz)
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }
			uint8_t id = 1;
			if(F_ICLK > 120000000) id = 0;
			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)    // 1/4 (240/4=60)
								  | device::SYSTEM::SCKCR.ICK.b(id)   // 1/2 (240/2=120)
								  | device::SYSTEM::SCKCR.BCK.b(2)    // 1/4 (240/4=60)
								  | device::SYSTEM::SCKCR.PCKA.b(1)   // 1/2 (240/2=120)
								  | device::SYSTEM::SCKCR.PCKB.b(2)   // 1/4 (240/4=60)
								  | device::SYSTEM::SCKCR.PCKC.b(2)   // 1/4 (240/4=60)
								  | device::SYSTEM::SCKCR.PCKD.b(2);  // 1/4 (240/4=60)
			device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
			device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;
		}
	};


	//-------------------------------------------------------------//
	/*!
		@brief  ソフト・リセットの起動
	*/
	//-------------------------------------------------------------//
	inline void assert_soft_reset()
	{
		device::SYSTEM::PRCR = 0xA502;
		device::SYSTEM::SWRR = 0xA501;
		device::SYSTEM::PRCR = 0xA500;
	}
}
