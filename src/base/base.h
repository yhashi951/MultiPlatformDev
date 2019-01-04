#pragma once

#ifdef _WINDOWS
#include "base/platform/win.h"
#endif

namespace Base
{
	// メインクラス
	class Main
	{
	public:
		// コンストラクタ
		Main(const char* name);

		// メイン実行関数
		int	Run();

		// 初期化
		bool	Initialize();

		// ループ
		bool	Loop();

		// 後処理
		void	Finalize();

	public:
#ifdef _WINDOWS
		Platform::Win	win;
#endif

	private:
		const char*	name_ = nullptr;
		int	exitCode_ = 0;
	};
};

