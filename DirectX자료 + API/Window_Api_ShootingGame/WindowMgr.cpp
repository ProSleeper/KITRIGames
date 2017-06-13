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


	WNDCLASS WndClass; // ������ Ŭ���� ����ü
					   /*
					   �����ڰ� �����츦 ���ϴ�
					   ������� ����� ���ؼ�
					   ����ü�� ���� �Է�
					   */

					   // WinClass  �޸𸮻� 0 ���� �ʱ�ȭ
	ZeroMemory(&WndClass, sizeof(WndClass));
	// memset(Destination[void*],0,Length)

	// ���� ����, �⺻ 0���� ������� ����
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;

	// ������ ( ��� )
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// ���콺 Ŀ�� �̹���
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// ������ �̹���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// �ν��Ͻ� �ڵ�
	WndClass.hInstance = m_hInst;

	// ���ν��� ����
	WndClass.lpfnWndProc = WndProc;

	// Ŭ���� �̸�
	WndClass.lpszClassName = _name;

	// �޴��̸�  / �⺻ NULL
	WndClass.lpszMenuName = NULL;

	// ������ ��Ÿ��
	WndClass.style = CS_HREDRAW | CS_VREDRAW;



	// 1. �����츦 �������� ���
	RegisterClass(&WndClass);

	// 2. ������ ����
	m_hWnd = CreateWindow(
		_name,			// Ŭ���� �̸�
		_name,			// ĸ�ǹ� �̸�
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
		CW_USEDEFAULT,			// ������ X��ǥ
		CW_USEDEFAULT,			// ������ Y��ǥ
		m_iWidth,			// ������ ����
		m_iHeight,			// ������ ����
		NULL,					// �θ� ������
		(HMENU)NULL,			// �޴�
		m_hInst,				// �ν��Ͻ� �ڵ�
		NULL					// ���� ������ , �⺻ NULL
	);

	// 3. ������ ȭ�� ���
	ShowWindow(m_hWnd, SW_SHOW);

	ResizeWindow();
}

int WindowMgr::GameLoop()
{
	MSG	 Message;	// �̺�Ʈ �޽��� ť

	while (true)
	{
		// ���ѷ���
		if (PeekMessage(
			&Message, NULL, 0, 0, PM_REMOVE)
			)
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);		// Ű ���� �̺�Ʈ �˻� �Լ�
			DispatchMessage(&Message);		// WndProc �̺�Ʈ ó�� �Լ�
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
	// ���� ������ ��Ÿ�� ���
	RECT _oldRect;
	DWORD _windowStyle = (DWORD)GetWindowLong(
									m_hWnd, GWL_STYLE);

	// ���� ������ ũ�� ���
	GetWindowRect(m_hWnd, &_oldRect);

	// ���� Ŭ���̾�Ʈ ũ��
	RECT _newRect;
	_newRect.left = 0;
	_newRect.top = 0;
	_newRect.right = m_iWidth;
	_newRect.bottom = m_iHeight;

	// Ŭ���̾�Ʈ ���� �缳��
	AdjustWindowRect(&_newRect, _windowStyle, NULL);
	
	// ������ �������� �ʺ�� ���� ���Ѵ�.
	int width = (_newRect.right - _newRect.left);
	int height = (_newRect.bottom - _newRect.top);

	// ���ο� ũ�⸦ �����쿡 ����
	SetWindowPos(m_hWnd, HWND_NOTOPMOST,
		_oldRect.left, _oldRect.top,
		width, height, SWP_SHOWWINDOW);
}