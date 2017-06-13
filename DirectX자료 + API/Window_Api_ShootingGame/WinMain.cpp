#include "GameCommon.h"
#pragma comment(lib,"msimg32.lib")

int WINAPI WinMain(
	HINSTANCE hInstance,	// 어플리케이션 인스턴스 핸들
	HINSTANCE hPrevInstance,// 이전 인스턴스 핸들 / Win32기반은 NULL
	LPSTR lpszCmdParam,		// 커맨드 라인 받을 포인터
	int nCmdShow			// 윈도우가 보여질때 상태 / 기본 NULL
)
{
	WINMGR->CreateWindowMgr(hInstance, 670, 800, "KITRI_API");

	GAMEMGR->Init();
	
	return WINMGR->GameLoop();
}

