#include "GameCommon.h"
#pragma comment(lib,"msimg32.lib")

int WINAPI WinMain(
	HINSTANCE hInstance,	// ���ø����̼� �ν��Ͻ� �ڵ�
	HINSTANCE hPrevInstance,// ���� �ν��Ͻ� �ڵ� / Win32����� NULL
	LPSTR lpszCmdParam,		// Ŀ�ǵ� ���� ���� ������
	int nCmdShow			// �����찡 �������� ���� / �⺻ NULL
)
{
	WINMGR->CreateWindowMgr(hInstance, 670, 800, "KITRI_API");

	GAMEMGR->Init();
	
	return WINMGR->GameLoop();
}

