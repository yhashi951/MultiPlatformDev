#pragma once

#ifdef USE_WINDOWS
#include "base/platform/win.h"
#endif

#ifdef USE_LINUX
#include "platform/linux.h"
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
#ifdef USE_WINDOWS
		Platform::Win	win;
#endif
#ifdef USE_LINUX
		Platform::Linux	linux;
#endif 

	private:
		const char*	name_ = nullptr;
		int	exitCode_ = 0;
	};
};

