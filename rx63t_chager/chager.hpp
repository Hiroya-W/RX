#pragma once
//=====================================================================//
/*!	@file
	@brief	Chager クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "rx/adc_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  チャージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class chager {

		device::adc_io<device::S12AD> adc_;

		static const int32_t low_limit_  = 6;
		static const int32_t high_limit_ = 404; // 15v at 19v in

		int32_t		loop_cpv0_;
		int32_t		loop_cpv1_;
		int32_t		adc_out0_;
		int32_t		adc_out1_;
		int32_t		adc_cur0_;
		int32_t		adc_cur1_;
		int32_t		adc_inp_;
		int32_t		adj_ref0_;
		int32_t		adj_ref1_;
		int32_t		adj_lim1_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		chager() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void initialize();


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service();

	};
}
