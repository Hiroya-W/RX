#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・ペリフェラル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
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

		DMAC0,		///< DMA コントローラ・チャネル０
		DMAC1,		///< DMA コントローラ・チャネル１
		DMAC2,		///< DMA コントローラ・チャネル２
		DMAC3,		///< DMA コントローラ・チャネル３
		DMAC4,		///< DMA コントローラ・チャネル４
		DMAC5,		///< DMA コントローラ・チャネル５
		DMAC6,		///< DMA コントローラ・チャネル６
		DMAC7,		///< DMA コントローラ・チャネル７

		EXDMAC0,	///< EXDMA コントローラ・チャネル０
		EXDMAC1,	///< EXDMA コントローラ・チャネル１

		MTU0,		///< マルチファンクションタイマパルスユニット０
		MTU1,		///< マルチファンクションタイマパルスユニット１
		MTU2,		///< マルチファンクションタイマパルスユニット２
		MTU3,		///< マルチファンクションタイマパルスユニット３
		MTU4,		///< マルチファンクションタイマパルスユニット４
		MTU5,		///< マルチファンクションタイマパルスユニット５
		MTU6,		///< マルチファンクションタイマパルスユニット６
		MTU7,		///< マルチファンクションタイマパルスユニット７

		TMR0,		///< 8 ビットタイマ０
		TMR1,		///< 8 ビットタイマ１
		TMR2,		///< 8 ビットタイマ２
		TMR3,		///< 8 ビットタイマ３

		CMT0,		///< コンペアマッチタイマ０（CMT）
		CMT1,		///< コンペアマッチタイマ１（CMT）
		CMT2,		///< コンペアマッチタイマ２（CMT）
		CMT3,		///< コンペアマッチタイマ３（CMT）

		CMTW0,		///< コンペアマッチタイマＷ０（CMTW）
		CMTW1,		///< コンペアマッチタイマＷ１（CMTW）

		TPU0,		///< 16 ビットタイマパルスユニット０
		TPU1,		///< 16 ビットタイマパルスユニット１
		TPU2,		///< 16 ビットタイマパルスユニット２
		TPU3,		///< 16 ビットタイマパルスユニット３
		TPU4,		///< 16 ビットタイマパルスユニット４
		TPU5,		///< 16 ビットタイマパルスユニット５

		DTC,		///< データトランスファコントローラ

		ETHERC0,	///< Ethernet 0 (PHY RMII)
		ETHERC1,	///< Ethernet 1 (PHY RMII)
		PTPETHERC,	///< PTP Ethernet

		ETHERCA,	///< Ethernet 0 (PHY RMII)カスタムポート接続

		EDMAC0,		///< Ethernet DMA 0
		EDMAC1,		///< Ethernet DMA 1
		PTPEDMAC,	///< PTP Ethernet DMA

		USB0,		///< USB2.0FSホスト/ファンクションモジュール（USBb）
#if defined(SIG_RX64M) || defined(SIG_RX71M)
		USBA,		///< USB 2.0 Full-Speed ホスト / ファンクションモジュール（USBA）
#endif

		SCI0,		///< シリアルコミュニケーションインタフェース (P20:TXD0, P21:RXD0)
		SCI1,		///< シリアルコミュニケーションインタフェース (PF0:TXD1, PF2:RXD1)
		SCI2,		///< シリアルコミュニケーションインタフェース (P13:TXD2, P12:RXD2)
		SCI3,		///< シリアルコミュニケーションインタフェース (P23:TXD3, P25:RXD3)
		SCI4,		///< シリアルコミュニケーションインタフェース (PB1:TXD4, PB0:RXD4)
		SCI5,		///< シリアルコミュニケーションインタフェース (PA4:TXD5, PA2:RXD5)
		SCI6,		///< シリアルコミュニケーションインタフェース (P00:TXD6, P01:RXD6)
		SCI7,		///< シリアルコミュニケーションインタフェース (P90:TXD7, P92:RXD7)
#if defined(SIG_RX64M) || defined(SIG_RX71M)
		SCIF8,		///< FIFO 内臓シリアルコミュニケーションインターフェース
		SCIF9,		///< FIFO 内臓シリアルコミュニケーションインターフェース
		SCIF10,		///< FIFO 内臓シリアルコミュニケーションインターフェース
		SCIF11,		///< FIFO 内臓シリアルコミュニケーションインターフェース
#elif defined(SIG_RX65N)
		SCI8,		///< シリアルコミュニケーションインターフェース
		SCI9,		///< シリアルコミュニケーションインターフェース
		SCI10,		///< シリアルコミュニケーションインターフェース
		SCI11,		///< シリアルコミュニケーションインターフェース
#endif
		SCI12,		///< シリアルコミュニケーションインタフェース

		RIIC0,		///< I 2 C バスインタフェース０（RIICa）
#if defined(SIG_RX65N)
		RIIC1,		///< I 2 C バスインタフェース１（RIICa）
#endif
		RIIC2,		///< I 2 C バスインタフェース２（RIICa）

		CAN0,		///< CAN インタフェース（CAN0）
		CAN1,		///< CAN インタフェース（CAN1）
#if defined(SIG_RX64M) || defined(SIG_RX71M)
		CAN2,		///< CAN インタフェース（CAN2）
#endif
#if defined(SIG_RX65N)
		RSPI0,		///< シリアルペリフェラルインタフェース（RSPI0）
		RSPI1,		///< シリアルペリフェラルインタフェース（RSPI1）
#else
		RSPI,		///< シリアルペリフェラルインタフェース（RSPIa）
#endif
#ifdef SIG_RX71M
		RSPI2,		///< シリアルペリフェラルインタフェース（RSPIb）
#endif
		QSPI,		///< クワッドシリアルペリフェラルインタフェース（QSPI）

#if defined(SIG_RX64M) || defined(SIG_RX71M)
		SSI0,		///< シリアルサウンドインタフェース（SSI）
		SSI1,		///< シリアルサウンドインタフェース（SSI）
		SRC,		///< サンプリングレートコンバータ（SRC）
#endif
		SDHI,		///< SD ホストインタフェース（SDHI）

		S12AD,		///< 12 ビット A/D コンバータ（S12ADC）
		S12AD1,		///< 12 ビット A/D コンバータ（S12ADC）

		R12DA,		///< 12 ビット D/A コンバータ（R12DA）

		ECCRAM,		///< ECC RAM (32K)
		STBRAM,		///< Standby RAM (8K)

		// 仮の仕様
		IRQ0,
		IRQ1,
		IRQ2,
		IRQ3,
		IRQ4,
		IRQ5,
		IRQ6,
		IRQ7,

#ifdef SIG_RX65N
		GLCDC,		///< グラフィック LCD コントローラ (GLCDC)
		DRW2D,		///< 2D 描画エンジン (DRW2D)
#endif

		ICU,		///< グループ割り込みペリフェラル
	};
}
