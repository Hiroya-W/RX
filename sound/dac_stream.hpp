#pragma once
//=====================================================================//
/*!	@file
	@brief	CPU 内蔵 D/A ストリームクラス @n
			内蔵 D/A に、連続した値を流す。@n
			MTU を基準タイマーとして利用する。@n
			DMAC を使って、D/A に値を書き込む。@n
			出力の GND レベルは中心電圧とする。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "sound/sound_out.hpp"
#include "common/mtu_io.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	D/A Stream class
		@param[in]	DAC			D/A 変換器クラス
		@param[in]	MTU			インターバルタイマークラス(MTUx)
		@param[in]	DMAC		DMAC クラス
		@param[in]	SOUND_OUT	サウンド出力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class DAC, class MTU, class DMAC, class SOUND_OUT>
	class dac_stream {

		SOUND_OUT&	sound_out_;

		struct mtu_t {
			SOUND_OUT&	sound_out_;
			volatile uint32_t wpos_;

			mtu_t(SOUND_OUT& sound_out) noexcept : sound_out_(sound_out), wpos_(0) { }
		};
		mtu_t		mtu_t_;

		static void* mtu_t_ptr_;

		// ITM 割り込み、64フレーム毎に、ソースバッファから波形メモリに転送
		class mtu_task {
		public:
			void operator() () {
				auto p = static_cast<mtu_t*>(mtu_t_ptr_);
				uint32_t tmp = p->wpos_;
				++p->wpos_;
				if((tmp ^ p->wpos_) & 64) {
					p->sound_out_.service(64);
				}
			}
		};

		typedef device::mtu_io<MTU, mtu_task> MTU_IO;
		MTU_IO		mtu_io_;

		// Internal D/A
		typedef device::dac_out<DAC> DAC_OUT;
		DAC_OUT		dac_out_;

		// DMAC 終了割り込み
		class dmac_term_task {
		public:
			void operator() () {
				auto p = static_cast<mtu_t*>(mtu_t_ptr_);
				DMAC::DMCNT.DTE = 1;  // DMA を再スタート
				p->wpos_ = 0;
			}
		};

		typedef device::dmac_mgr<DMAC, dmac_term_task> DMAC_MGR;
		DMAC_MGR	dmac_mgr_;

		uint32_t	sample_rate_;

		uint8_t		mtu_intl_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	sound_out	サウンドバッファの参照
		*/
		//-----------------------------------------------------------------//
		dac_stream(SOUND_OUT& sound_out) noexcept :
			sound_out_(sound_out), mtu_t_(sound_out), mtu_io_(),
			dac_out_(), dmac_mgr_(), sample_rate_(48'000), mtu_intl_(0)
		{
			mtu_t_ptr_ = &mtu_t_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	sample_rate	初期サンプルレート
			@param[in]	dmac_intl	DMAC の割り込みレベル
			@param[in]	mtu_intl	MTU の割り込みレベル
			@param[in]	amp_ena		D/A アンプを無効にする場合「false」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t sample_rate, uint8_t dmac_intl, uint8_t mtu_intl, bool amp_ena = true) noexcept
		{
			{  // 内臓１２ビット D/A の設定
				bool amp_ena = true;
				dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
				dac_out_.out0(0x8000);
				dac_out_.out1(0x8000);
			}

			// 波形メモリーの無音状態初期化
			sound_out_.mute();

			mtu_intl_ = mtu_intl;
			set_sample_rate(sample_rate);

			{  // DMAC マネージャー開始
				bool cpu_intr = true;
				auto ret = dmac_mgr_.start(mtu_io_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
					reinterpret_cast<uint32_t>(sound_out_.get_wave()), DAC::DADR0.address(),
					sound_out_.size(), dmac_intl, cpu_intr);
				if(!ret) {
//					utils::format("DMAC Not start...\n");
					return false;
				}
//				utils::format("TPU intr level: %d\n") % static_cast<int>(tpu_io_.get_intr_vec());
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプルレートを設定
			@param[in]	freq	サンプルレート
		*/
		//-----------------------------------------------------------------//
		void set_sample_rate(uint32_t freq) noexcept
		{
    	    if(!mtu_io_.start(freq, mtu_intl_)) {
        	    utils::format("ITM start error...\n");
        	}
			sample_rate_ = freq;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サンプルレートを取得
			@return	サンプルレート
		*/
		//-----------------------------------------------------------------//
		uint32_t get_sample_rate() const noexcept { return sample_rate_; }
	};

	template<class DAC, class MTU, class DMAC, class SOUND_OUT>
		void* dac_stream<DAC, MTU, DMAC, SOUND_OUT>::mtu_t_ptr_;
}
