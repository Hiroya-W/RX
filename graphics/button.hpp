#pragma once
//=====================================================================//
/*!	@file
	@brief	ボタン表示と制御 @n
			・領域内で、「押した」、「離した」がある場合に「選択」と認識する。@n
			・選択時関数を使わない場合、select_id を監視する事で、状態の変化を認識できる。@n
			・選択時関数にはラムダ式を使える。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ボタン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct button : public widget {

		typedef button value_type;

		/// 選択される度にカ count が＋１する。
		typedef std::function<void(uint32_t count)> SELECT_FUNC_TYPE;

		static constexpr int16_t round_radius = 6;
		static constexpr int16_t frame_width  = 3;
		static constexpr int16_t box_size     = 30;		///< サイズが省略された場合の標準的なサイズ
		static constexpr int16_t edge_to_title = 4;

	private:

		SELECT_FUNC_TYPE	select_func_;
		uint32_t			select_id_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
		*/
		//-----------------------------------------------------------------//
		button(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), select_func_(), select_id_(0)
		{
			if(get_location().size.x <= 0) {
				auto tlen = 0;
				if(str != nullptr) {
					tlen = strlen(str) * 8;
				}
				at_location().size.x = (frame_width + edge_to_title) * 2 + tlen;
			}
			if(get_location().size.y <= 0) {
				at_location().size.y = box_size;
			}
			insert_widget(this);
		}


		button(const button& th) = delete;
		button& operator = (const button& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~button() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Button"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::BUTTON; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	ena		無効状態にする場合「false」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool ena = true) noexcept override
		{
			++select_id_;
			if(select_func_) {
				select_func_(select_id_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) noexcept override
		{
			if(ena) {
				set_state(STATE::ENABLE);
			} else {
				set_state(STATE::DISABLE);
				reset_touch_state();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト ID の取得
			@return	セレクト ID
		*/
		//-----------------------------------------------------------------//
		uint32_t get_select_id() const noexcept { return select_id_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画テンプレート
			@param[in]	rdr		描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			rdr.set_fore_color(get_base_color());
			rdr.round_box(r, round_radius);
			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}
			graphics::share_color sh(0, 0, 0);
			sh.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sh);

			r.org  += frame_width;
			r.size -= frame_width * 2;
			rdr.round_box(r, round_radius - frame_width);

			rdr.set_fore_color(get_font_color());
			auto mobj = get_mobj();
			if(mobj != nullptr) {  // mobj があれば、テキストより優先される。
				auto sz = rdr.get_mobj_size(mobj);
				rdr.draw_mobj(r.org + (r.size - sz) / 2, mobj, false);
			} else {
				auto sz = rdr.at_font().get_text_size(get_title());
				rdr.draw_text(r.org + (r.size - sz) / 2, get_title());
			}
		}
	};
}
