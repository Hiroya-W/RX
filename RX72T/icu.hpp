#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・ICUC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/icu_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  割り込みコントローラ（ICUD）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR : uint8_t {
			NONE    = 0,	///< none 

			BUSERR  = 16,   ///< BSC

			RAMERR  = 18,	///< RAM

			FIFERR  = 21,   ///< FCU

			FRDYI   = 23,   ///< FCU

			SWINT2  = 26,   ///< ICU
			SWINT   = 27,   ///< ICU

			CMI0    = 28,   ///< CMT0
			CMI1    = 29,   ///< CMT1
			CMI2    = 30,   ///< CMT2
			CMI3    = 31,   ///< CMT3

			D0FIFO0 = 34,   ///< USB0
 			D1FIFO0 = 35,   ///< USB0

			SPRI0   = 38,   ///< RSPI0
			SPTI0   = 39,   ///< RSPI0

			RIIC_RXI0 = 52,   ///< RIIC0
			RIIC_TXI0 = 53,   ///< RIIC0

			RXI1    = 60,	///< SCI1
			TXI1    = 61,	///< SCI1

			IRQ0    = 64,   ///< ICU
			IRQ1    = 65,
			IRQ2    = 66,
			IRQ3    = 67,
			IRQ4    = 68,
			IRQ5    = 69,
			IRQ6    = 70,
			IRQ7    = 71,
			IRQ8    = 72,
			IRQ9    = 73,
			IRQ10   = 74,
			IRQ11   = 75,
			IRQ12   = 76,
			IRQ13   = 77,
			IRQ14   = 78,
			IRQ15   = 79,

			RXI5	= 84,	///< SCI5
			TXI5	= 85,	///< SCI5
			RXI6	= 86,	///< SCI6
			TXI6	= 87,	///< SCI6

			LVD1    = 88,   ///< LVD1
			LVD2    = 89,   ///< LVD2

			USBR0	= 90,	///< USB0

			IWUNI   = 95,   // IWDT
			WUNI	= 96,	// WDT

			RXI8	= 100,	///< SCI8
			TXI8	= 101,	///< SCI8
			RXI9	= 102,	///< SCI9
			TXI9	= 103,	///< SCI9

			GROUPBE0 = 106,	///< ICU

			GROUPBL0 = 110,	///< ICU
			GROUPBL1 = 111,	///< ICU
			GROUPAL0 = 112,	///< ICU

			RXI11	= 114,	///< SCI11
			TXI11	= 115,	///< SCI11
			RXI12	= 116,	///< SCI12
			TXI12	= 117,	///< SCI12

			DMAC0I  = 120,	///< DMAC
			DMAC1I  = 121,	///< DMAC
			DMAC2I  = 122,	///< DMAC
			DMAC3I  = 123,	///< DMAC
			DMAC74I = 124,	///< DMAC

			OSTDI   = 125,	///< OST

			S12ADI    = 128,  ///< S12AD
			S12GBADI  = 129,  ///< S12AD
			S12GCADI  = 130,  ///< S12AD

			S12ADI1   = 132,  ///< S12AD1
			S12GBADI1 = 133,  ///< S12AD1
			S12GCADI1 = 134,  ///< S12AD1

			S12ADI2   = 136,  ///< S12AD2
			S12GBADI2 = 137,  ///< S12AD2
			S12GCADI2 = 138,  ///< S12AD2

			CMIA0   = 146,	///< TMR0: CMIA0
			CMIB0   = 147,	///< TMR0: CMIB0
			OVI0    = 148,	///< TMR0: OVI0
			CMIA1   = 149,	///< TMR1: CMIA1
			CMIB1   = 150,	///< TMR1: CMIB1
			OVI1    = 151,	///< TMR1: OVI1
			CMIA2   = 152,	///< TMR2: CMIA2
			CMIB2   = 153,	///< TMR2: CMIB2
			OVI2    = 154,	///< TMR2: OVI2
			CMIA3   = 155,	///< TMR3: CMIA3
			CMIB3   = 156,	///< TMR3: CMIB3
			OVI3    = 157,	///< TMR3: OVI3
			CMIA4   = 158,	///< TMR4: CMIA4
			CMIB4   = 159,	///< TMR4: CMIB4
			OVI4    = 160,	///< TMR4: OVI4
			CMIA5   = 161,	///< TMR5: CMIA5
			CMIB5   = 162,	///< TMR5: CMIB5
			OVI5    = 163,	///< TMR5: OVI5
			CMIA6   = 164,	///< TMR6: CMIA6
			CMIB6   = 165,	///< TMR6: CMIB6
			OVI6    = 166,	///< TMR6: OVI6
			CMIA7   = 167,	///< TMR7: CMIA7
			CMIB7   = 168,	///< TMR7: CMIB7
			OVI7    = 169,	///< TMR7: OVI7

			RXF0    = 170,	///< CAN0
			TXF0    = 171,	///< CAN0
			RXM0    = 172,	///< CAN0
			TXM0    = 173,	///< CAN0

			USBI0	= 174,	///< USB0

			ELSR18I = 175,	///< ELC
			ELSR19I = 176,	///< ELC

			RD		= 177,	///< TSIP-Lite
			WR		= 178,	///< TSIP-Lite
			ERR		= 179,	///< TSIP-Lite

			CMPC0	= 180,	///< CMPC0
			CMPC1	= 181,	///< CMPC1
			CMPC2	= 182,	///< CMPC2
			CMPC3	= 183,	///< CMPC3
			CMPC4	= 184,	///< CMPC4
			CMPC5	= 185,	///< CMPC5

			INTA208 = 208,	///< PERIA
			INTA209 = 209,	///< PERIA
			INTA210 = 210,	///< PERIA
			INTA211 = 211,	///< PERIA
			INTA212 = 212,	///< PERIA
			INTA213 = 213,	///< PERIA
			INTA214 = 214,	///< PERIA
			INTA215 = 215,	///< PERIA
			INTA216 = 216,	///< PERIA
			INTA217 = 217,	///< PERIA
			INTA218 = 218,	///< PERIA
			INTA219 = 219,	///< PERIA
			INTA220 = 220,	///< PERIA
			INTA221 = 221,	///< PERIA
			INTA222 = 222,	///< PERIA
			INTA223 = 223,	///< PERIA
			INTA224 = 224,	///< PERIA
			INTA225 = 225,	///< PERIA
			INTA226 = 226,	///< PERIA
			INTA227 = 227,	///< PERIA
			INTA228 = 228,	///< PERIA
			INTA229 = 229,	///< PERIA
			INTA230 = 230,	///< PERIA
			INTA231 = 231,	///< PERIA
			INTA232 = 232,	///< PERIA
			INTA233 = 233,	///< PERIA
			INTA234 = 234,	///< PERIA
			INTA235 = 235,	///< PERIA
			INTA236 = 236,	///< PERIA
			INTA237 = 237,	///< PERIA
			INTA238 = 238,	///< PERIA
			INTA239 = 239,	///< PERIA
			INTA240 = 240,	///< PERIA
			INTA241 = 241,	///< PERIA
			INTA242 = 242,	///< PERIA
			INTA243 = 243,	///< PERIA
			INTA244 = 244,	///< PERIA
			INTA245 = 245,	///< PERIA
			INTA246 = 246,	///< PERIA
			INTA247 = 247,	///< PERIA
			INTA248 = 248,	///< PERIA
			INTA249 = 249,	///< PERIA
			INTA250 = 250,	///< PERIA
			INTA251 = 251,	///< PERIA
			INTA252 = 252,	///< PERIA
			INTA253 = 253,	///< PERIA
			INTA254 = 254,	///< PERIA
			INTA255 = 255	///< PERIA
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPIE0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_IE0 : uint8_t {
			DPFPUEX,	///< 倍精度浮動少数点例外
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBE0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BE0 : uint8_t {
			ERS0,	///< CAN0 / ERS0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL0 : uint8_t {
			TEI1 = 2,		///< SCI1 / TEI1（送信完了）
			ERI1,			///< SCI1 / ERI1（受信エラー）

			TEI5 = 10,		///< SCI5 / TEI5（送信完了）
			ERI5,			///< SCI5 / ERI5（受信エラー）
			TEI6,			///< SCI6 / TEI6（送信完了）
			ERI6,			///< SCI6 / ERI6（受信エラー）

			TEI12   = 16,	///< SCI12 / TEI12（送信完了）
			ERI12,			///< SCI12 / ERI12（受信エラー）
			SCIX0,			///< SCI12 / SCIX0
			SCIX1,			///< SCI12 / SCIX1
			SCIX2,			///< SCI12 / SCIX2
			SCIX3,			///< SCI12 / SCIX3

			FERRI   = 26,	///< CAC / FERRI
			MENDI,			///< CAC / MENDI
			OVFI,			///< CAC / OVFI
			DOPCI,			///< DOC / DOPCI
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPBL1・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_BL1 : uint8_t {
			POEGGAI,		///< POEG (group A)
			POEGGBI,		///< POEG (group B)
			POEGGCI,		///< POEG (group C)
			POEGGDI,		///< POEG (group C)

			OEI5 = 8,		///< POE / OEI5
			OEI1,			///< POE / OEI1
			OEI2,			///< POE / OEI2
			OEI3,			///< POE / OEI3
			OEI4,			///< POE / OEI4
			TEI0,			///< RIIC0 / TEI0
			EEI0,			///< RIIC0 / EEI0

			S12CMPAI2 = 18,	///< S12AD2 / S12CMPAI2
			S12CMPBI2,		///< S12AD2 / S12CMPBI2
			S12CMPAI,		///< S12AD / S12CMPAI
			S12CMPBI,		///< S12AD / S12CMPBI
			S12CMPAI1,		///< S12AD1 / S12CMPAI1
			S12CMPBI1,		///< S12AD1 / S12CMPBI1
			TEI8,			///< SCI8 / TEI8
			ERI8,			///< SCI8 / ERI8
			TEI9,			///< SCI9 / TEI9
			ERI9,			///< SCI9 / ERI9
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GROUPAL0・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_AL0 : uint8_t {
			TEI11 = 12,		///< SCI11 / TEI11
			ERI11,			///< SCI11 / ERI11

			SPII0 = 16,		///< RSPI0 / SPII0
			SPEI0,			///< RSPI0 / SPEI0
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込みＡ要因・ベクター・インデックス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class VECTOR_SELA : uint8_t {
			NONE = 0,	///< なし

			TGIA0 = 1,	///< MTU0（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB0,		///< MTU0（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC0,		///< MTU0（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID0,		///< MTU0（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV0,		///< MTU0（TCNTのオーバフロー）
			TGIE0,		///< MTU0（TGREのインプットキャプチャ /コンペアマッチ）
			TGIF0,		///< MTU0（TGRFのインプットキャプチャ /コンペアマッチ）

			TGIA1 = 8,	///< MTU1（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB1,		///< MTU1（TGRBのインプットキャプチャ /コンペアマッチ）
			TCIV1,		///< MTU1（TCNTのオーバフロー）
			TCIU1,		///< MTU1（TCNTのアンダフロー）

			TGIA2 = 12,	///< MTU2（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB2,		///< MTU2（TGRBのインプットキャプチャ /コンペアマッチ）
			TCIV2,		///< MTU2（TCNTのオーバフロー）
			TCIU2,		///< MTU2（TCNTのアンダフロー）

			TGIA3 = 16,	///< MTU3（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB3,		///< MTU3（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC3,		///< MTU3（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID3,		///< MTU3（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV3,		///< MTU3（TCNTのオーバフロー）

			TGIA4 = 21,	///< MTU4（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB4,		///< MTU4（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC4,		///< MTU4（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID4,		///< MTU4（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV4,		///< MTU4（TCNTのオーバフロー /アンダフロー（相補PWMモード時のみ））

			TGIU5 = 27,	///< MTU5（TGRUのインプットキャプチャ /コンペアマッチ）
			TGIV5,		///< MTU5（TGRVのインプットキャプチャ /コンペアマッチ）
			TGIW5,		///< MTU5（TGRWのインプットキャプチャ /コンペアマッチ）

			TGIA6 = 30,	///< MTU6（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB6,		///< MTU6（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC6,		///< MTU6（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID6,		///< MTU6（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV6,		///< MTU6（TCNTのオーバフロー）

			TGIA7 = 35,	///< MTU7（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB7,		///< MTU7（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC7,		///< MTU7（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID7,		///< MTU7（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV7,		///< MTU7（TCNTのオーバフロー /アンダフロー (相補PWMモード時のみ))

			TGIA8 = 41,	///< MTU8（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB8,		///< MTU8（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC8,		///< MTU8（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID8,		///< MTU8（TGRDのインプットキャプチャ /コンペアマッチ）
			TCIV8,		///< MTU8（TCNTのオーバフロー）

			TGIA9 = 47,	///< MTU9（TGRAのインプットキャプチャ /コンペアマッチ）
			TGIB9,		///< MTU9（TGRBのインプットキャプチャ /コンペアマッチ）
			TGIC9,		///< MTU9（TGRCのインプットキャプチャ /コンペアマッチ）
			TGID9,		///< MTU9（TGRDのインプットキャプチャ /コンペアマッチ）
			TGIV9,		///< MTU9（TCNTのオーバフロー）
			TGIE9,		///< MTU9 (TGREのコンペアマッチ)
			TGIF9,		///< MTU9 (TGRFのコンペアマッチ)

			GTCIA0 = 56,///< GPTW0 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB0,		///< GPTW0 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC0,		///< GPTW0 (GTCCRC レジスタのコンペアマッチ)
			GTCID0,		///< GPTW0 (GTCCRD レジスタのコンペアマッチ)
			GDTE0,		///< GPTW0 (デッドタイムエラー)
			GTCIE0,		///< GPTW0 (GTCCRE レジスタのコンペアマッチ)
			GTCIF0,		///< GPTW0 (GTCCRF レジスタのコンペアマッチ)
			GTCIV0,		///< GPTW0 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU0,		///< GPTW0 (GTCNT カウンタのアンダフロー)

			GTCIA1 = 65,///< GPTW1 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB1,		///< GPTW1 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC1,		///< GPTW1 (GTCCRC レジスタのコンペアマッチ)
			GTCID1,		///< GPTW1 (GTCCRD レジスタのコンペアマッチ)
			GDTE1,		///< GPTW1 (デッドタイムエラー)
			GTCIE1,		///< GPTW1 (GTCCRE レジスタのコンペアマッチ)
			GTCIF1,		///< GPTW1 (GTCCRF レジスタのコンペアマッチ)
			GTCIV1,		///< GPTW1 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU1,		///< GPTW1 (GTCNT カウンタのアンダフロー)

			GTCIA2 = 74,///< GPTW2 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB2,		///< GPTW2 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC2,		///< GPTW2 (GTCCRC レジスタのコンペアマッチ)
			GTCID2,		///< GPTW2 (GTCCRD レジスタのコンペアマッチ)
			GDTE2,		///< GPTW2 (デッドタイムエラー)
			GTCIE2,		///< GPTW2 (GTCCRE レジスタのコンペアマッチ)
			GTCIF2,		///< GPTW2 (GTCCRF レジスタのコンペアマッチ)
			GTCIV2,		///< GPTW2 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU2,		///< GPTW2 (GTCNT カウンタのアンダフロー)

			GTCIA3 = 83,///< GPTW3 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB3,		///< GPTW3 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC3,		///< GPTW3 (GTCCRC レジスタのコンペアマッチ)
			GTCID3,		///< GPTW3 (GTCCRD レジスタのコンペアマッチ)
			GDTE3,		///< GPTW3 (デッドタイムエラー)
			GTCIE3,		///< GPTW3 (GTCCRE レジスタのコンペアマッチ)
			GTCIF3,		///< GPTW3 (GTCCRF レジスタのコンペアマッチ)
			GTCIV3,		///< GPTW3 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU3,		///< GPTW3 (GTCNT カウンタのアンダフロー)

			GTCIA4 = 92,///< GPTW4 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB4,		///< GPTW4 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC4,		///< GPTW4 (GTCCRC レジスタのコンペアマッチ)
			GTCID4,		///< GPTW4 (GTCCRD レジスタのコンペアマッチ)
			GDTE4,		///< GPTW4 (デッドタイムエラー)
			GTCIE4,		///< GPTW4 (GTCCRE レジスタのコンペアマッチ)
			GTCIF4,		///< GPTW4 (GTCCRF レジスタのコンペアマッチ)
			GTCIV4,		///< GPTW4 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU4,		///< GPTW4 (GTCNT カウンタのアンダフロー)

			GTCIA5 =101,///< GPTW5 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB5,		///< GPTW5 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC5,		///< GPTW5 (GTCCRC レジスタのコンペアマッチ)
			GTCID5,		///< GPTW5 (GTCCRD レジスタのコンペアマッチ)
			GDTE5,		///< GPTW5 (デッドタイムエラー)
			GTCIE5,		///< GPTW5 (GTCCRE レジスタのコンペアマッチ)
			GTCIF5,		///< GPTW5 (GTCCRF レジスタのコンペアマッチ)
			GTCIV5,		///< GPTW5 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU5,		///< GPTW5 (GTCNT カウンタのアンダフロー)

			GTCIA6 =110,///< GPTW6 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB6,		///< GPTW6 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC6,		///< GPTW6 (GTCCRC レジスタのコンペアマッチ)
			GTCID6,		///< GPTW6 (GTCCRD レジスタのコンペアマッチ)
			GDTE6,		///< GPTW6 (デッドタイムエラー)
			GTCIE6,		///< GPTW6 (GTCCRE レジスタのコンペアマッチ)
			GTCIF6,		///< GPTW6 (GTCCRF レジスタのコンペアマッチ)
			GTCIV6,		///< GPTW6 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU6,		///< GPTW6 (GTCNT カウンタのアンダフロー)

			GTCIA7 =119,///< GPTW7 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB7,		///< GPTW7 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC7,		///< GPTW7 (GTCCRC レジスタのコンペアマッチ)
			GTCID7,		///< GPTW7 (GTCCRD レジスタのコンペアマッチ)
			GDTE7,		///< GPTW7 (デッドタイムエラー)
			GTCIE7,		///< GPTW7 (GTCCRE レジスタのコンペアマッチ)
			GTCIF7,		///< GPTW7 (GTCCRF レジスタのコンペアマッチ)
			GTCIV7,		///< GPTW7 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU7,		///< GPTW7 (GTCNT カウンタのアンダフロー)

			GTCIA8 =128,///< GPTW8 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB8,		///< GPTW8 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC8,		///< GPTW8 (GTCCRC レジスタのコンペアマッチ)
			GTCID8,		///< GPTW8 (GTCCRD レジスタのコンペアマッチ)
			GDTE8,		///< GPTW8 (デッドタイムエラー)
			GTCIE8,		///< GPTW8 (GTCCRE レジスタのコンペアマッチ)
			GTCIF8,		///< GPTW8 (GTCCRF レジスタのコンペアマッチ)
			GTCIV8,		///< GPTW8 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU8,		///< GPTW8 (GTCNT カウンタのアンダフロー)

			GTCIA9 =137,///< GPTW9 (GTCCRA レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIB9,		///< GPTW9 (GTCCRB レジスタのインプットキャプチャ / コンペアマッチ)
			GTCIC9,		///< GPTW9 (GTCCRC レジスタのコンペアマッチ)
			GTCID9,		///< GPTW9 (GTCCRD レジスタのコンペアマッチ)
			GDTE9,		///< GPTW9 (デッドタイムエラー)
			GTCIE9,		///< GPTW9 (GTCCRE レジスタのコンペアマッチ)
			GTCIF9,		///< GPTW9 (GTCCRF レジスタのコンペアマッチ)
			GTCIV9,		///< GPTW9 (GTCNT カウンタのオーバフロー (GTPR レジスタのコンペアマッチ))
			GTCIU9,		///< GPTW9 (GTCNT カウンタのアンダフロー)

			NONE2 = 255,///< 割り込み選択なし
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター IE0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_IE0 ivec) noexcept {
			return VECTOR::GROUPIE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BL0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL0 ivec) noexcept {
			return VECTOR::GROUPBL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BL1 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BL1 ivec) noexcept {
			return VECTOR::GROUPBL1;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター BE0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_BE0 ivec) noexcept {
			return VECTOR::GROUPBE0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループベクター AL0 の取得
			@param[in]	VEC		グループベクター型
			@return グループベクター
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static VECTOR get_group_vector(VECTOR_AL0 ivec) noexcept {
			return VECTOR::GROUPAL0;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IR レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ir_t {

			rw8_t<base + 16> BUSERR;
			rw8_t<base + 17> GROUPIE0;
			rw8_t<base + 18> RAMERR;

			rw8_t<base + 21> FIFERR;

			rw8_t<base + 23> FRDYI;

			rw8_t<base + 26> SWINT2;
			rw8_t<base + 27> SWINT;
			rw8_t<base + 28> CMI0;
			rw8_t<base + 29> CMI1;
			rw8_t<base + 30> CMI2;
			rw8_t<base + 31> CMI3;

			rw8_t<base + 34> D0FIFO0;	///< USB0
			rw8_t<base + 35> D1FIFO0;	///< USB0

			rw8_t<base + 38> SPRI0;		///< RSPI0 Rx
			rw8_t<base + 39> SPTI0;		///< RSPI0 Tx
			rw8_t<base + 40> SPRI1;		///< RSPI1 Rx
			rw8_t<base + 41> SPTI1;		///< RSPI1 Tx
			rw8_t<base + 42> SPRI;		///< QSPI Rx
			rw8_t<base + 43> SPTI;		///< QSPI Tx
			rw8_t<base + 44> SBFAI;		///< SDHI
			rw8_t<base + 45> MBFAI;		///< MMCIF
			rw8_t<base + 46> SSITXI0;	///< SSIE0 Tx
			rw8_t<base + 47> SSIRXI0;	///< SSIE0 Rx
			rw8_t<base + 48> SSIRTI1;	///< SSIE1 Rx/Tx

			rw8_t<base + 50> RIIC_RXI1;	///< RIIC1 Rx
			rw8_t<base + 51> RIIC_TXI1;	///< RIIC1 Tx
			rw8_t<base + 52> RIIC_RXI0;	///< RIIC0 Rx
			rw8_t<base + 53> RIIC_TXI0;	///< RIIC0 Tx
			rw8_t<base + 54> RIIC_RXI2;	///< RIIC2 Rx
			rw8_t<base + 55> RIIC_TXI2;	///< RIIC2 Tx

			rw8_t<base + 58> RXI0;		///< SCI0 Rx
			rw8_t<base + 59> TXI0;		///< SCI0 Tx
			rw8_t<base + 60> RXI1;		///< SCI1 Rx
			rw8_t<base + 61> TXI1;		///< SCI1 Tx
			rw8_t<base + 62> RXI2;		///< SCI2 Rx
			rw8_t<base + 63> TXI2;		///< SCI2 Tx

			rw8_t<base + 64> IRQ0;
			rw8_t<base + 65> IRQ1;
			rw8_t<base + 66> IRQ2;
			rw8_t<base + 67> IRQ3;
			rw8_t<base + 68> IRQ4;
			rw8_t<base + 69> IRQ5;
			rw8_t<base + 70> IRQ6;
			rw8_t<base + 71> IRQ7;
			rw8_t<base + 72> IRQ8;
			rw8_t<base + 73> IRQ9;
			rw8_t<base + 74> IRQ10;
			rw8_t<base + 75> IRQ11;
			rw8_t<base + 76> IRQ12;
			rw8_t<base + 77> IRQ13;
			rw8_t<base + 78> IRQ14;
			rw8_t<base + 79> IRQ15;
			rw8_t<base + 80> RXI3;		///< SCI3 Rx
			rw8_t<base + 81> TXI3;		///< SCI3 Tx
			rw8_t<base + 82> RXI4;		///< SCI4 Rx
			rw8_t<base + 83> TXI4;		///< SCI4 Tx
			rw8_t<base + 84> RXI5;		///< SCI5 Rx
			rw8_t<base + 85> TXI5;		///< SCI5 Tx
			rw8_t<base + 86> RXI6;		///< SCI6 Rx
			rw8_t<base + 87> TXI6;		///< SCI6 Tx
			rw8_t<base + 88> LVD1;		///< LVD1
			rw8_t<base + 89> LVD2;		///< LVD2
			rw8_t<base + 90> USBR0;		///< USB0

			rw8_t<base + 92> ALM;		///< RTC
			rw8_t<base + 93> PRD;		///< RTC

			rw8_t<base + 95> IWUNI;		///< IWDT
			rw8_t<base + 96> WUNI;		///< IWDT
			rw8_t<base + 97> PCDFI;		///< PDC
			rw8_t<base + 98> RXI7;		///< SCI7 Rx
			rw8_t<base + 99> TXI7;		///< SCI7 Tx
			rw8_t<base + 100> RXI8;		///< SCI8 Rx
			rw8_t<base + 101> TXI8;		///< SCI8 Tx
			rw8_t<base + 102> RXI9;		///< SCI9 Rx
			rw8_t<base + 103> TXI9;		///< SCI9 Tx
			rw8_t<base + 104> RXI10;	///< SCI10 Rx
			rw8_t<base + 105> TXI10;	///< SCI10 Tx
			rw8_t<base + 106> GROUPBE0;	///< ICU
			rw8_t<base + 107> GROUPBL2;	///< ICU
			rw8_t<base + 108> SPRI2;	///< RSPI2 Rx
			rw8_t<base + 109> SPTI2;	///< RSPI2 Tx
			rw8_t<base + 110> GROUPBL0;	///< ICU
			rw8_t<base + 111> GROUPBL1;	///< ICU
			rw8_t<base + 112> GROUPAL0;	///< ICU
			rw8_t<base + 113> GROUPAL1;	///< ICU
			rw8_t<base + 114> RXI11;	///< SCI11 Rx
			rw8_t<base + 115> TXI11;	///< SCI11 Tx
			rw8_t<base + 116> RXI12;	///< SCI12 Rx
			rw8_t<base + 117> TXI12;	///< SCI12 Tx

			rw8_t<base + 120> DMAC0I;	///< DMAC
			rw8_t<base + 121> DMAC1I;	///< DMAC
			rw8_t<base + 122> DMAC2I;	///< DMAC
			rw8_t<base + 123> DMAC3I;	///< DMAC
			rw8_t<base + 124> DMAC74I;	///< DMAC
			rw8_t<base + 125> OSTDI;	///< OST
			rw8_t<base + 126> EXDMAC0I;	///< EXDMAC
			rw8_t<base + 127> EXDMAC1I;	///< EXDMAC
			rw8_t<base + 128> INTB128;
			rw8_t<base + 129> INTB129;
			rw8_t<base + 130> INTB130;
			rw8_t<base + 131> INTB131;
			rw8_t<base + 132> INTB132;
			rw8_t<base + 133> INTB133;
			rw8_t<base + 134> INTB134;
			rw8_t<base + 135> INTB135;
			rw8_t<base + 136> INTB136;
			rw8_t<base + 137> INTB137;
			rw8_t<base + 138> INTB138;
			rw8_t<base + 139> INTB139;
			rw8_t<base + 140> INTB140;
			rw8_t<base + 141> INTB141;
			rw8_t<base + 142> INTB142;
			rw8_t<base + 143> INTB143;
			rw8_t<base + 144> INTB144;
			rw8_t<base + 145> INTB145;
			rw8_t<base + 146> INTB146;
			rw8_t<base + 147> INTB147;
			rw8_t<base + 148> INTB148;
			rw8_t<base + 149> INTB149;
			rw8_t<base + 150> INTB150;
			rw8_t<base + 151> INTB151;
			rw8_t<base + 152> INTB152;
			rw8_t<base + 153> INTB153;
			rw8_t<base + 154> INTB154;
			rw8_t<base + 155> INTB155;
			rw8_t<base + 156> INTB156;
			rw8_t<base + 157> INTB157;
			rw8_t<base + 158> INTB158;
			rw8_t<base + 159> INTB159;
			rw8_t<base + 160> INTB160;
			rw8_t<base + 161> INTB161;
			rw8_t<base + 162> INTB162;
			rw8_t<base + 163> INTB163;
			rw8_t<base + 164> INTB164;
			rw8_t<base + 165> INTB165;
			rw8_t<base + 166> INTB166;
			rw8_t<base + 167> INTB167;
			rw8_t<base + 168> INTB168;
			rw8_t<base + 169> INTB169;
			rw8_t<base + 170> INTB170;
			rw8_t<base + 171> INTB171;
			rw8_t<base + 172> INTB172;
			rw8_t<base + 173> INTB173;
			rw8_t<base + 174> INTB174;
			rw8_t<base + 175> INTB175;
			rw8_t<base + 176> INTB176;
			rw8_t<base + 177> INTB177;
			rw8_t<base + 178> INTB178;
			rw8_t<base + 179> INTB179;
			rw8_t<base + 180> INTB180;
			rw8_t<base + 181> INTB181;
			rw8_t<base + 182> INTB182;
			rw8_t<base + 183> INTB183;
			rw8_t<base + 184> INTB184;
			rw8_t<base + 185> INTB185;
			rw8_t<base + 186> INTB186;
			rw8_t<base + 187> INTB187;
			rw8_t<base + 188> INTB188;
			rw8_t<base + 189> INTB189;
			rw8_t<base + 190> INTB190;
			rw8_t<base + 191> INTB191;
			rw8_t<base + 192> INTB192;
			rw8_t<base + 193> INTB193;
			rw8_t<base + 194> INTB194;
			rw8_t<base + 195> INTB195;
			rw8_t<base + 196> INTB196;
			rw8_t<base + 197> INTB197;
			rw8_t<base + 198> INTB198;
			rw8_t<base + 199> INTB199;
			rw8_t<base + 200> INTB200;
			rw8_t<base + 201> INTB201;
			rw8_t<base + 202> INTB202;
			rw8_t<base + 203> INTB203;
			rw8_t<base + 204> INTB204;
			rw8_t<base + 205> INTB205;
			rw8_t<base + 206> INTB206;
			rw8_t<base + 207> INTB207;

			rw8_t<base + 208> INTA208;
			rw8_t<base + 209> INTA209;
			rw8_t<base + 210> INTA210;
			rw8_t<base + 211> INTA211;
			rw8_t<base + 212> INTA212;
			rw8_t<base + 213> INTA213;
			rw8_t<base + 214> INTA214;
			rw8_t<base + 215> INTA215;
			rw8_t<base + 216> INTA216;
			rw8_t<base + 217> INTA217;
			rw8_t<base + 218> INTA218;
			rw8_t<base + 219> INTA219;
			rw8_t<base + 220> INTA220;
			rw8_t<base + 221> INTA221;
			rw8_t<base + 222> INTA222;
			rw8_t<base + 223> INTA223;
			rw8_t<base + 224> INTA224;
			rw8_t<base + 225> INTA225;
			rw8_t<base + 226> INTA226;
			rw8_t<base + 227> INTA227;
			rw8_t<base + 228> INTA228;
			rw8_t<base + 229> INTA229;
			rw8_t<base + 230> INTA230;
			rw8_t<base + 231> INTA231;
			rw8_t<base + 232> INTA232;
			rw8_t<base + 233> INTA233;
			rw8_t<base + 234> INTA234;
			rw8_t<base + 235> INTA235;
			rw8_t<base + 236> INTA236;
			rw8_t<base + 237> INTA237;
			rw8_t<base + 238> INTA238;
			rw8_t<base + 239> INTA239;
			rw8_t<base + 240> INTA240;
			rw8_t<base + 241> INTA241;
			rw8_t<base + 242> INTA242;
			rw8_t<base + 243> INTA243;
			rw8_t<base + 244> INTA244;
			rw8_t<base + 245> INTA245;
			rw8_t<base + 246> INTA246;
			rw8_t<base + 247> INTA247;
			rw8_t<base + 248> INTA248;
			rw8_t<base + 249> INTA249;
			rw8_t<base + 250> INTA250;
			rw8_t<base + 251> INTA251;
			rw8_t<base + 252> INTA252;
			rw8_t<base + 253> INTA253;
			rw8_t<base + 254> INTA254;
			rw8_t<base + 255> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		typedef ir_t<0x00087000> IR_;
		static IR_ IR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IER レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ier_t {
			typedef rw8_t<base + 0x02> ier02;
			bit_rw_t<ier02, bitpos::B0>	BUSERR;
			bit_rw_t<ier02, bitpos::B1>	GROUPIE0;
			bit_rw_t<ier02, bitpos::B2>	RAMERR;

			bit_rw_t<ier02, bitpos::B5>	FIFERR;

			bit_rw_t<ier02, bitpos::B7>	FRDYI;

			typedef rw8_t<base + 0x03> ier03;
			bit_rw_t<ier03, bitpos::B2>	SWINT2;
			bit_rw_t<ier03, bitpos::B3>	SWINT;
			bit_rw_t<ier03, bitpos::B4>	CMI0;
			bit_rw_t<ier03, bitpos::B5>	CMI1;
			bit_rw_t<ier03, bitpos::B6>	CMI2;
			bit_rw_t<ier03, bitpos::B7>	CMI3;

			typedef rw8_t<base + 0x04> ier04;
			bit_rw_t<ier04, bitpos::B2>	D0FIFO0;	///< USB0
			bit_rw_t<ier04, bitpos::B3>	D1FIFO0;	///< USB0

			bit_rw_t<ier04, bitpos::B6>	SPRI0;		///< RSPI0 Rx
			bit_rw_t<ier04, bitpos::B7>	SPTI0;		///< RSPI0 Tx

			typedef rw8_t<base + 0x05> ier05;
			bit_rw_t<ier05, bitpos::B0>	SPRI1;		///< RSPI1 Rx
			bit_rw_t<ier05, bitpos::B1>	SPTI1;		///< RSPI1 Tx
			bit_rw_t<ier05, bitpos::B2>	SPRI;		///< QSPI Rx
			bit_rw_t<ier05, bitpos::B3>	SPTI;		///< QSPI Tx
			bit_rw_t<ier05, bitpos::B4>	SBFAI;		///< SDHI
			bit_rw_t<ier05, bitpos::B5>	MBFAI;		///< MMCIF
			bit_rw_t<ier05, bitpos::B6>	SSITXI0;	///< SSIE0 Tx
			bit_rw_t<ier05, bitpos::B7>	SSIRXI0;	///< SSIE0 Rx

			typedef rw8_t<base + 0x06> ier06;
			bit_rw_t<ier06, bitpos::B0>	SSIRTI1;	///< SSIE1 Rx/Tx

			bit_rw_t<ier06, bitpos::B2>	RIIC_RXI1;	///< RIIC1 Rx
			bit_rw_t<ier06, bitpos::B3>	RIIC_TXI1;	///< RIIC1 Tx
			bit_rw_t<ier06, bitpos::B4>	RIIC_RXI0;	///< RIIC0 Rx
			bit_rw_t<ier06, bitpos::B5>	RIIC_TXI0;	///< RIIC0 Tx
			bit_rw_t<ier06, bitpos::B6>	RIIC_RXI2;	///< RIIC2 Rx
			bit_rw_t<ier06, bitpos::B7>	RIIC_TXI2;	///< RIIC2 Rx

			typedef rw8_t<base + 0x07> ier07;
			bit_rw_t<ier07, bitpos::B2>	RXI0;		///< SCI0 Rx
			bit_rw_t<ier07, bitpos::B3>	TXI0;		///< SCI0 Tx
			bit_rw_t<ier07, bitpos::B4>	RXI1;		///< SCI1 Rx
			bit_rw_t<ier07, bitpos::B5>	TXI1;		///< SCI1 Tx
			bit_rw_t<ier07, bitpos::B6>	RXI2;		///< SCI2 Rx
			bit_rw_t<ier07, bitpos::B7>	TXI2;		///< SCI2 Tx

			typedef rw8_t<base + 0x08> ier08;
			bit_rw_t<ier08, bitpos::B0>	IRQ0;
			bit_rw_t<ier08, bitpos::B1>	IRQ1;
			bit_rw_t<ier08, bitpos::B2>	IRQ2;
			bit_rw_t<ier08, bitpos::B3>	IRQ3;
			bit_rw_t<ier08, bitpos::B4>	IRQ4;
			bit_rw_t<ier08, bitpos::B5>	IRQ5;
			bit_rw_t<ier08, bitpos::B6>	IRQ6;
			bit_rw_t<ier08, bitpos::B7>	IRQ7;

			typedef rw8_t<base + 0x09> ier09;
			bit_rw_t<ier09, bitpos::B0>	IRQ8;
			bit_rw_t<ier09, bitpos::B1>	IRQ9;
			bit_rw_t<ier09, bitpos::B2>	IRQ10;
			bit_rw_t<ier09, bitpos::B3>	IRQ11;
			bit_rw_t<ier09, bitpos::B4>	IRQ12;
			bit_rw_t<ier09, bitpos::B5>	IRQ13;
			bit_rw_t<ier09, bitpos::B6>	IRQ14;
			bit_rw_t<ier09, bitpos::B7>	IRQ15;

			typedef rw8_t<base + 0x0A> ier0A;
			bit_rw_t<ier0A, bitpos::B0>	RXI3;		///< SCI3 Rx
			bit_rw_t<ier0A, bitpos::B1>	TXI3;		///< SCI3 Tx
			bit_rw_t<ier0A, bitpos::B2>	RXI4;		///< SCI4 Rx
			bit_rw_t<ier0A, bitpos::B3>	TXI4;		///< SCI4 Tx
			bit_rw_t<ier0A, bitpos::B4>	RXI5;		///< SCI5 Rx
			bit_rw_t<ier0A, bitpos::B5>	TXI5;		///< SCI5 Tx
			bit_rw_t<ier0A, bitpos::B6>	RXI6;		///< SCI6 Rx
			bit_rw_t<ier0A, bitpos::B7>	TXI6;		///< SCI6 Tx

			typedef rw8_t<base + 0x0B> ier0B;
			bit_rw_t<ier0B, bitpos::B0>	LVD1;		///< LVD1
			bit_rw_t<ier0B, bitpos::B1>	LVD2;		///< LVD2
			bit_rw_t<ier0B, bitpos::B2>	USBR0;		///< USB0

			bit_rw_t<ier0B, bitpos::B4>	ALM;		///< RTC
			bit_rw_t<ier0B, bitpos::B5>	PRD;		///< RTC

			bit_rw_t<ier0B, bitpos::B7>	IWUNI;		///< IWDT

			typedef rw8_t<base + 0x0C> ier0C;
			bit_rw_t<ier0C, bitpos::B0>	WUIN;		///< WDT
			bit_rw_t<ier0C, bitpos::B1>	PCDFI;		///< PDC
			bit_rw_t<ier0C, bitpos::B2>	RXI7;		///< SCI7 Rx
			bit_rw_t<ier0C, bitpos::B3>	TXI7;		///< SCI7 Tx
			bit_rw_t<ier0C, bitpos::B4>	RXI8;		///< SCI8 Rx
			bit_rw_t<ier0C, bitpos::B5>	TXI8;		///< SCI8 Tx
			bit_rw_t<ier0C, bitpos::B6>	RXI9;		///< SCI9 Rx
			bit_rw_t<ier0C, bitpos::B7>	TXI9;		///< SCI9 Tx

			typedef rw8_t<base + 0x0D> ier0D;
			bit_rw_t<ier0D, bitpos::B0>	RXI10;		///< SCI10 Rx
			bit_rw_t<ier0D, bitpos::B1>	TXI10;		///< SCI10 Tx
			bit_rw_t<ier0D, bitpos::B2>	GROUPBE0;	///< ICU
			bit_rw_t<ier0D, bitpos::B3>	GROUPBL2;	///< ICU
			bit_rw_t<ier0D, bitpos::B4>	SPRI2;		///< RSPI2 Rx
			bit_rw_t<ier0D, bitpos::B5>	SPTI2;		///< RSPI2 Tx
			bit_rw_t<ier0D, bitpos::B6>	GROUPBL0;	///< ICU
			bit_rw_t<ier0D, bitpos::B7>	GROUPBL1;	///< ICU

			typedef rw8_t<base + 0x0E> ier0E;
			bit_rw_t<ier0E, bitpos::B0>	GROUPAL0;	///< ICU
			bit_rw_t<ier0E, bitpos::B1> GROUPAL1;	///< ICU
			bit_rw_t<ier0E, bitpos::B2>	RXI11;		///< SCI11 Rx
			bit_rw_t<ier0E, bitpos::B3>	TXI11;		///< SCI11 Tx
			bit_rw_t<ier0E, bitpos::B4> RXI12;		///< SCI12 Rx
			bit_rw_t<ier0E, bitpos::B5> TXI12;		///< SCI12 Tx

			typedef rw8_t<base + 0x0F> ier0F;
			bit_rw_t<ier0F, bitpos::B0> DMAC0I;		///< DMAC
			bit_rw_t<ier0F, bitpos::B1> DMAC1I;		///< DMAC
			bit_rw_t<ier0F, bitpos::B2> DMAC2I;		///< DMAC
			bit_rw_t<ier0F, bitpos::B3> DMAC3I;		///< DMAC
			bit_rw_t<ier0F, bitpos::B4> DMAC74I;	///< DMAC
			bit_rw_t<ier0F, bitpos::B5> OSTDI;		///< OST
			bit_rw_t<ier0F, bitpos::B6> EXDMAC0I;	///< EXDMAC
			bit_rw_t<ier0F, bitpos::B7> EXDMAC1I;	///< EXDMAC

			typedef rw8_t<base + 0x10> ier10;
			bit_rw_t<ier10, bitpos::B0> INTB128;
			bit_rw_t<ier10, bitpos::B1> INTB129;
			bit_rw_t<ier10, bitpos::B2> INTB130;
			bit_rw_t<ier10, bitpos::B3> INTB131;
			bit_rw_t<ier10, bitpos::B4> INTB132;
			bit_rw_t<ier10, bitpos::B5> INTB133;
			bit_rw_t<ier10, bitpos::B6> INTB134;
			bit_rw_t<ier10, bitpos::B7> INTB135;


			typedef rw8_t<base + 0x1A> ier1A;
			bit_rw_t<ier1A, bitpos::B0> INTA208;
			bit_rw_t<ier1A, bitpos::B1> INTA209;
			bit_rw_t<ier1A, bitpos::B2> INTA210;
			bit_rw_t<ier1A, bitpos::B3> INTA211;
			bit_rw_t<ier1A, bitpos::B4> INTA212;
			bit_rw_t<ier1A, bitpos::B5> INTA213;
			bit_rw_t<ier1A, bitpos::B6> INTA214;
			bit_rw_t<ier1A, bitpos::B7> INTA215;
			typedef rw8_t<base + 0x1B> ier1B;
			bit_rw_t<ier1B, bitpos::B0> INTA216;
			bit_rw_t<ier1B, bitpos::B1> INTA217;
			bit_rw_t<ier1B, bitpos::B2> INTA218;
			bit_rw_t<ier1B, bitpos::B3> INTA219;
			bit_rw_t<ier1B, bitpos::B4> INTA220;
			bit_rw_t<ier1B, bitpos::B5> INTA221;
			bit_rw_t<ier1B, bitpos::B6> INTA222;
			bit_rw_t<ier1B, bitpos::B7> INTA223;
			typedef rw8_t<base + 0x1C> ier1C;
			bit_rw_t<ier1C, bitpos::B0> INTA224;
			bit_rw_t<ier1C, bitpos::B1> INTA225;
			bit_rw_t<ier1C, bitpos::B2> INTA226;
			bit_rw_t<ier1C, bitpos::B3> INTA227;
			bit_rw_t<ier1C, bitpos::B4> INTA228;
			bit_rw_t<ier1C, bitpos::B5> INTA229;
			bit_rw_t<ier1C, bitpos::B6> INTA230;
			bit_rw_t<ier1C, bitpos::B7> INTA231;
			typedef rw8_t<base + 0x1D> ier1D;
			bit_rw_t<ier1D, bitpos::B0> INTA232;
			bit_rw_t<ier1D, bitpos::B1> INTA233;
			bit_rw_t<ier1D, bitpos::B2> INTA234;
			bit_rw_t<ier1D, bitpos::B3> INTA235;
			bit_rw_t<ier1D, bitpos::B4> INTA236;
			bit_rw_t<ier1D, bitpos::B5> INTA237;
			bit_rw_t<ier1D, bitpos::B6> INTA238;
			bit_rw_t<ier1D, bitpos::B7> INTA239;
			typedef rw8_t<base + 0x1E> ier1E;
			bit_rw_t<ier1E, bitpos::B0> INTA240;
			bit_rw_t<ier1E, bitpos::B1> INTA241;
			bit_rw_t<ier1E, bitpos::B2> INTA242;
			bit_rw_t<ier1E, bitpos::B3> INTA243;
			bit_rw_t<ier1E, bitpos::B4> INTA244;
			bit_rw_t<ier1E, bitpos::B5> INTA245;
			bit_rw_t<ier1E, bitpos::B6> INTA246;
			bit_rw_t<ier1E, bitpos::B7> INTA247;
			typedef rw8_t<base + 0x1F> ier1F;
			bit_rw_t<ier1F, bitpos::B0> INTA248;
			bit_rw_t<ier1F, bitpos::B1> INTA249;
			bit_rw_t<ier1F, bitpos::B2> INTA250;
			bit_rw_t<ier1F, bitpos::B3> INTA251;
			bit_rw_t<ier1F, bitpos::B4> INTA252;
			bit_rw_t<ier1F, bitpos::B5> INTA253;
			bit_rw_t<ier1F, bitpos::B6> INTA254;
			bit_rw_t<ier1F, bitpos::B7> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  許可、不許可
				@param[in]	vec		割り込みベクター
				@param[in]	ena		許可／不許可
			*/
			//-------------------------------------------------------------//
			void enable(VECTOR vec, bool ena) noexcept
			{
				auto idx = static_cast<uint8_t>(vec);
				auto tmp = rd8_(base + (idx >> 3));
				if(ena) {
					tmp |=   1 << (idx & 7);
				} else {
					tmp &= ~(1 << (idx & 7));
				}
				wr8_(base + (idx >> 3), tmp);
			}


			//-------------------------------------------------------------//
			/*!
				@brief  許可状態を取得
				@param[in]	vec		割り込みベクター
				@return 許可状態（許可の場合「true」）
			*/
			//-------------------------------------------------------------//
			bool get(VECTOR vec) const noexcept
			{
				auto idx = static_cast<uint8_t>(vec);
				auto tmp = rd8_(base + (idx >> 3));
				return tmp & (1 << (idx & 7));
			}
		};
		typedef ier_t<0x00087200> IER_;
		static IER_ IER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPR レジスタ @n
					全て、下位４ビットが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ipr_t {
			rw8_t<base + 0> BUSERR;
			rw8_t<base + 0> GROUPIE0;
			rw8_t<base + 0> RAMERR;

			rw8_t<base + 1> FIFERR;
			rw8_t<base + 2> FRDYI;

			rw8_t<base + 3> SWINT2;
			rw8_t<base + 3> SWINT;
			rw8_t<base + 4> CMI0;
			rw8_t<base + 5> CMI1;
			rw8_t<base + 6> CMI2;
			rw8_t<base + 7> CMI3;

			rw8_t<base + 34> D0FIFO0;	///< USB0
			rw8_t<base + 35> D1FIFO0;	///< USB0

			rw8_t<base + 38> SPRI0;		///< RSPI0 Rx
			rw8_t<base + 39> SPTI0;		///< RSPI0 Tx
			rw8_t<base + 40> SPRI1;		///< RSPI1 Rx
			rw8_t<base + 41> SPTI1;		///< RSPI1 Tx
			rw8_t<base + 42> SPRI;		///< QSPI Rx
			rw8_t<base + 43> SPTI;		///< QSPI Tx
			rw8_t<base + 44> SBFAI;		///< SDHI
			rw8_t<base + 45> MBFAI;		///< MMCIF 
			rw8_t<base + 46> SSITXI0;	///< SSIE0 Tx
			rw8_t<base + 47> SSIRXI0;	///< SSIE0 Rx
			rw8_t<base + 48> SSIRTI1;	///< SSIE1 Rx/Tx

			rw8_t<base + 50> RIIC_RXI1;	///< RIIC1 Rx
			rw8_t<base + 51> RIIC_TXI1;	///< RIIC1 Tx
			rw8_t<base + 52> RIIC_RXI0;	///< RIIC0 Rx
			rw8_t<base + 53> RIIC_TXI0;	///< RIIC0 Tx
			rw8_t<base + 54> RIIC_RXI2;	///< RIIC2 Rx
			rw8_t<base + 55> RIIC_TXI2;	///< RIIC2 Tx

			rw8_t<base + 58> RXI0;		///< SCI0 Rx
			rw8_t<base + 59> TXI0;		///< SCI0 Tx
			rw8_t<base + 60> RXI1;		///< SCI1 Rx
			rw8_t<base + 61> TXI1;		///< SCI1 Tx
			rw8_t<base + 62> RXI2;		///< SCI2 Rx
			rw8_t<base + 63> TXI2;		///< SCI2 Tx
			rw8_t<base + 64> IRQ0;
			rw8_t<base + 65> IRQ1;
			rw8_t<base + 66> IRQ2;
			rw8_t<base + 67> IRQ3;
			rw8_t<base + 68> IRQ4;
			rw8_t<base + 69> IRQ5;
			rw8_t<base + 70> IRQ6;
			rw8_t<base + 71> IRQ7;
			rw8_t<base + 72> IRQ8;
			rw8_t<base + 73> IRQ9;
			rw8_t<base + 74> IRQ10;
			rw8_t<base + 75> IRQ11;
			rw8_t<base + 76> IRQ12;
			rw8_t<base + 77> IRQ13;
			rw8_t<base + 78> IRQ14;
			rw8_t<base + 79> IRQ15;
			rw8_t<base + 80> RXI3;		///< SCI3 Rx
			rw8_t<base + 81> TXI3;		///< SCI3 Tx
			rw8_t<base + 82> RXI4;		///< SCI4 Rx
			rw8_t<base + 83> TXI4;		///< SCI4 Tx
			rw8_t<base + 84> RXI5;		///< SCI5 Rx
			rw8_t<base + 85> TXI5;		///< SCI5 Tx
			rw8_t<base + 86> RXI6;		///< SCI6 Rx
			rw8_t<base + 87> TXI6;		///< SCI6 Tx
			rw8_t<base + 88> LVD1;		///< LVD1
			rw8_t<base + 89> LVD2;		///< LVD2
			rw8_t<base + 89> USBR0;		///< USB0

			rw8_t<base + 92> ALM;		///< RTC
			rw8_t<base + 93> PRD;		///< RTC

			rw8_t<base + 95> IWUNI;		///< IWDT
			rw8_t<base + 96> WUNI;		///< WDT
			rw8_t<base + 97> PCDFI;		///< PDC
			rw8_t<base + 98> RXI7;		///< SCI7 Rx
			rw8_t<base + 99> TXI7;		///< SCI7 Tx
			rw8_t<base + 100> RXI8;		///< SCI8 Rx
			rw8_t<base + 101> TXI8;		///< SCI8 Tx
			rw8_t<base + 102> RXI9;		///< SCI9 Rx
			rw8_t<base + 103> TXI9;		///< SCI9 Tx
			rw8_t<base + 104> RXI10;	///< SCI10 Rx
			rw8_t<base + 105> TXI10;	///< SCI10 Tx
			rw8_t<base + 106> GROUPBE0;	///< ICU
			rw8_t<base + 107> GROUPBL2;	///< ICU
			rw8_t<base + 108> SPRI2;	///< RSPI2 Rx
			rw8_t<base + 109> SPTI2;	///< RSPI2 Tx
			rw8_t<base + 110> GROUPBL0;	///< ICU
			rw8_t<base + 111> GROUPBL1;	///< ICU
			rw8_t<base + 112> GROUPAL0;	///< ICU
			rw8_t<base + 113> GROUPAL1;	///< ICU
			rw8_t<base + 114> RXI11;	///< SCI11 Rx
			rw8_t<base + 115> TXI11;	///< SCI11 Tx
			rw8_t<base + 116> RXI12;	///< SCI12 Rx
			rw8_t<base + 117> TXI12;	///< SCI12 Tx

			rw8_t<base + 120> DMAC0I;	///< DMAC
			rw8_t<base + 121> DMAC1I;	///< DMAC
			rw8_t<base + 122> DMAC2I;	///< DMAC
			rw8_t<base + 123> DMAC3I;	///< DMAC
			rw8_t<base + 124> DMAC74I;	///< DMAC
			rw8_t<base + 125> OSTDI;	///< OST
			rw8_t<base + 126> EXDMAC0I;	///< EXDMAC
			rw8_t<base + 127> EXDMAC1I;	///< EXDMAC
			rw8_t<base + 128> INTB128;
			rw8_t<base + 129> INTB129;
			rw8_t<base + 130> INTB130;
			rw8_t<base + 131> INTB131;
			rw8_t<base + 132> INTB132;
			rw8_t<base + 133> INTB133;
			rw8_t<base + 134> INTB134;
			rw8_t<base + 135> INTB135;
			rw8_t<base + 136> INTB136;
			rw8_t<base + 137> INTB137;
			rw8_t<base + 138> INTB138;
			rw8_t<base + 139> INTB139;
			rw8_t<base + 140> INTB140;
			rw8_t<base + 141> INTB141;
			rw8_t<base + 142> INTB142;
			rw8_t<base + 143> INTB143;
			rw8_t<base + 144> INTB144;
			rw8_t<base + 145> INTB145;
			rw8_t<base + 146> INTB146;
			rw8_t<base + 147> INTB147;
			rw8_t<base + 148> INTB148;
			rw8_t<base + 149> INTB149;
			rw8_t<base + 150> INTB150;

			rw8_t<base + 208> INTA208;
			rw8_t<base + 209> INTA209;
			rw8_t<base + 210> INTA210;
			rw8_t<base + 211> INTA211;
			rw8_t<base + 212> INTA212;
			rw8_t<base + 213> INTA213;
			rw8_t<base + 214> INTA214;
			rw8_t<base + 215> INTA215;
			rw8_t<base + 216> INTA216;
			rw8_t<base + 217> INTA217;
			rw8_t<base + 218> INTA218;
			rw8_t<base + 219> INTA219;
			rw8_t<base + 220> INTA220;
			rw8_t<base + 221> INTA221;
			rw8_t<base + 222> INTA222;
			rw8_t<base + 223> INTA223;
			rw8_t<base + 224> INTA224;
			rw8_t<base + 225> INTA225;
			rw8_t<base + 226> INTA226;
			rw8_t<base + 227> INTA227;
			rw8_t<base + 228> INTA228;
			rw8_t<base + 229> INTA229;
			rw8_t<base + 230> INTA230;
			rw8_t<base + 231> INTA231;
			rw8_t<base + 232> INTA232;
			rw8_t<base + 233> INTA233;
			rw8_t<base + 234> INTA234;
			rw8_t<base + 235> INTA235;
			rw8_t<base + 236> INTA236;
			rw8_t<base + 237> INTA237;
			rw8_t<base + 238> INTA238;
			rw8_t<base + 239> INTA239;
			rw8_t<base + 240> INTA240;
			rw8_t<base + 241> INTA241;
			rw8_t<base + 242> INTA242;
			rw8_t<base + 243> INTA243;
			rw8_t<base + 244> INTA244;
			rw8_t<base + 245> INTA245;
			rw8_t<base + 246> INTA246;
			rw8_t<base + 247> INTA247;
			rw8_t<base + 248> INTA248;
			rw8_t<base + 249> INTA249;
			rw8_t<base + 250> INTA250;
			rw8_t<base + 251> INTA251;
			rw8_t<base + 252> INTA252;
			rw8_t<base + 253> INTA253;
			rw8_t<base + 254> INTA254;
			rw8_t<base + 255> INTA255;


			//-------------------------------------------------------------//
			/*!
				@brief  []オペレータ
				@param[in]	vec		割り込みベクター
				@return IR レジスターの参照
			*/
			//-------------------------------------------------------------//
			volatile uint8_t& operator [] (VECTOR vec) {
				return *reinterpret_cast<volatile uint8_t*>(base + static_cast<uint8_t>(vec));
			}
		};
		typedef ipr_t<0x00087300> IPR_;
		static IPR_ IPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因選択レジスタ m（DMRSRm）（m = DMAC チャネル番号）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087400> DMRSR0_;
		static DMRSR0_ DMRSR0;
		typedef rw8_t<0x00087404> DMRSR1_;
		static DMRSR1_ DMRSR1;
		typedef rw8_t<0x00087408> DMRSR2_;
		static DMRSR2_ DMRSR2;
		typedef rw8_t<0x0008740C> DMRSR3_;
		static DMRSR3_ DMRSR3;
		typedef rw8_t<0x00087410> DMRSR4_;
		static DMRSR4_ DMRSR4;
		typedef rw8_t<0x00087414> DMRSR5_;
		static DMRSR5_ DMRSR5;
		typedef rw8_t<0x00087418> DMRSR6_;
		static DMRSR6_ DMRSR6;
		typedef rw8_t<0x0008741C> DMRSR7_;
		static DMRSR7_ DMRSR7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ コントロールレジスタ i（IRQCRi）（i = 0 ～ 15）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  IRQMD;
		};
		static irqcr_t<0x00087500>  IRQCR0;
		static irqcr_t<0x00087501>  IRQCR1;
		static irqcr_t<0x00087502>  IRQCR2;
		static irqcr_t<0x00087503>  IRQCR3;
		static irqcr_t<0x00087504>  IRQCR4;
		static irqcr_t<0x00087505>  IRQCR5;
		static irqcr_t<0x00087506>  IRQCR6;
		static irqcr_t<0x00087507>  IRQCR7;
		static irqcr_t<0x00087508>  IRQCR8;
		static irqcr_t<0x00087509>  IRQCR9;
		static irqcr_t<0x0008750A>  IRQCR10;
		static irqcr_t<0x0008750B>  IRQCR11;
		static irqcr_t<0x0008750C>  IRQCR12;
		static irqcr_t<0x0008750D>  IRQCR13;
		static irqcr_t<0x0008750E>  IRQCR14;
		static irqcr_t<0x0008750F>  IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 0（IRQFLTE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN0;
			bit_rw_t<io_, bitpos::B1> FLTEN1;
			bit_rw_t<io_, bitpos::B2> FLTEN2;
			bit_rw_t<io_, bitpos::B3> FLTEN3;
			bit_rw_t<io_, bitpos::B4> FLTEN4;
			bit_rw_t<io_, bitpos::B5> FLTEN5;
			bit_rw_t<io_, bitpos::B6> FLTEN6;
			bit_rw_t<io_, bitpos::B7> FLTEN7;
		};
		static irqflte0_t<0x00087520> IRQFLTE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 1（IRQFLTE1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN8;
			bit_rw_t<io_, bitpos::B1> FLTEN9;
			bit_rw_t<io_, bitpos::B2> FLTEN10;
			bit_rw_t<io_, bitpos::B3> FLTEN11;
			bit_rw_t<io_, bitpos::B4> FLTEN12;
			bit_rw_t<io_, bitpos::B5> FLTEN13;
			bit_rw_t<io_, bitpos::B6> FLTEN14;
			bit_rw_t<io_, bitpos::B7> FLTEN15;
		};
		static irqflte1_t<0x00087521> IRQFLTE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 0（IRQFLTC0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL0;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL1;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL2;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL3;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL4;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL5;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL6;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL7;
		};
		static irqfltc0_t<0x00087528> IRQFLTC0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 1（IRQFLTC1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL8;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL9;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL10;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL11;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL12;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL13;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL14;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL15;
		};
		static irqfltc1_t<0x0008752A> IRQFLTC1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct grp_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>  IS0;
			bit_ro_t <io_, bitpos::B1>  IS1;
			bit_ro_t <io_, bitpos::B2>  IS2;
			bit_ro_t <io_, bitpos::B3>  IS3;
			bit_ro_t <io_, bitpos::B4>  IS4;
			bit_ro_t <io_, bitpos::B5>  IS5;
			bit_ro_t <io_, bitpos::B6>  IS6;
			bit_ro_t <io_, bitpos::B7>  IS7;

			bit_ro_t <io_, bitpos::B8>  IS8;
			bit_ro_t <io_, bitpos::B9>  IS9;
			bit_ro_t <io_, bitpos::B10> IS10;
			bit_ro_t <io_, bitpos::B11> IS11;
			bit_ro_t <io_, bitpos::B12> IS12;
			bit_ro_t <io_, bitpos::B13> IS13;
			bit_ro_t <io_, bitpos::B14> IS14;
			bit_ro_t <io_, bitpos::B15> IS15;

			bit_ro_t <io_, bitpos::B16> IS16;
			bit_ro_t <io_, bitpos::B17> IS17;
			bit_ro_t <io_, bitpos::B18> IS18;
			bit_ro_t <io_, bitpos::B19> IS19;
			bit_ro_t <io_, bitpos::B20> IS20;
			bit_ro_t <io_, bitpos::B21> IS21;
			bit_ro_t <io_, bitpos::B22> IS22;
			bit_ro_t <io_, bitpos::B23> IS23;

			bit_ro_t <io_, bitpos::B24> IS24;
			bit_ro_t <io_, bitpos::B25> IS25;
			bit_ro_t <io_, bitpos::B26> IS26;
			bit_ro_t <io_, bitpos::B27> IS27;
			bit_ro_t <io_, bitpos::B28> IS28;
			bit_ro_t <io_, bitpos::B29> IS29;
			bit_ro_t <io_, bitpos::B30> IS30;
			bit_ro_t <io_, bitpos::B31> IS31;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求レジスタ（GRPBE0）@n
					グループ BL0/1 割り込み要求レジスタ（GRPBL0/GRPBL1）@n
					グループ AL0/1 割り込み要求レジスタ（GRPAL0/GRPAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef grp_t<0x00087600> GRPBE0_;
		static GRPBE0_ GRPBE0;
		typedef grp_t<0x00087630> GRPBL0_;
		static GRPBL0_ GRPBL0;
		typedef grp_t<0x00087634> GRPBL1_;
		static GRPBL1_ GRPBL1;
		typedef grp_t<0x00087830> GRPAL0_;
		static GRPAL0_ GRPAL0;
		typedef grp_t<0x00087834> GRPAL1_;
		static GRPAL1_ GRPAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求許可レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct gen_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EN0;
			bit_rw_t<io_, bitpos::B1>  EN1;
			bit_rw_t<io_, bitpos::B2>  EN2;
			bit_rw_t<io_, bitpos::B3>  EN3;
			bit_rw_t<io_, bitpos::B4>  EN4;
			bit_rw_t<io_, bitpos::B5>  EN5;
			bit_rw_t<io_, bitpos::B6>  EN6;
			bit_rw_t<io_, bitpos::B7>  EN7;

			bit_rw_t<io_, bitpos::B8>  EN8;
			bit_rw_t<io_, bitpos::B9>  EN9;
			bit_rw_t<io_, bitpos::B10> EN10;
			bit_rw_t<io_, bitpos::B11> EN11;
			bit_rw_t<io_, bitpos::B12> EN12;
			bit_rw_t<io_, bitpos::B13> EN13;
			bit_rw_t<io_, bitpos::B14> EN14;
			bit_rw_t<io_, bitpos::B15> EN15;

			bit_rw_t<io_, bitpos::B16> EN16;
			bit_rw_t<io_, bitpos::B17> EN17;
			bit_rw_t<io_, bitpos::B18> EN18;
			bit_rw_t<io_, bitpos::B19> EN19;
			bit_rw_t<io_, bitpos::B20> EN20;
			bit_rw_t<io_, bitpos::B21> EN21;
			bit_rw_t<io_, bitpos::B22> EN22;
			bit_rw_t<io_, bitpos::B23> EN23;

			bit_rw_t<io_, bitpos::B24> EN24;
			bit_rw_t<io_, bitpos::B25> EN25;
			bit_rw_t<io_, bitpos::B26> EN26;
			bit_rw_t<io_, bitpos::B27> EN27;
			bit_rw_t<io_, bitpos::B28> EN28;
			bit_rw_t<io_, bitpos::B29> EN29;
			bit_rw_t<io_, bitpos::B30> EN30;
			bit_rw_t<io_, bitpos::B31> EN31;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込み要求許可レジスタ（GENBE0）@n
					グループ BL0/1 割り込み要求許可レジスタ（GENBL0/GENBL1/GENBL2）@n
					グループ AL0/1 割り込み要求許可レジスタ（GENAL0/GENAL1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef gen_t<0x00087640> GENBE0_;
		static GENBE0_ GENBE0;
		typedef gen_t<0x00087670> GENBL0_;
		static GENBL0_ GENBL0;
		typedef gen_t<0x00087674> GENBL1_;
		static GENBL1_ GENBL1;
		typedef gen_t<0x00087870> GENAL0_;
		static GENAL0_ GENAL0;
		typedef gen_t<0x00087874> GENAL1_;
		static GENAL1_ GENAL1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ BE0 割り込みクリアレジスタ（GCRBE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct gcrbe0_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CLR0;
			bit_rw_t <io_, bitpos::B1>  CLR1;
			bit_rw_t <io_, bitpos::B2>  CLR2;
			bit_rw_t <io_, bitpos::B3>  CLR3;
			bit_rw_t <io_, bitpos::B4>  CLR4;
			bit_rw_t <io_, bitpos::B5>  CLR5;
			bit_rw_t <io_, bitpos::B6>  CLR6;
			bit_rw_t <io_, bitpos::B7>  CLR7;

			bit_rw_t <io_, bitpos::B8>  CLR8;
			bit_rw_t <io_, bitpos::B9>  CLR9;
			bit_rw_t <io_, bitpos::B10> CLR10;
			bit_rw_t <io_, bitpos::B11> CLR11;
			bit_rw_t <io_, bitpos::B12> CLR12;
			bit_rw_t <io_, bitpos::B13> CLR13;
			bit_rw_t <io_, bitpos::B14> CLR14;
			bit_rw_t <io_, bitpos::B15> CLR15;

			bit_rw_t <io_, bitpos::B16> CLR16;
			bit_rw_t <io_, bitpos::B17> CLR17;
			bit_rw_t <io_, bitpos::B18> CLR18;
			bit_rw_t <io_, bitpos::B19> CLR19;
			bit_rw_t <io_, bitpos::B20> CLR20;
			bit_rw_t <io_, bitpos::B21> CLR21;
			bit_rw_t <io_, bitpos::B22> CLR22;
			bit_rw_t <io_, bitpos::B23> CLR23;

			bit_rw_t <io_, bitpos::B24> CLR24;
			bit_rw_t <io_, bitpos::B25> CLR25;
			bit_rw_t <io_, bitpos::B26> CLR26;
			bit_rw_t <io_, bitpos::B27> CLR27;
			bit_rw_t <io_, bitpos::B28> CLR28;
			bit_rw_t <io_, bitpos::B29> CLR29;
			bit_rw_t <io_, bitpos::B30> CLR30;
			bit_rw_t <io_, bitpos::B31> CLR31;
		};
		typedef gcrbe0_t<0x00087680> GCRBE0_;
		static GCRBE0_ GCRBE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み要求レジスタ
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pixr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PIR0;
			bit_rw_t <io_, bitpos::B1>  PIR1;
			bit_rw_t <io_, bitpos::B2>  PIR2;
			bit_rw_t <io_, bitpos::B3>  PIR3;
			bit_rw_t <io_, bitpos::B4>  PIR4;
			bit_rw_t <io_, bitpos::B5>  PIR5;
			bit_rw_t <io_, bitpos::B6>  PIR6;
			bit_rw_t <io_, bitpos::B7>  PIR7;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要求レジスタ k（PIARk）（k = 0h ～ Bh）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pixr_t<0x00087900> PIAR0_;
		static PIAR0_ PIAR0;
		typedef pixr_t<0x00087901> PIAR1_;
		static PIAR1_ PIAR1;
		typedef pixr_t<0x00087902> PIAR2_;
		static PIAR2_ PIAR2;
		typedef pixr_t<0x00087903> PIAR3_;
		static PIAR3_ PIAR3;
		typedef pixr_t<0x00087904> PIAR4_;
		static PIAR4_ PIAR4;
		typedef pixr_t<0x00087905> PIAR5_;
		static PIAR5_ PIAR5;
		typedef pixr_t<0x00087906> PIAR6_;
		static PIAR6_ PIAR6;
		typedef pixr_t<0x00087907> PIAR7_;
		static PIAR7_ PIAR7;
		typedef pixr_t<0x00087908> PIAR8_;
		static PIAR8_ PIAR8;
		typedef pixr_t<0x00087909> PIAR9_;
		static PIAR9_ PIAR9;
		typedef pixr_t<0x0008790A> PIARA_;
		static PIARA_ PIARA;
		typedef pixr_t<0x0008790B> PIARB_;
		static PIARB_ PIARB;
		typedef pixr_t<0x0008790C> PIARC_;
		static PIARC_ PIARC;
		typedef pixr_t<0x0008790D> PIARD_;
		static PIARD_ PIARD;
		typedef pixr_t<0x0008790E> PIARE_;
		static PIARE_ PIARE;
		typedef pixr_t<0x0008790F> PIARF_;
		static PIARF_ PIARF;
		typedef pixr_t<0x00087910> PIAR10_;
		static PIAR10_ PIAR10;
		typedef pixr_t<0x00087911> PIAR11_;
		static PIAR11_ PIAR11;
		typedef pixr_t<0x00087912> PIAR12_;
		static PIAR12_ PIAR12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要因選択レジスタ n（SLIARn）（n = 208 ～ 255）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef icu_utils::slixr_t<0x00087900, VECTOR, VECTOR_SELA> SLIAR_;
		static SLIAR_ SLIAR;
#if 0
		static rw8_t<0x000879D0> SLIAR208;
		static rw8_t<0x000879D1> SLIAR209;
		static rw8_t<0x000879D2> SLIAR210;
		static rw8_t<0x000879D3> SLIAR211;
		static rw8_t<0x000879D4> SLIAR212;
		static rw8_t<0x000879D5> SLIAR213;
		static rw8_t<0x000879D6> SLIAR214;
		static rw8_t<0x000879D7> SLIAR215;
		static rw8_t<0x000879D8> SLIAR216;
		static rw8_t<0x000879D9> SLIAR217;
		static rw8_t<0x000879DA> SLIAR218;
		static rw8_t<0x000879DB> SLIAR219;
		static rw8_t<0x000879DC> SLIAR220;
		static rw8_t<0x000879DD> SLIAR221;
		static rw8_t<0x000879DE> SLIAR222;
		static rw8_t<0x000879DF> SLIAR223;

		static rw8_t<0x000879E0> SLIAR224;
		static rw8_t<0x000879E1> SLIAR225;
		static rw8_t<0x000879E2> SLIAR226;
		static rw8_t<0x000879E3> SLIAR227;
		static rw8_t<0x000879E4> SLIAR228;
		static rw8_t<0x000879E5> SLIAR229;
		static rw8_t<0x000879E6> SLIAR230;
		static rw8_t<0x000879E7> SLIAR231;
		static rw8_t<0x000879E8> SLIAR232;
		static rw8_t<0x000879E9> SLIAR233;
		static rw8_t<0x000879EA> SLIAR234;
		static rw8_t<0x000879EB> SLIAR235;
		static rw8_t<0x000879EC> SLIAR236;
		static rw8_t<0x000879ED> SLIAR237;
		static rw8_t<0x000879EE> SLIAR238;
		static rw8_t<0x000879EF> SLIAR239;

		static rw8_t<0x000879F0> SLIAR240;
		static rw8_t<0x000879F1> SLIAR241;
		static rw8_t<0x000879F2> SLIAR242;
		static rw8_t<0x000879F3> SLIAR243;
		static rw8_t<0x000879F4> SLIAR244;
		static rw8_t<0x000879F5> SLIAR245;
		static rw8_t<0x000879F6> SLIAR246;
		static rw8_t<0x000879F7> SLIAR247;
		static rw8_t<0x000879F8> SLIAR248;
		static rw8_t<0x000879F9> SLIAR249;
		static rw8_t<0x000879FA> SLIAR250;
		static rw8_t<0x000879FB> SLIAR251;
		static rw8_t<0x000879FC> SLIAR252;
		static rw8_t<0x000879FD> SLIAR253;
		static rw8_t<0x000879FE> SLIAR254;
		static rw8_t<0x000879FF> SLIAR255;
#endif
	};
	typedef icu_t<void> ICU;

	template<class _> typename icu_t<_>::IR_ icu_t<_>::IR;
	template<class _> typename icu_t<_>::IER_ icu_t<_>::IER;
	template<class _> typename icu_t<_>::IPR_ icu_t<_>::IPR;

	template<class _> typename icu_t<_>::DMRSR0_ icu_t<_>::DMRSR0;
	template<class _> typename icu_t<_>::DMRSR1_ icu_t<_>::DMRSR1;
	template<class _> typename icu_t<_>::DMRSR2_ icu_t<_>::DMRSR2;
	template<class _> typename icu_t<_>::DMRSR3_ icu_t<_>::DMRSR3;
	template<class _> typename icu_t<_>::DMRSR4_ icu_t<_>::DMRSR4;
	template<class _> typename icu_t<_>::DMRSR5_ icu_t<_>::DMRSR5;
	template<class _> typename icu_t<_>::DMRSR6_ icu_t<_>::DMRSR6;
	template<class _> typename icu_t<_>::DMRSR7_ icu_t<_>::DMRSR7;

	template<class _> typename icu_t<_>::GRPBE0_ icu_t<_>::GRPBE0;
	template<class _> typename icu_t<_>::GRPBL0_ icu_t<_>::GRPBL0;
	template<class _> typename icu_t<_>::GRPBL1_ icu_t<_>::GRPBL1;
	template<class _> typename icu_t<_>::GRPAL0_ icu_t<_>::GRPAL0;
	template<class _> typename icu_t<_>::GRPAL1_ icu_t<_>::GRPAL1;

	template<class _> typename icu_t<_>::GENBE0_ icu_t<_>::GENBE0;
	template<class _> typename icu_t<_>::GENBL0_ icu_t<_>::GENBL0;
	template<class _> typename icu_t<_>::GENBL1_ icu_t<_>::GENBL1;
	template<class _> typename icu_t<_>::GENAL0_ icu_t<_>::GENAL0;
	template<class _> typename icu_t<_>::GENAL1_ icu_t<_>::GENAL1;

	template<class _> typename icu_t<_>::GCRBE0_ icu_t<_>::GCRBE0;

	template<class _> typename icu_t<_>::PIAR0_ icu_t<_>::PIAR0;
	template<class _> typename icu_t<_>::PIAR1_ icu_t<_>::PIAR1;
	template<class _> typename icu_t<_>::PIAR2_ icu_t<_>::PIAR2;
	template<class _> typename icu_t<_>::PIAR3_ icu_t<_>::PIAR3;
	template<class _> typename icu_t<_>::PIAR4_ icu_t<_>::PIAR4;
	template<class _> typename icu_t<_>::PIAR5_ icu_t<_>::PIAR5;
	template<class _> typename icu_t<_>::PIAR6_ icu_t<_>::PIAR6;
	template<class _> typename icu_t<_>::PIAR7_ icu_t<_>::PIAR7;
	template<class _> typename icu_t<_>::PIAR8_ icu_t<_>::PIAR8;
	template<class _> typename icu_t<_>::PIAR9_ icu_t<_>::PIAR9;
	template<class _> typename icu_t<_>::PIARA_ icu_t<_>::PIARA;
	template<class _> typename icu_t<_>::PIARB_ icu_t<_>::PIARB;
	template<class _> typename icu_t<_>::PIARC_ icu_t<_>::PIARC;
	template<class _> typename icu_t<_>::PIARD_ icu_t<_>::PIARD;
	template<class _> typename icu_t<_>::PIARE_ icu_t<_>::PIARE;
	template<class _> typename icu_t<_>::PIARF_ icu_t<_>::PIARF;
	template<class _> typename icu_t<_>::PIAR10_ icu_t<_>::PIAR10;
	template<class _> typename icu_t<_>::PIAR11_ icu_t<_>::PIAR11;
	template<class _> typename icu_t<_>::PIAR12_ icu_t<_>::PIAR12;

	template<class _> typename icu_t<_>::SLIAR_ icu_t<_>::SLIAR;
}
