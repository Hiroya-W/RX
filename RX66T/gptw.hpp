#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T GPTW 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用 PWM タイマ・クラス
		@param[in]	base	ベースアドレス
		@param[in]	peri	ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral peri>
	struct gptw_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtwp_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     WP;
			bit_rw_t <io_, bitpos::B1>     STRWP;
			bit_rw_t <io_, bitpos::B2>     STPWP;
			bit_rw_t <io_, bitpos::B3>     CLRWP;
			bit_rw_t <io_, bitpos::B4>     CMNWP;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static gtwp_t<base + 0x00> GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtstr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSTRT0;
			bit_rw_t <io_, bitpos::B1>  CSTRT1;
			bit_rw_t <io_, bitpos::B2>  CSTRT2;
			bit_rw_t <io_, bitpos::B3>  CSTRT3;
			bit_rw_t <io_, bitpos::B4>  CSTRT4;
			bit_rw_t <io_, bitpos::B5>  CSTRT5;
			bit_rw_t <io_, bitpos::B6>  CSTRT6;
			bit_rw_t <io_, bitpos::B7>  CSTRT7;
			bit_rw_t <io_, bitpos::B8>  CSTRT8;
			bit_rw_t <io_, bitpos::B9>  CSTRT9;
		};
		static gtstr_t<base + 0x04> GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマソフトウェアストップレジスタ (GTSTP)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtstp_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSTOP0;
			bit_rw_t <io_, bitpos::B1>  CSTOP1;
			bit_rw_t <io_, bitpos::B2>  CSTOP2;
			bit_rw_t <io_, bitpos::B3>  CSTOP3;
			bit_rw_t <io_, bitpos::B4>  CSTOP4;
			bit_rw_t <io_, bitpos::B5>  CSTOP5;
			bit_rw_t <io_, bitpos::B6>  CSTOP6;
			bit_rw_t <io_, bitpos::B7>  CSTOP7;
			bit_rw_t <io_, bitpos::B8>  CSTOP8;
			bit_rw_t <io_, bitpos::B9>  CSTOP9;
		};
		static gtstp_t<base + 0x08> GTSTP;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマソフトウェアクリアレジスタ (GTCLR)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtclr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CCLR0;
			bit_rw_t <io_, bitpos::B1>  CCLR1;
			bit_rw_t <io_, bitpos::B2>  CCLR2;
			bit_rw_t <io_, bitpos::B3>  CCLR3;
			bit_rw_t <io_, bitpos::B4>  CCLR4;
			bit_rw_t <io_, bitpos::B5>  CCLR5;
			bit_rw_t <io_, bitpos::B6>  CCLR6;
			bit_rw_t <io_, bitpos::B7>  CCLR7;
			bit_rw_t <io_, bitpos::B8>  CCLR8;
			bit_rw_t <io_, bitpos::B9>  CCLR9;
		};
		static gtclr_t<base + 0x0C> GTCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマスタート要因セレクトレジスタ (GTSSR)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtssr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  SSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  SSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  SSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  SSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  SSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  SSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  SSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  SSCARBL;
			bit_rw_t <io_, bitpos::B9>  SSCARBH;
			bit_rw_t <io_, bitpos::B10> SSCAFBL;
			bit_rw_t <io_, bitpos::B11> SSCAFBH;
			bit_rw_t <io_, bitpos::B12> SSCBRAL;
			bit_rw_t <io_, bitpos::B13> SSCBRAH;
			bit_rw_t <io_, bitpos::B14> SSCBFAL;
			bit_rw_t <io_, bitpos::B15> SSCBFAH;
			bit_rw_t <io_, bitpos::B16> SSELCA;
			bit_rw_t <io_, bitpos::B17> SSELCB;
			bit_rw_t <io_, bitpos::B18> SSELCC;
			bit_rw_t <io_, bitpos::B19> SSELCD;
			bit_rw_t <io_, bitpos::B20> SSELCE;
			bit_rw_t <io_, bitpos::B21> SSELCF;
			bit_rw_t <io_, bitpos::B22> SSELCG;
			bit_rw_t <io_, bitpos::B23> SSELCH;

			bit_rw_t <io_, bitpos::B31> CSTRT;
		};
		static gtssr_t<base + 0x10> GTSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマストップ要因セレクトレジスタ (GTPSR)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtpsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  PSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  PSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  PSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  PSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  PSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  PSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  PSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  PSCARBL;
			bit_rw_t <io_, bitpos::B9>  PSCARBH;
			bit_rw_t <io_, bitpos::B10> PSCAFBL;
			bit_rw_t <io_, bitpos::B11> PSCAFBH;
			bit_rw_t <io_, bitpos::B12> PSCBRAL;
			bit_rw_t <io_, bitpos::B13> PSCBRAH;
			bit_rw_t <io_, bitpos::B14> PSCBFAL;
			bit_rw_t <io_, bitpos::B15> PSCBFAH;
			bit_rw_t <io_, bitpos::B16> PSELCA;
			bit_rw_t <io_, bitpos::B17> PSELCB;
			bit_rw_t <io_, bitpos::B18> PSELCC;
			bit_rw_t <io_, bitpos::B19> PSELCD;
			bit_rw_t <io_, bitpos::B20> PSELCE;
			bit_rw_t <io_, bitpos::B21> PSELCF;
			bit_rw_t <io_, bitpos::B22> PSELCG;
			bit_rw_t <io_, bitpos::B23> PSELCH;

			bit_rw_t <io_, bitpos::B31> CSTOP;
		};
		static gtpsr_t<base + 0x14> GTPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマクリア要因セレクトレジスタ (GTCSR)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtcsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  CSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  CSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  CSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  CSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  CSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  CSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  CSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  CSCARBL;
			bit_rw_t <io_, bitpos::B9>  CSCARBH;
			bit_rw_t <io_, bitpos::B10> CSCAFBL;
			bit_rw_t <io_, bitpos::B11> CSCAFBH;
			bit_rw_t <io_, bitpos::B12> CSCBRAL;
			bit_rw_t <io_, bitpos::B13> CSCBRAH;
			bit_rw_t <io_, bitpos::B14> CSCBFAL;
			bit_rw_t <io_, bitpos::B15> CSCBFAH;
			bit_rw_t <io_, bitpos::B16> CSELCA;
			bit_rw_t <io_, bitpos::B17> CSELCB;
			bit_rw_t <io_, bitpos::B18> CSELCC;
			bit_rw_t <io_, bitpos::B19> CSELCD;
			bit_rw_t <io_, bitpos::B20> CSELCE;
			bit_rw_t <io_, bitpos::B21> CSELCF;
			bit_rw_t <io_, bitpos::B22> CSELCG;
			bit_rw_t <io_, bitpos::B23> CSELCH;

			bit_rw_t <io_, bitpos::B31> CCLR;
		};
		static gtcsr_t<base + 0x18> GTCSR;





