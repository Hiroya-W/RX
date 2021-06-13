//=====================================================================//
/*! @file
    @brief  I2C サンプル @n
			対話形式で接続された I2C デバイスをモニターする。@n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX64M, RX71M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX65N (RX65N Envision kit): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
					SCI9 を使用する @n
			RX72N: (RX72N Envision kit) @n
					16MHz のベースクロックを使用する @n
					P40 ピンにLEDを接続する @n
					SCI2 を使用する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/command.hpp"
#include "common/iica_io.hpp"
#include "common/sci_i2c_io.hpp"

#include "chip/FT5206.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

namespace {

#if defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::system_io<10'000'000, 80'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C_IO;
#else
	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::system_io<10'000'000, 160'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::system_io<12'000'000, 240'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX71M)
	typedef device::system_io<12'000'000, 240'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::system_io<12'000'000, 240'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N" };
	typedef device::system_io<16'000'000, 240'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	typedef device::SCI4 I2C_CH;
	typedef utils::fixed_fifo<char, 512> RBF;
	typedef utils::fixed_fifo<char, 512> SBF;
	typedef device::sci_i2c_io<I2C_CH, RBF, SBF> I2C_IO;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	// タッチセンサー「RESET」制御ポート
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	// タッチセンサー I2C ポート設定
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;
	#define TOUCH_I2C
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
	SCI		sci_;

#ifdef TOUCH_I2C
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);
#endif

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT			cmt_;

	I2C_IO		i2c_io_;

	typedef utils::command<256> CMD;
	CMD 		cmd_;

	void command_()
	{
		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			uint32_t n = 0;
			while(n < cmdn) {
				char tmp[256];
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					utils::format("Param%d: '%s'\n") % n % tmp;
				}
				++n;
			}
		}
	}
}


extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定（100Hz）
		uint8_t intr = 1;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = F_ICLK / 1000000;
	utils::format("Start I2C sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{  // I2C の開始
//		uint8_t intr = 3;
//		if(!i2c_io_.start(I2C_IO::SPEED::STANDARD, I2C_IO::MODE::MASTER, intr)) {
//			utils::format("I2C Start fail...\n");
//		}
	}

#ifdef TOUCH_I2C
	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		uint8_t intr_lvl = 0;
		if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, FT5206_I2C::MODE::MASTER, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		} else {
			utils::format("FT5206/SCI-I2C Start\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		} else {
			utils::format("FT5206 Start\n");
		}
	}
#endif

	LED::OUTPUT();
	LED::P = 0;

	{
		utils::format("SCI Baud rate (set):  %d\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("SCI Baud rate (real): %d (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;
		utils::format("CMT rate (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("CMT rate (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

#ifdef TOUCH_I2C
		touch_.update();
		{
			auto n = touch_.get_touch_num();
			if(n > 0) {
				utils::format("Touch: %d") % static_cast<int>(n);
				auto t = touch_.get_touch_pos(0);
				utils::format(", (%d, %d)") % t.pos.x % t.pos.y;
				utils::format("\n");
			}
		}
#endif
		command_();

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
