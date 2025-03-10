#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ペリフェラル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016,2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ペリフェラル種別
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint16_t {

		CAC,	///< クロック周波数精度測定回路

		DTC,	///< データトランスファコントローラ

		CMT0,	///< コンペアマッチタイマー０
		CMT1,	///< コンペアマッチタイマー１
		CMT2,	///< コンペアマッチタイマー２
		CMT3,	///< コンペアマッチタイマー３

		IWDT,	///< 独立ウォッチドッグタイマ

		RIIC0,	///< I 2 C バスインタフェース０

		SCI1,	///< シリアルコミュニケーションインタフェース０
		SCI1C,	///< シリアルコミュニケーションインタフェース０（クロック出力付）
		SCI5,	///< シリアルコミュニケーションインタフェース５
		SCI5C,	///< シリアルコミュニケーションインタフェース５（クロック出力付）
		SCI6,	///< シリアルコミュニケーションインタフェース６
		SCI6C,	///< シリアルコミュニケーションインタフェース６（クロック出力付）

		RSPI0,	///< シリアルペリフェラルインタフェース０

		CRC,	///< CRC 演算器（CRC）

		RSCAN,	///< RSCAN インタフェース（※Ｂバージョンのみ）

		MTU0,	///< マルチファンクションタイマパルスユニット０
		MTU1,	///< マルチファンクションタイマパルスユニット１
		MTU2,	///< マルチファンクションタイマパルスユニット２
		MTU3,	///< マルチファンクションタイマパルスユニット３
		MTU4,	///< マルチファンクションタイマパルスユニット４
		MTU5,	///< マルチファンクションタイマパルスユニット５
		MTU6,	///< マルチファンクションタイマパルスユニット６
		MTU7,	///< マルチファンクションタイマパルスユニット７
		MTU9,	///< マルチファンクションタイマパルスユニット９

		POE,	///< ポートアウトプットイネーブル

		GPT0,	///< 汎用 PWM タイマ０
		GPT1,	///< 汎用 PWM タイマ１
		GPT2,	///< 汎用 PWM タイマ２
		GPT3,	///< 汎用 PWM タイマ３

		TMR0,	///< 8 ビットタイマ０
		TMR1,	///< 8 ビットタイマ１
		TMR2,	///< 8 ビットタイマ２
		TMR3,	///< 8 ビットタイマ３
		TMR4,	///< 8 ビットタイマ４
		TMR5,	///< 8 ビットタイマ５
		TMR6,	///< 8 ビットタイマ６
		TMR7,	///< 8 ビットタイマ７

		S12AD,	///< 12 ビット A/D コンバータ０
		S12AD1,	///< 12 ビット A/D コンバータ１
		S12AD2,	///< 12 ビット A/D コンバータ２

		DA,		///< 8 ビット　D/A コンバータ

		CMPC0,	///< コンパレータＣ０
		CMPC1,	///< コンパレータＣ１
		CMPC2,	///< コンパレータＣ２
		CMPC3,	///< コンパレータＣ３

		DOC,	///< データ演算回路（DOC）
	};
}
