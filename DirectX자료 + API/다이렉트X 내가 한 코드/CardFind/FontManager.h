#pragma once

#define FONTMGR	FontManager::GetInstance()

class FontManager
{
	SINGLETONE(FontManager);

	LPD3DXFONT			m_pFont;
	
public:
	void Setup();
	void DrawText(int _x, int _y, D3DXCOLOR _color, char* msg, ...);
	void Release();
};

