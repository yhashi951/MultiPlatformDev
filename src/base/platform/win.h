#pragma once

#include <Windows.h>

namespace Base
{

namespace Platform
{

	class Win
	{
	public:
		// コールバック用ウィンドウプロシージャ型
		typedef	bool(*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

	public:
		Win();
		~Win();

		// 準備
		void	Prepare(HINSTANCE hinst);

		// Winプラットフォームのインスタンスとウィンドウ作成
		bool	CreateInstance(const char* name);

		// 更新
		bool	Update();

		// 解放
		void	Release();

		// インスタンス取得
		static	const Win*	GetInstance();

		// ウィンドウプロシージャのコールバック指定
		static	void	SetCallbackWndProc(Win::WNDPROC pCallbackWndProc);

		// ウィンドウプロシージャ
		static	bool	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	public:
		// ウィンドウズインスタンス取得
		HINSTANCE	GetHinstance() const { return hInstance_; }
		// ウィンドウハンドル取得
		HWND		GetHwnd() const		{ return hWnd_; }

	private:
		HINSTANCE	hInstance_ = nullptr;	// インスタンス
		HWND		hWnd_ = nullptr;		// ウィンドウハンドル
	};

};	// Platform

};	// Base
