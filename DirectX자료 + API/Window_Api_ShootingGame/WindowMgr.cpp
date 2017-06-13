#include "GameCommon.h"

WindowMgr::WindowMgr()
{
	m_hInst = NULL;
	m_hWnd = NULL;
	m_iWidth = 800;
	m_iHeight = 600;
}

WindowMgr::~WindowMgr()
{

}

void WindowMgr::CreateWindowMgr(
	HINSTANCE _hInst, int _w, int _h,char* _name) 
{
	m_hInst = _hInst;
	m_iWidth = _w;
	m_iHeight = _h;


	WNDCLASS WndClass; // 윈도우 클래스 구조체
					   /*
					   개발자가 윈도우를 원하는
					   방식으로 만들기 위해서
					   구조체를 직접 입력
					   */

					   // WinClass  메모리상 0 으로 초기화
	ZeroMemory(&WndClass, sizeof(WndClass));
	// memset(Destination[void*],0,Length)

	// 예약 영역, 기본 0으로 사용하지 않음
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;

	// 바탕색 ( 흰색 )
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// 마우스 커서 이미지
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// 아이콘 이미지
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// 인스턴스 핸들
	WndClass.hInstance = m_hInst;

	// 프로시저 지정
	WndClass.lpfnWndProc = WndProc;

	// 클래스 이름
	WndClass.lpszClassName = _name;

	// 메뉴이름  / 기본 NULL
	WndClass.lpszMenuName = NULL;

	// 윈도우 스타일
	WndClass.style = CS_HREDRAW | CS_VREDRAW;



	// 1. 윈도우를 레지스터 등록
	RegisterClass(&WndClass);

	// 2. 윈도우 생성
	m_hWnd = CreateWindow(
		_name,			// 클래스 이름
		_name,			// 캡션바 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		CW_USEDEFAULT,			// 윈도우 X좌표
		CW_USEDEFAULT,			// 윈도우 Y좌표
		m_iWidth,			// 윈도우 넓이
		m_iHeight,			// 윈도우 높이
		NULL,					// 부모 윈도우
		(HMENU)NULL,			// 메뉴
		m_hInst,				// 인스턴스 핸들
		NULL					// 여분 데이터 , 기본 NULL
	);

	// 3. 윈도우 화면 출력
	ShowWindow(m_hWnd, SW_SHOW);

	ResizeWindow();
}

int WindowMgr::GameLoop()
{
	MSG	 Message;	// 이벤트 메시지 큐

	while (true)
	{
		// 무한루프
		if (PeekMessage(
			&Message, NULL, 0, 0, PM_REMOVE)
			)
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);		// 키 문자 이벤트 검사 함수
			DispatchMessage(&Message);		// WndProc 이벤트 처리 함수
		}
		else
		{
			GAMEMGR->Loop();
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WindowMgr::WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


void WindowMgr::ResizeWindow()
{
	// 현재 윈도우 스타일 얻기
	RECT _oldRect;
	DWORD _windowStyle = (DWORD)GetWindowLong(
									m_hWnd, GWL_STYLE);

	// 현재 윈도우 크기 얻기
	GetWindowRect(m_hWnd, &_oldRect);

	// 변경 클라이언트 크기
	RECT _newRect;
	_newRect.left = 0;
	_newRect.top = 0;
	_newRect.right = m_iWidth;
	_newRect.bottom = m_iHeight;

	// 클라이언트 영역 재설정
	AdjustWindowRect(&_newRect, _windowStyle, NULL);
	
	// 보정된 윈도우의 너비와 폭을 구한다.
	int width = (_newRect.right - _newRect.left);
	int height = (_newRect.bottom - _newRect.top);

	// 새로운 크기를 윈도우에 설정
	SetWindowPos(m_hWnd, HWND_NOTOPMOST,
		_oldRect.left, _oldRect.top,
		width, height, SWP_SHOWWINDOW);
}