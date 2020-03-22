#pragma once
//=====================================================================//
/*! @file
    @brief  ハードウェアー・ベクター関係
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

#define INTERRUPT_FUNC __attribute__ ((interrupt))

#ifdef __cplusplus
extern "C" {
#endif

	//-----------------------------------------------------------------//
	/*!
		@brief	割り込み関数の設定
		@param[in]	task	割り込み関数
		@param[in]	idx		割り込みベクター番号
	 */
	//-----------------------------------------------------------------//
	void set_interrupt_task(void (*task)(void), uint32_t idx);

#ifdef __cplusplus
};
#endif


