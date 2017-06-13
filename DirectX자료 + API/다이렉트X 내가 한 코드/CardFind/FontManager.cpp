#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager()
	: m_pFont(NULL)
{
}


FontManager::~FontManager()
{
	Release();
}

void FontManager::Setup()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	fd.Width = 6;
	fd.Height = 12;
	fd.Weight = FW_MEDIUM; // FW_BOLD (글자 두껍게)
	fd.CharSet = DEFAULT_CHARSET;
	strcpy_s(fd.FaceName, "굴림체");
	// fd.Italic 폰트 기울이기

	D3DXCreateFontIndirect(DEVICE, &fd, &m_pFont);
	//D3DXCreateFont()
}

void FontManager::DrawText(int _x, int _y, D3DXCOLOR _color, char* msg, ...)
{
	char _szBuff[256] = { 0 };

	va_list vl;
	va_start(vl, msg);
	vsprintf_s(_szBuff, msg, vl);
	va_end(vl);

	RECT rc = { _x, _y, 0, 0 };
	m_pFont->DrawText(NULL, _szBuff, (int)strlen(_szBuff), &rc, DT_NOCLIP, _color);
}

void FontManager::Release()
{
	SAFE_RELEASE(m_pFont);
}
