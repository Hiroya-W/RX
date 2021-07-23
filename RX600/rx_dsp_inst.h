#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン DSP 命令定義（gcc）@n
            r_dsp_inst_rxv?.h に準拠
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <stdint.h>

#ifndef __GNUC__
  #error "rx_dsp_inst.h: Requires gcc compiler"
#endif

//-----------------------------------------------------------------//
/*!
	@brief  32bit 乗算（結果をアキュムレータ ACC0）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emula_a0(int32_t src, int32_t src2)
{
    asm("emula %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 乗算（結果をアキュムレータ ACC1）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emula_a1(int32_t src, int32_t src2)
{
    asm("emula %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 積和（結果を加算するアキュムレータ ACC0）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emaca_a0(int32_t src, int32_t src2)
{
    asm("emaca %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 積和（結果を加算するアキュムレータ ACC1）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emaca_a1(int32_t src, int32_t src2)
{
    asm("emaca %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 積差（結果を減算するアキュムレータ ACC0）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emsba_a0(int32_t src, int32_t src2)
{
    asm("emsba %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 積差（結果を減算するアキュムレータ ACC1）
	@param[in]  src     32bit 固定小数点の被乗数
    @param[in]  src2    32bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __emsba_a1(int32_t src, int32_t src2)
{
    asm("emsba %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 上位 16bit x 上位 16bit（ACC0）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mulhi_a0(int32_t src, int32_t src2)
{
    asm("mulhi %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 上位 16bit x 上位 16bit（ACC1）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mulhi_a1(int32_t src, int32_t src2)
{
    asm("mulhi %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 16bit x 上位 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mullh_a0(int32_t src, int32_t src2)
{
    asm("mullh %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 16bit x 上位 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mullh_a1(int32_t src, int32_t src2)
{
    asm("mullh %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 16bit x 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mullo_a0(int32_t src, int32_t src2)
{
    asm("mullo %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 16bit x 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __mullo_a1(int32_t src, int32_t src2)
{
    asm("mullo %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 乗算 上位 16bit x 上位 16bit（ACC0）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muchi_a0(int32_t src, int32_t src2)
{
    asm("muchi %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積和 上位 16bit x 上位 16bit（ACC1）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muchi_a1(int32_t src, int32_t src2)
{
    asm("muchi %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積和 16bit x 上位 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muclh_a0(int32_t src, int32_t src2)
{
    asm("muclh %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積和 16bit x 上位 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muclh_a1(int32_t src, int32_t src2)
{
    asm("muclh %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積和 16bit x 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muclo_a0(int32_t src, int32_t src2)
{
    asm("muclo %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積和 16bit x 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __muclo_a1(int32_t src, int32_t src2)
{
    asm("muclo %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 上位 16bit x 上位 16bit（ACC0）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msbhi_a0(int32_t src, int32_t src2)
{
    asm("msbhi %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 上位 16bit x 上位 16bit（ACC1）
	@param[in]  src     上位 16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msbhi_a1(int32_t src, int32_t src2)
{
    asm("msbhi %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 16bit x 上位 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msblh_a0(int32_t src, int32_t src2)
{
    asm("msblh %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 16bit x 上位 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    上位 16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msblh_a1(int32_t src, int32_t src2)
{
    asm("msblh %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 16bit x 16bit（ACC0）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msblo_a0(int32_t src, int32_t src2)
{
    asm("msblo %[src], %[src2], A0" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 積差 16bit x 16bit（ACC1）
	@param[in]  src     16bit に 16bit 固定小数点の被乗数
    @param[in]  src2    16bit に 16bit 固定小数点の乗数
*/
//-----------------------------------------------------------------//
inline void __msblo_a1(int32_t src, int32_t src2)
{
    asm("msblo %[src], %[src2], A1" : : [src] "r" (src), [src2] "r" (src2) );
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と丸め（LeftShift: 1, ACC0）
*/
//-----------------------------------------------------------------//
inline void __racl_s1_a0(void)
{
    asm("racl #1, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と丸め（LeftShift: 1, ACC1）
*/
//-----------------------------------------------------------------//
inline void __racl_s1_a1(void)
{
    asm("racl #1, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と丸め（LeftShift: 2, ACC0）
*/
//-----------------------------------------------------------------//
inline void __racl_s2_a0(void)
{
    asm("racl #2, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と丸め（LeftShift: 2, ACC1）
*/
//-----------------------------------------------------------------//
inline void __racl_s2_a1(void)
{
    asm("racl #2, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と切り捨て（LeftShift: 1, ACC0）
*/
//-----------------------------------------------------------------//
inline void __rdacl_s1_a0(void)
{
    asm("rdacl #1, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と切り捨て（LeftShift: 1, ACC1）
*/
//-----------------------------------------------------------------//
inline void __rdacl_s1_a1(void)
{
    asm("rdacl #1, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と切り捨て（LeftShift: 2, ACC0）
*/
//-----------------------------------------------------------------//
inline void __rdacl_s2_a0(void)
{
    asm("rdacl #2, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  32bit 飽和と切り捨て（LeftShift: 2, ACC1）
*/
//-----------------------------------------------------------------//
inline void __rdacl_s2_a1(void)
{
    asm("rdacl #2, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と丸め（LeftShift: 1, ACC0）
*/
//-----------------------------------------------------------------//
inline void __racw_s1_a0(void)
{
    asm("racw #1, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と丸め（LeftShift: 1, ACC1）
*/
//-----------------------------------------------------------------//
inline void __racw_s1_a1(void)
{
    asm("racw #1, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と丸め（LeftShift: 2, ACC0）
*/
//-----------------------------------------------------------------//
inline void __racw_s2_a0(void)
{
    asm("racw #2, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と丸め（LeftShift: 2, ACC1）
*/
//-----------------------------------------------------------------//
inline void __racw_s2_a1(void)
{
    asm("racw #2, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と切り捨て（LeftShift: 1, ACC0）
*/
//-----------------------------------------------------------------//
inline void __rdacw_s1_a0(void)
{
    asm("rdacw #1, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と切り捨て（LeftShift: 1, ACC1）
*/
//-----------------------------------------------------------------//
inline void __rdacw_s1_a1(void)
{
    asm("rdacw #1, A1");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と切り捨て（LeftShift: 2, ACC0）
*/
//-----------------------------------------------------------------//
inline void __rdacw_s2_a0(void)
{
    asm("rdacw #2, A0");
}


//-----------------------------------------------------------------//
/*!
	@brief  16bit 飽和と切り捨て（LeftShift: 2, ACC1）
*/
//-----------------------------------------------------------------//
inline void __rdacw_s2_a1(void)
{
    asm("rdacw #2, A1");
}

#ifdef __RXV3__
//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 0, ACC0)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s0_a0(void)
{
    int32_t dst;
    asm("mvfacgu #0, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 0, ACC1)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s0_a1(void)
{
    int32_t dst;
    asm("mvfacgu #0, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 1, ACC0)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s1_a0(void)
{
    int32_t dst;
    asm("mvfacgu #1, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 1, ACC1)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s1_a1(void)
{
    int32_t dst;
    asm("mvfacgu #1, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 2, ACC0)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s2_a0(void)
{
    int32_t dst;
    asm("mvfacgu #2, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータガードビットの読み出し（Left Shift: 2, ACC1)
    @return アキュムレータガードビット
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacgu_s2_a1(void)
{
    int32_t dst;
    asm("mvfacgu #2, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}
#endif

//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 0, ACC0)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s0_a0(void)
{
    int32_t dst;
    asm("mvfachi #0, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 0, ACC1)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s0_a1(void)
{
    int32_t dst;
    asm("mvfachi #0, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 1, ACC0)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s1_a0(void)
{
    int32_t dst;
    asm("mvfachi #1, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 1, ACC1)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s1_a1(void)
{
    int32_t dst;
    asm("mvfachi #1, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 2, ACC0)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s2_a0(void)
{
    int32_t dst;
    asm("mvfachi #2, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit の読み出し（Left Shift: 2, ACC1)
    @return アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfachi_s2_a1(void)
{
    int32_t dst;
    asm("mvfachi #2, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 0, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s0_a0(void)
{
    int32_t dst;
    asm("mvfaclo #0, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 0, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s0_a1(void)
{
    int32_t dst;
    asm("mvfaclo #0, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 1, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s1_a0(void)
{
    int32_t dst;
    asm("mvfaclo #1, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 1, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s1_a1(void)
{
    int32_t dst;
    asm("mvfaclo #1, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 2, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s2_a0(void)
{
    int32_t dst;
    asm("mvfaclo #2, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit の読み出し（Left Shift: 2, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfaclo_s2_a1(void)
{
    int32_t dst;
    asm("mvfaclo #2, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 0, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s0_a0(void)
{
    int32_t dst;
    asm("mvfacmi #0, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 0, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s0_a1(void)
{
    int32_t dst;
    asm("mvfacmi #0, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 1, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s1_a0(void)
{
    int32_t dst;
    asm("mvfacmi #1, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 1, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s1_a1(void)
{
    int32_t dst;
    asm("mvfacmi #1, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 2, ACC0)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s2_a0(void)
{
    int32_t dst;
    asm("mvfacmi #2, A0, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ中央 32bit の読み出し（Left Shift: 2, ACC1)
    @return アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline int32_t __mvfacmi_s2_a1(void)
{
    int32_t dst;
    asm("mvfacmi #2, A1, %[dst]" : [dst] "=r" (dst) );
    return dst;
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit 書き込み（ACC0)
    @param[in] src  アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtachi_a0(uint32_t src)
{
    asm("mvtachi %[src], A0" : : [src] "r" (src) );
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit 書き込み（ACC1)
    @param[in] src  アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtachi_a1(uint32_t src)
{
    asm("mvtachi %[src], A1" : : [src] "r" (src) );
}

#ifdef __RXV3_
//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit 書き込み（ACC0)
    @param[in] src  アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtacgu_a0(uint32_t src)
{
    asm("mvtacgu %[src], A0" : : [src] "r" (src) );
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ上位 32bit 書き込み（ACC1)
    @param[in] src  アキュムレータ上位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtacgu_a1(uint32_t src)
{
    asm("mvtacgu %[src], A1" : : [src] "r" (src) );
}
#endif

//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit 書き込み（ACC0)
    @param[in] src  アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtaclo_a0(uint32_t src)
{
    asm("mvtaclo %[src], A0" : : [src] "r" (src) );
}


//-----------------------------------------------------------------//
/*!
	@brief  アキュムレータ下位 32bit 書き込み（ACC1)
    @param[in] src  アキュムレータ下位 32bit
*/
//-----------------------------------------------------------------//
inline void __mvtaclo_a1(uint32_t src)
{
    asm("mvtaclo %[src], A1" : : [src] "r" (src) );
}
