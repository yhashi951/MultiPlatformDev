#pragma once

#include <xcb/xcb.h>

namespace Base
{

namespace Platform
{
	class Linux
	{
	public:
		Linux();
		~Linux();

		// Linuxプラットフォームのインスタンスとウィンドウ作成
		bool	CreateInstance(const char* name);

		// 更新
		bool	Update();

		// 解放
		void	Release();

		// インスタンス取得
		static	const Linux*	GetInstance();

	private:
		bool quit_ = false;
		xcb_connection_t* pConnection_ = nullptr;
		xcb_screen_t* pScreen_ = nullptr;
		xcb_window_t window_;
		xcb_intern_atom_reply_t* pAtomWmDeleteWindow_ = nullptr;

		uint16_t width_ = 1280;
		uint16_t height_ = 720;

	public:
		// ハンドラーイベント
		void	HandleEvent(const xcb_generic_event_t* event);

	};

};	// Platform

};	// Base

