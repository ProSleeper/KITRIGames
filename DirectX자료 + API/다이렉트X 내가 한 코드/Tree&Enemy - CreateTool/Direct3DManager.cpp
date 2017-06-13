#include "stdafx.h"
#include "Direct3DManager.h"


Direct3DManager::Direct3DManager()
	: m_pD3D(NULL)
	, m_pDevice(NULL)
	, m_hWnd(NULL)
	, m_nWidth(0)
	, m_nHeight(0)
{
}


Direct3DManager::~Direct3DManager()
{
	Destroy();
}

void Direct3DManager::Setup(void)
{
	m_nWidth = WINDOW_WIDTH;
	m_nHeight = WINDOW_HEIGHT;

	// d3d 객체 생성
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D)
	{
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.BackBufferWidth = m_nWidth;
		d3dpp.BackBufferHeight = m_nHeight;
		d3dpp.BackBufferCount = 1;
		d3dpp.Windowed = true;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		// 디바이스 생성
		m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice);

		if (m_pDevice == NULL)
		{
			MessageBox(NULL, "디바이스 생성 실패", "ERROR", MB_OK);
		}
	}

	ReSizeWindow();
}

void Direct3DManager::Destroy(void)
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
}

void Direct3DManager::ReSizeWindow()
{
	RECT		_oldRect;
	GetWindowRect(m_hWnd, &_oldRect);   // 윈도우 전체 렉트

	RECT		_rcWindow = { 0, 0, m_nWidth, m_nHeight };
	AdjustWindowRect(&_rcWindow, WS_OVERLAPPEDWINDOW, true);
	//							 ▲ 윈도우를 만들때 어떻게 만들엇는지 정보
	int _w = _rcWindow.right - _rcWindow.left;
	int _h = _rcWindow.bottom - _rcWindow.top;

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, _oldRect.left, _oldRect.top, _w, _h, SWP_SHOWWINDOW);
}
