#pragma once
class WindowMgr : public Singleton<WindowMgr>
{
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	int				m_iWidth;
	int				m_iHeight;

	PROPERTY_FUNC(HWND, hWnd, m_hWnd)
	PROPERTY_FUNC(int, Width, m_iWidth)
	PROPERTY_FUNC(int, Height, m_iHeight)

public:
	void CreateWindowMgr(HINSTANCE _hInst, 
		int _w, int _h,
		char* _name
	);
	int GameLoop();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	void ResizeWindow();

	WindowMgr();
	virtual ~WindowMgr();
};