#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタート / ストップ制御レジスタ（GTHSCR）
		*/
		//-----------------------------------------------------------------//
		struct gthscr_t : public rw16_t<0x000C2004> {
			typedef rw16_t<0x000C2004> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CSHW0;
			bits_rw_t<io_, bitpos::B2, 2>  CSHW1;
			bits_rw_t<io_, bitpos::B4, 2>  CSHW2;
			bits_rw_t<io_, bitpos::B6, 2>  CSHW3;
			bits_rw_t<io_, bitpos::B8, 2>  CPHW0;
			bits_rw_t<io_, bitpos::B10, 2> CPHW1;
			bits_rw_t<io_, bitpos::B12, 2> CPHW2;
			bits_rw_t<io_, bitpos::B14, 2> CPHW3;
		};
		static gthscr_t GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリア制御レジスタ（GTHCCR）
		*/
		//-----------------------------------------------------------------//
		struct gthccr_t : public rw16_t<0x000C2006> {
			typedef rw16_t<0x000C2006> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCHW0;
			bits_rw_t<io_, bitpos::B2, 2>  CCHW1;
			bits_rw_t<io_, bitpos::B4, 2>  CCHW2;
			bits_rw_t<io_, bitpos::B6, 2>  CCHW3;
			bit_rw_t< io_, bitpos::B8>     CCSW0;
			bit_rw_t< io_, bitpos::B9>     CCSW1;
			bit_rw_t< io_, bitpos::B10>    CCSW2;
			bit_rw_t< io_, bitpos::B11>    CCSW3;
		};
		static gthccr_t GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
		*/
		//-----------------------------------------------------------------//
		struct gthssr_t : public rw16_t<0x000C2008> {
			typedef rw16_t<0x000C2008> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHSL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHSL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHSL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHSL3;
		};
		static gthssr_t GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ / クリア要因セレクトレジスタ（GTHPSR）
		*/
		//-----------------------------------------------------------------//
		struct gthpsr_t : public rw16_t<0x000C200A> {
			typedef rw16_t<0x000C200A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHPL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHPL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHPL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHPL3;
		};
		static gthpsr_t GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		struct gtwp_t : public rw16_t<0x000C200C> {
			typedef rw16_t<0x000C200C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   WP0;
			bit_rw_t<io_, bitpos::B1>   WP1;
			bit_rw_t<io_, bitpos::B2>   WP2;
			bit_rw_t<io_, bitpos::B3>   WP3;
		};
		static gtwp_t GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
		*/
		//-----------------------------------------------------------------//
		struct gtsync_t : public rw16_t<0x000C200E> {
			typedef rw16_t<0x000C200E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  SYNC0;
			bits_rw_t<io_, bitpos::B4,  2>  SYNC1;
			bits_rw_t<io_, bitpos::B8,  2>  SYNC2;
			bits_rw_t<io_, bitpos::B12, 2>  SYNC3;
		};
		static gtsync_t GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
		*/
		//-----------------------------------------------------------------//
		struct gtetint_t : public rw16_t<0x000C2010> {
			typedef rw16_t<0x000C2010> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      ETIPEN;
			bit_rw_t< io_, bitpos::B1>      ETINEN;
			bits_rw_t<io_, bitpos::B13, 2>  GTENFCS;
			bit_rw_t< io_, bitpos::B15>     GTETRGEN;
		};
		static gtetint_t GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
		*/
		//-----------------------------------------------------------------//
		struct gtbdr_t : public rw16_t<0x000C2014> {
			typedef rw16_t<0x000C2014> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>    BD00;
			bit_rw_t<io_, bitpos::B1>    BD01;
			bit_rw_t<io_, bitpos::B2>    BD02;
			bit_rw_t<io_, bitpos::B3>    BD03;
			bit_rw_t<io_, bitpos::B4>    BD10;
			bit_rw_t<io_, bitpos::B5>    BD11;
			bit_rw_t<io_, bitpos::B6>    BD12;
			bit_rw_t<io_, bitpos::B7>    BD13;
			bit_rw_t<io_, bitpos::B8>    BD20;
			bit_rw_t<io_, bitpos::B9>    BD21;
			bit_rw_t<io_, bitpos::B10>   BD22;
			bit_rw_t<io_, bitpos::B11>   BD23;
			bit_rw_t<io_, bitpos::B12>   BD30;
			bit_rw_t<io_, bitpos::B13>   BD31;
			bit_rw_t<io_, bitpos::B14>   BD32;
			bit_rw_t<io_, bitpos::B15>   BD33;
		};
		static gtbdr_t GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		struct gtswp_t : public rw16_t<0x000C2018> {
			typedef rw16_t<0x000C2018> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SWP0;
			bit_rw_t<io_, bitpos::B1>  SWP1;
			bit_rw_t<io_, bitpos::B2>  SWP2;
			bit_rw_t<io_, bitpos::B3>  SWP3;
		};
		static gtswp_t GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマクリア書き込み保護レジスタ（GTCWP）
		*/
		//-----------------------------------------------------------------//
		struct gtcwp_t : public rw16_t<0x000C201C> {
			typedef rw16_t<0x000C201C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CWP0;
			bit_rw_t<io_, bitpos::B1>  CWP1;
			bit_rw_t<io_, bitpos::B2>  CWP2;
			bit_rw_t<io_, bitpos::B3>  CWP3;
		};
		static gtcwp_t GTCWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ共通レジスタ書き込み保護レジスタ（GTCMNWP）
		*/
		//-----------------------------------------------------------------//
		struct gtcmnwp_t : public rw16_t<0x000C2020> {
			typedef rw16_t<0x000C2020> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMNWP;
		};
		static gtcmnwp_t GTCMNWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマモードレジスタ（GTMDR）
		*/
		//-----------------------------------------------------------------//
		struct gtmdr_t : public rw16_t<0x000C2024> {
			typedef rw16_t<0x000C2024> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LWA01;
			bit_rw_t<io_, bitpos::B1>  LWA23;
		};
		static gtmdr_t GTMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部クロックノイズフィルタコントロールレジスタ（GTECNFCR）
		*/
		//-----------------------------------------------------------------//
		struct gtecnfcr_t : public rw32_t<0x000C2028> {
			typedef rw32_t<0x000C2028> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      NFENECA;
			bit_rw_t< io_, bitpos::B1>      NFENECB;
			bit_rw_t< io_, bitpos::B2>      NFENECC;
			bit_rw_t< io_, bitpos::B3>      NFENECD;

			bit_rw_t< io_, bitpos::B8>      INVECA;
			bit_rw_t< io_, bitpos::B9>      INVECB;
			bit_rw_t< io_, bitpos::B10>     INVECC;
			bit_rw_t< io_, bitpos::B11>     INVECD;

			bits_rw_t<io_, bitpos::B16, 2>  NFCSECA;
			bits_rw_t<io_, bitpos::B18, 2>  NFCSECB;
			bits_rw_t<io_, bitpos::B20, 2>  NFCSECC;
			bits_rw_t<io_, bitpos::B22, 2>  NFCSECD;
		};
		static gtecnfcr_t GTECNFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ A/D 変換開始要求信号モニタレジスタ（GTADSMR）
		*/
		//-----------------------------------------------------------------//
		struct gtadsmr_t : public rw32_t<0x000C202C> {
			typedef rw32_t<0x000C202C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   ADSMS0;
			bit_rw_t< io_, bitpos::B8>      ADSMEN0;

			bits_rw_t<io_, bitpos::B16, 4>  ADSMS1;
			bit_rw_t< io_, bitpos::B24>     ADSMEN1;
		};
		static gtadsmr_t GTADSMR;
	};
	typedef gpt_t GPT;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ch		チャネル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, uint32_t ch>
	struct gptn_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ I/O コントロールレジスタ (GTIOR)
		*/
		//-----------------------------------------------------------------//
		struct gtior_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> GTIOA;
			bit_rw_t <io_, bitpos::B6>    OADFLT;
			bit_rw_t <io_, bitpos::B7>    OAHLD;
			bits_rw_t<io_, bitpos::B8, 6> GTIOB;
			bit_rw_t <io_, bitpos::B14>   OBDFLT;
			bit_rw_t <io_, bitpos::B15>   OBHLD;
		};
		static gtior_t GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ 割り込み出力設定レジスタ (GTINTAD)
		*/
		//-----------------------------------------------------------------//
		struct gtintad_t : public rw16_t<base + 0x02> {
			typedef rw16_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    GTINTA;
			bit_rw_t< io_, bitpos::B1>    GTINTB;
			bit_rw_t< io_, bitpos::B2>    GTINTC;
			bit_rw_t< io_, bitpos::B3>    GTINTD;
			bit_rw_t< io_, bitpos::B4>    GTINTE;
			bit_rw_t< io_, bitpos::B5>    GTINTF;
			bits_rw_t<io_, bitpos::B6, 2> GTINTPR;

			bit_rw_t< io_, bitpos::B11>   EINT;
			bit_rw_t< io_, bitpos::B12>   ADTRAUEN;
			bit_rw_t< io_, bitpos::B13>   ADTRADEN;
			bit_rw_t< io_, bitpos::B14>   ADTRBUEN;
			bit_rw_t< io_, bitpos::B15>   ADTRBDEN;
		};
		static gtintad_t GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコントロールレジスタ (GTCR)
		*/
		//-----------------------------------------------------------------//
		struct gtcr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  MD;
			bits_rw_t<io_, bitpos::B8, 4>  TPCS;
			bits_rw_t<io_, bitpos::B12, 2> CCLR;
		};
		static gtcr_t GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
		*/
		//-----------------------------------------------------------------//
		struct gtber_t : public rw16_t<base + 0x06> {
			typedef rw16_t<base + 0x06> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCRA;
			bits_rw_t<io_, bitpos::B2, 2>  CCRB;
			bits_rw_t<io_, bitpos::B4, 2>  PR;
			bit_rw_t< io_, bitpos::B6>     CCRSWT;
			bits_rw_t<io_, bitpos::B8, 2>  ADTTA;
			bit_rw_t< io_, bitpos::B10>    ADTDA;
			bits_rw_t<io_, bitpos::B12, 2> ADTTB;
			bit_rw_t< io_, bitpos::B14>    ADTDB;
		};
		static gtber_t GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウント方向レジスタ (GTUDC)
		*/
		//-----------------------------------------------------------------//
		struct gtudc_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     UD;
			bit_rw_t< io_, bitpos::B1>     UDF;
			bits_rw_t<io_, bitpos::B8, 2>  OADTY;
			bit_rw_t< io_, bitpos::B10>    OADTYF;
			bit_rw_t< io_, bitpos::B11>    OADTYR;
			bits_rw_t<io_, bitpos::B12, 2> OBDTY;
			bit_rw_t< io_, bitpos::B14>    OBDTYF;
			bit_rw_t< io_, bitpos::B15>    OBDTYR;
		};
		static gtudc_t GTUDC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ割り込み、A/D 変換開始要求間引き設定レジスタ (GTITC)
		*/
		//-----------------------------------------------------------------//
		struct gtitc_t : public rw16_t<base + 0x0A> {
			typedef rw16_t<base + 0x0A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     ITLA;
			bit_rw_t< io_, bitpos::B1>     ITLB;
			bit_rw_t< io_, bitpos::B2>     ITLC;
			bit_rw_t< io_, bitpos::B3>     ITLD;
			bit_rw_t< io_, bitpos::B4>     ITLE;
			bit_rw_t< io_, bitpos::B5>     ITLF;
			bits_rw_t<io_, bitpos::B6, 2 > IVTC;
			bits_rw_t<io_, bitpos::B8, 3 > IVTT;
			bit_rw_t< io_, bitpos::B12>    ADTAL;
			bit_rw_t< io_, bitpos::B14>    ADTBL;
		};
		static gtitc_t GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマステータスレジスタ (GTST)
		*/
		//-----------------------------------------------------------------//
		struct gtst_t : public rw16_t<base + 0x0C> {
			typedef rw16_t<base + 0x0C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> ITCNT;
			bit_rw_t< io_, bitpos::B11>   DTEF;
			bit_rw_t< io_, bitpos::B15>   TUCF;
		};
		static gtst_t GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x0E> GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマコンペアキャプチャレジスタ m（GTCCRm）（m = A ～ F）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x10> GTCCRA;
		static rw16_t<base + 0x12> GTCCRB;
		static rw16_t<base + 0x14> GTCCRC;
		static rw16_t<base + 0x16> GTCCRD;
		static rw16_t<base + 0x18> GTCCRE;
		static rw16_t<base + 0x1A> GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1C> GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1E> GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x20> GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスタｍ (GTADTRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x24> GTADTRA;
		static rw16_t<base + 0x2C> GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングバッファレジスタｍ (GTADTBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x26> GTADTBRA;
		static rw16_t<base + 0x2E> GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングダブルバッファレジスタｍ (GTADTDBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x28> GTADTDBRA;
		static rw16_t<base + 0x30> GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力ネゲートコントロールレジスタ (GTONCR)
		*/
		//-----------------------------------------------------------------//
		struct gtoncr_t : public rw16_t<base + 0x34> {
			typedef rw16_t<base + 0x34> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    NEA;
			bit_rw_t< io_, bitpos::B1>    NEB;
			bit_rw_t< io_, bitpos::B2>    NVA;
			bit_rw_t< io_, bitpos::B3>    NVB;
			bits_rw_t<io_, bitpos::B4, 4> NFS;
			bit_rw_t< io_, bitpos::B8>    NFV;

			bit_rw_t< io_, bitpos::B12>   SWN;

			bit_rw_t< io_, bitpos::B14>   OAE;
			bit_rw_t< io_, bitpos::B15>   OBE;
		};
		static gtoncr_t GTONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムコントロールレジスタ (GTDTCR)
		*/
		//-----------------------------------------------------------------//
		struct gtdtcr_t : public rw16_t<base + 0x36> {
			typedef rw16_t<base + 0x36> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>  TDE;
			bit_rw_t< io_, bitpos::B4>  TDBUE;
			bit_rw_t< io_, bitpos::B5>  TDBDE;
			bit_rw_t< io_, bitpos::B8>  TDFER;
		};
		static gtdtcr_t GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイム値レジスタｍ (GTDVm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x38> GTDVU;
		static rw16_t<base + 0x3A> GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムバッファレジスタｍ (GTDBm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x3C> GTDBU;
		static rw16_t<base + 0x3E> GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
		*/
		//-----------------------------------------------------------------//
		struct gtsos_t : public rw16_t<base + 0x40> {
			typedef rw16_t<base + 0x40> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SOS;
		};
		static gtsos_t GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
		*/
		//-----------------------------------------------------------------//
		struct gtsotr_t : public rw16_t<base + 0x42> {
			typedef rw16_t<base + 0x42> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SOTR;
		};
		static gtsos_t GTSOTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルを返す
			@return チャネル
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_chanel() { return ch; }
	};

	typedef gptn_t<0x000C2100, peripheral::GPT0, 0> GPT0;
	typedef gptn_t<0x000C2180, peripheral::GPT1, 1> GPT1;
	typedef gptn_t<0x000C2200, peripheral::GPT2, 2> GPT2;
	typedef gptn_t<0x000C2280, peripheral::GPT3, 3> GPT3;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 連結、定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gptl_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードカウンタレジスタ（GTCNTLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x00> GTCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマロングワードコンペアキャプチャレジスタ m（GTCCRmLW）（m = A ～ F）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x04> GTCCRALW;
		static rw32_t<base + 0x08> GTCCRBLW;
		static rw32_t<base + 0x0C> GTCCRCLW;
		static rw32_t<base + 0x10> GTCCRDLW;
		static rw32_t<base + 0x14> GTCCRELW;
		static rw32_t<base + 0x18> GTCCRFLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定レジスタ（GTPRLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x1C> GTPRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定バッファレジスタ（GTPBRLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x20> GTPBRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定ダブルバッファレジスタ（GTPDBRLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x24> GTPDBRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングレジスタ m（GTADTRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x28> GTADTRALW;
		static rw32_t<base + 0x34> GTADTRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングバッファレジスタ m（GTADTBRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x2C> GTADTBRALW;
		static rw32_t<base + 0x38> GTADTBRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングダブルバッファレジスタ m（GTADTDBRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x30> GTADTDBRALW;
		static rw32_t<base + 0x3C> GTADTDBRBLW;

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードデッドタイム値レジスタ m（GTDVmLW）（m = U, D）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x40> GTDVULW;
		static rw32_t<base + 0x44> GTDVDLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードデッドタイムバッファレジスタ m（GTDBmLW）（m = U, D）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x48> GTDBULW;
		static rw32_t<base + 0x4C> GTDBDLW;
#endif


	};

	typedef gptw_t<0x000C2000, peripheral::GPTW0> GPTW0;
	typedef gptw_t<0x000C2100, peripheral::GPTW1> GPTW1;
	typedef gptw_t<0x000C2200, peripheral::GPTW2> GPTW2;
	typedef gptw_t<0x000C2300, peripheral::GPTW3> GPTW3;
	typedef gptw_t<0x000C2400, peripheral::GPTW4> GPTW4;
	typedef gptw_t<0x000C2500, peripheral::GPTW5> GPTW5;
	typedef gptw_t<0x000C2600, peripheral::GPTW6> GPTW6;
	typedef gptw_t<0x000C2700, peripheral::GPTW7> GPTW7;
	typedef gptw_t<0x000C2800, peripheral::GPTW8> GPTW8;
	typedef gptw_t<0x000C2900, peripheral::GPTW9> GPTW9;
}
