#pragma once
class Image
{
	HDC		m_hDC;
	HDC		m_hMemDc;
	HBITMAP m_hBit;

	int		m_iWidth;
	int		m_iHeight;

	DWORD	m_dwColor;

	PROPERTY_FUNC(HDC, MemDC, m_hMemDc)
	PROPERTY_FUNC(int, Width, m_iWidth)
	PROPERTY_FUNC(int, Height, m_iHeight)


public:
	void LoadBitImage(HDC _dc, char* _name, DWORD _dwColor = -1);
	void LoadBitImage(HDC _dc, char* _name, 
		int _fx, int _fy, DWORD _dwColor = -1);

	void RenderImage(HDC _backDC, int _x, int _y);
	void RenderImage(HDC _backDC, int _x, int _y,
		int _imgX, int _imgY);

	void RenderImage(
		HDC _backDC, int _x, int _y, int _w);

	void RenderImage(HDC _backDC,
		int x, int y, BLENDFUNCTION _bf);

	void RenderImage(HDC _backDC,
		float _x, float _y, float _w, float _h,
		RECT rcDraw);

	void ReleaseImage();

public:
	Image();
	virtual ~Image();
};

