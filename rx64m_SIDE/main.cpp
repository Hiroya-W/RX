//=====================================================================//
/*! @file
    @brief  RX64M SIDE sample @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"

#include "side/arcade.h"

namespace {

	InvadersMachine side_;

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fixed_fifo<char, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

}

extern "C" {
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);			
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

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

	device::PORT0::PDR.B7 = 1; // output
	while(1) {



	}
}
