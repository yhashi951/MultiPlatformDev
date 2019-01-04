// MultiPlatformDev.cpp: アプリケーションのエントリ ポイントを定義します。
//

#include "main.h"
#include "base/base.h"


#ifdef WIN32

// Windowsのメイン関数
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	
	Base::Main main(Main::APP_TITLE_NAME);
	main.win.Prepare(hInstance);
	return main.Run();
}

#else

// メイン関数
int	main(int argc const char* argv[])
{
	Base::Main main(Main::APP_TITLE_NAME);
	return main.Run();
}

#endif

