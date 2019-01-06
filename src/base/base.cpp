#include "base.h"

namespace Base
{
	Main::Main(const char* name)
		: name_(name)
	{
	}

	// メイン実行関数
	int Main::Run()
	{
		// 初期化
		if (!Initialize())
		{
			if (exitCode_ == 0) { exitCode_ = -1; }	// 終了コード加工
			return exitCode_;
		}

		// ループ
		while (Loop())
		{
		}

		// 後処理
		Finalize();

		return exitCode_;
	}

	// 初期化
	bool Main::Initialize()
	{
#ifdef USE_WINDOWS
		// Window生成
		if (win.CreateInstance(name_))
		{
			return true;
		}
#endif
#ifdef USE_LINUX
		// Linux生成
		if (linux.CreateInstance(name_))
		{
			return true;
		}
#endif
		return false;
	}

	// ループ
	bool Main::Loop()
	{
#ifdef USE_WINDOWS
		if (!win.Update()) { return false; }
#endif
#ifdef USE_LINUX
		if (!linux.Update()) { return false; }
#endif

		return true;
	}

	// 後処理
	void Main::Finalize()
	{
#ifdef USE_WINDOWS
		win.Release();
#endif
#ifdef USE_LINUX
		linux.Release();
#endif
	}
};	// Base

