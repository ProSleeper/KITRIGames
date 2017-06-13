#include "GameCommon.h"



Image::Image()
{
	m_hDC = NULL;
	m_hMemDc = NULL;
	m_hBit = NULL;
	m_iWidth = 0;
	m_iHeight = 0;

	m_dwColor = 0;
}

Image::~Image()
{
	ReleaseImage();
}

void Image::LoadBitImage(HDC _dc, char* _name, DWORD _dwColor)
{
	m_hDC = _dc;
	m_dwColor = _dwColor;

	m_hMemDc = CreateCompatibleDC(m_hDC);
	m_hBit = (HBITMAP)LoadImage(NULL, _name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(m_hMemDc, m_hBit);

	BITMAP bitInfo;
	GetObject(m_hBit, sizeof(BITMAP), &bitInfo);
	m_iWidth = bitInfo.bmWidth;
	m_iHeight = bitInfo.bmHeight;		
}

void Image::LoadBitImage(HDC _dc, char* _name,
	int _fx, int _fy, DWORD _dwColor)
{
	m_hDC = _dc;
	m_dwColor = _dwColor;

	m_hMemDc = CreateCompatibleDC(m_hDC);
	m_hBit = (HBITMAP)LoadImage(NULL, _name, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	SelectObject(m_hMemDc, m_hBit);

	BITMAP bitInfo;
	GetObject(m_hBit, sizeof(BITMAP), &bitInfo);
	m_iWidth = bitInfo.bmWidth / _fx;
	m_iHeight = bitInfo.bmHeight / _fy;
}

void Image::RenderImage(HDC _backDC, int _x, int _y)
{
	if (m_dwColor == -1)
	{
		BitBlt(_backDC, _x, _y, m_iWidth, m_iHeight,
			m_hMemDc, 0, 0, SRCCOPY);
	}
	else
	{
		TransparentBlt(_backDC, _x, _y, m_iWidth, m_iHeight,
			m_hMemDc, 0, 0, m_iWidth, m_iHeight, m_dwColor);
	}
}

void Image::RenderImage(HDC _backDC, int _x, int _y,
	int _imgX, int _imgY)
{
	if (m_dwColor == -1)
	{
		BitBlt(_backDC, _x, _y, m_iWidth, m_iHeight,
			m_hMemDc, _imgX, _imgY, SRCCOPY);
	}
	else
	{
		TransparentBlt(_backDC, _x, _y, m_iWidth, m_iHeight,
			m_hMemDc, _imgX, _imgY, m_iWidth, m_iHeight, m_dwColor);
	}
}

void Image::RenderImage(
	HDC _backDC, int _x, int _y, int _w)
{
	if (m_dwColor == -1)
	{
		BitBlt(_backDC, _x, _y, _w, m_iHeight,
			m_hMemDc, 0, 0, SRCCOPY);
	}
	else
	{
		TransparentBlt(_backDC, _x, _y, m_iWidth, m_iHeight,
			m_hMemDc, 0, 0, _w, m_iHeight, m_dwColor);
	}
}

void Image::RenderImage(HDC _backDC,
	int _x, int _y, BLENDFUNCTION _bf)

{
	AlphaBlend(_backDC, _x, _y, m_iWidth, m_iHeight,
		m_hMemDc, 0, 0, m_iWidth, m_iHeight, _bf);
}

void Image::RenderImage(HDC _backDC,
	float _x, float _y, float _w, float _h,
	RECT rcDraw)
{
	BitBlt(_backDC, _x, _y, _w, _h, m_hMemDc, rcDraw.left,
		rcDraw.top, SRCCOPY);
}

void Image::ReleaseImage()
{
	DeleteObject(m_hMemDc);
}


