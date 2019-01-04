
#include "win.h"
#include <stdio.h>

namespace Base
{
namespace Platform
{
	Win*	pWinInstance_ = nullptr;
	Win::WNDPROC	pCallbackWndProc_ = nullptr;

	// コンストラクタ
	Win::Win()
	{
		if (!pWinInstance_)
		{
			pWinInstance_ = this;
		}
	}

	// デストラクタ
	Win::~Win()
	{
		if (hInstance_)
		{
			Release();
		}

		if (pWinInstance_ == this)
		{
			pWinInstance_ = nullptr;
		}
	}

	// 準備
	void Win::Prepare(HINSTANCE hinst)
	{
		hInstance_ = hinst;
	}

	// インスタンス作成p
	bool Win::CreateInstance(const char* name)
	{
		if (!hInstance_) { return false; }

		char wndClassName[128] = {};
		sprintf_s(wndClassName, "%s_wc", name);

		// ウィンドウクラス設定
		{
			WNDCLASSEX wcex = {};

			wcex.cbSize = sizeof(wcex);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			// WndProcをラムダで設定
			wcex.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
			{
				WndProc(hWnd, uMsg, wParam, lParam);
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			};
			wcex.hInstance = hInstance_;
			wcex.lpszClassName = wndClassName;

			if (!RegisterClassEx(&wcex))
			{
				return false;
			}
		}

		// ウィンドウ生成
		hWnd_ = CreateWindowA(wndClassName, name, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance_, nullptr);

		if (!hWnd_)
		{
			return false;
		}

		// ウィンドウ表示
		ShowWindow(hWnd_, SW_SHOW);
		UpdateWindow(hWnd_);

		return true;
	}

	// 更新
	bool Win::Update()
	{
		MSG msg;

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) 
			{
				return false;
			}
		}

		return true;
	}

	// 解放
	void Win::Release()
	{
		hInstance_ = nullptr;
	}

	// インスタンス取得
	const Win* Win::GetInstance()
	{
		return pWinInstance_;
	}

	// ウィンドウプロシージャのコールバック指定
	void Win::SetCallbackWndProc(Win::WNDPROC pCallbackWndProc)
	{
		pCallbackWndProc_ = pCallbackWndProc;
	}

	// ウィンドウプロシージャ
	bool Win::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// コールバックがあればそっちが優先
		if (pCallbackWndProc_)
		{
			if (pCallbackWndProc_(hWnd, uMsg, wParam, lParam))
			{
				return true;
			}
		}

		switch (uMsg)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			break;
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED)
			{
				if (((wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED)))
				{
				}
			}
			break;
		default:
			return false;
		}

		return true;
	}

};	// Platform
};	// Base
