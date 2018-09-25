//=====================================================================//
/*! @file
    @brief  RX64M SDC サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/string_utils.hpp"

// #define SDHI_IF

namespace {

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fifo<uint16_t, 256> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::rtc_io rtc_;

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御

#ifdef SDHI_IF
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER> SDHI;  ///< ハードウェアー定義
	SDHI	sdh_;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;

	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義
//	typedef device::rspi_io<device::RSPI> RSPI;  ///< Hard SPI 定義
//	RSPI rspi_;
	SPI		spi_;

	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;  ///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;  ///< カード検出

	typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> MMC;   ///< ハードウェアー定義

	MMC		sdh_(spi_, 20000000);
#endif
	typedef utils::sdc_man SDC;
	SDC		sdc_;

	utils::command<256> cmd_;

//	utils::SDRAM_128M_32W	sdram_;

	uint8_t v_ = 91;
	uint8_t m_ = 123;
	uint8_t rand_()
	{
		v_ += v_ << 2;
		++v_;
		uint8_t n = 0;
		if(m_ & 0x02) n = 1;
		if(m_ & 0x40) n ^= 1;
		m_ += m_;
		if(n == 0) ++m_;
		return v_ ^ m_;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  ファイル作成テスト
		@param[in]	fname	ファイル名
		@param[in]	size	作成サイズ
		@return 成功なら「true」
	*/
	//-----------------------------------------------------------------//
	bool create_test_file_(const char* fname, uint32_t size)
	{
		uint8_t buff[512];
		FIL fp;

		for(uint16_t i = 0; i < sizeof(buff); ++i) {
			buff[i] = rand_();
		}

		auto st = cmt_.get_counter();
		if(!sdc_.open(&fp, fname, FA_WRITE | FA_CREATE_ALWAYS)) {
			utils::format("Can't create file: '%s'\n") % fname;
			return false;
		}

		auto ed = cmt_.get_counter();
		uint32_t topen = ed - st;
		st = ed;

		auto rs = size;
		while(rs > 0) {
			UINT sz = sizeof(buff);
			if(sz > rs) sz = rs;
			UINT bw;
			f_write(&fp, buff, sz, &bw);
			rs -= bw;
		}
		ed = cmt_.get_counter();
		uint32_t twrite = ed - st;
		st = ed;

		f_close(&fp);
		ed = cmt_.get_counter();
		uint32_t tclose = ed - st;

		utils::format("Open:  %d [ms]\n") % (topen * 10);
		auto pbyte = size * 100 / twrite;
		utils::format("Write: %d Bytes/Sec\n") % pbyte;
		utils::format("Write: %d KBytes/Sec\n") % (pbyte / 1024);
		utils::format("Close: %d [ms]\n") % (tclose * 10);

		return true;
	}
}


extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}


	char sci_getch(void)
	{
		return sci_.getch();
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return sdh_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdh_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdh_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		time_t t = 0;
		rtc_.get_time(t);
		return utils::str::get_fattime(t);
	}


	void utf8_to_sjis(const char* src, char* dst, uint32_t len) {
		utils::str::utf8_to_sjis(src, dst, len);
	}


	time_t get_time_()
	{
		time_t t = 0;
		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read\n");
		}
		return t;
	}


	void disp_time_(time_t t)
	{
		struct tm *m = localtime(&t);
		utils::format("%s %s %d %02d:%02d:%02d  %4d\n")
			% get_wday(m->tm_wday)
			% get_mon(m->tm_mon)
			% static_cast<uint32_t>(m->tm_mday)
			% static_cast<uint32_t>(m->tm_hour)
			% static_cast<uint32_t>(m->tm_min)
			% static_cast<uint32_t>(m->tm_sec)
			% static_cast<uint32_t>(m->tm_year + 1900);
	}


	const char* get_dec_(const char* p, char tmch, int& value) {
		int v = 0;
		char ch;
		while((ch = *p) != 0) {
			++p;
			if(ch == tmch) {
				break;
			} else if(ch >= '0' && ch <= '9') {
				v *= 10;
				v += ch - '0';
			} else {
				return nullptr;
			}
		}
		value = v;
		return p;
	}


	void set_time_date_()
	{
		time_t t = get_time_();
		if(t == 0) return;

		struct tm *m = localtime(&t);
		bool err = false;
		if(cmd_.get_words() == 3) {
			char buff[12];
			if(cmd_.get_word(1, buff, sizeof(buff))) {
				const char* p = buff;
				int vs[3];
				uint8_t i;
				for(i = 0; i < 3; ++i) {
					p = get_dec_(p, '/', vs[i]);
					if(p == nullptr) {
						break;
					}
				}
				if(p != nullptr && p[0] == 0 && i == 3) {
					if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
					if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
					if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
				} else {
					err = true;
				}
			}

			if(cmd_.get_word(2, buff, sizeof(buff))) {
				const char* p = buff;
				int vs[3];
				uint8_t i;
				for(i = 0; i < 3; ++i) {
					p = get_dec_(p, ':', vs[i]);
					if(p == nullptr) {
						break;
					}
				}
				if(p != nullptr && p[0] == 0 && (i == 2 || i == 3)) {
					if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
					if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
					if(i == 3 && vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
					else m->tm_sec = 0;
				} else {
					err = true;
				}
			}
		}

		if(err) {
			sci_puts("Can't analize Time/Date input.\n");
			return;
		}

		time_t tt = mktime(m);
		if(!rtc_.set_time(tt)) {
			sci_puts("Stall RTC write...\n");
		}
	}


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
//	SDC_POWER::DIR = 1;
//	SDC_POWER::P = 0;

	device::system_io<12000000>::setup_system_clock();

	// SDRAM 初期化 128M/32bits bus
//	sdram_();

	{  // タイマー設定（１００Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(100, cmt_irq_level);
	}

	{  // SCI 設定
//		uint8_t sci_level = 2;
		uint8_t sci_level = 0;
		sci_.start(115200, sci_level);
	}

	{  // RTC 設定
		rtc_.start();
	}

#ifdef SDHI_IF
	utils::format("RX64M SDHI SD-Card sample\n");
#else
	utils::format("RX64M Soft SPI SD-Card sample\n");
#endif
	{  // SD カード・クラスの初期化
		sdh_.start();
		sdc_.start();
	}

	// 電圧検出の表示
//	utils::format("  LVDA0: %d\n") % static_cast<uint16_t>(device::SYSTEM::RSTSR0.LVD0RF());
//	utils::format("  LVDA1: %d\n") % static_cast<uint16_t>(device::SYSTEM::RSTSR0.LVD1RF());
//	utils::format("  LVDA2: %d\n") % static_cast<uint16_t>(device::SYSTEM::RSTSR0.LVD2RF());

	device::PORT0::PDR.B7 = 1; // output

	cmd_.set_prompt("# ");

	uint32_t cnt = 0;
	char buff[16];
	while(1) {
		cmt_.sync();

		sdc_.service(sdh_.service());

		// コマンド入力と、コマンド解析
		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				bool f = false;
				if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							cmd_.get_word(1, tmp, sizeof(tmp));
							sdc_.dir(tmp);
						} else {
							sdc_.dir("");
						}
					}
					f = true;
				} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							cmd_.get_word(1, tmp, sizeof(tmp));
							sdc_.cd(tmp);						
						} else {
							sdc_.cd("/");
						}
					}
					f = true;
				} else if(cmd_.cmp_word(0, "pwd")) { // pwd
					utils::format("%s\n") % sdc_.get_current();
					f = true;
				} else if(cmd_.cmp_word(0, "date")) {
					if(cmdn == 1) {
						time_t t = get_time_();
						if(t != 0) {
							disp_time_(t);
						}
					} else {
						set_time_date_();
					}
					f = true;
///				} else if(cmd_.cmp_word(0, "power")) {
///					SDC_POWER::P = 0;
///					f = true;
				} else if(cmd_.cmp_word(0, "test")) {
					create_test_file_("write_test.bin", 1024 * 1024);
					f = true;
				} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
					utils::format("date\n");
					utils::format("date yyyy/mm/dd hh:mm[:ss]\n");
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
					utils::format("test    test speed for write file\n");
					f = true;
				}
				if(!f) {
					char tmp[128];
					if(cmd_.get_word(0, tmp, sizeof(tmp))) {
						utils::format("Command error: '%s'\n") % tmp;
					}
				}
			}
		}

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 15) ? 0 : 1;
	}
}
