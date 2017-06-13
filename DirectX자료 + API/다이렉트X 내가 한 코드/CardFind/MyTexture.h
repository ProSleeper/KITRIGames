#pragma once
class MyTexture
{
	GETTER(LPDIRECT3DTEXTURE9, Texture, m_pTexture);
	GETTER(string, Name, m_TexName);
	GETTER(int, Width, m_nWidth);
	GETTER(int, Hight, m_nHight);

public:
	void Init(string _name);
	void Release();

public:
	MyTexture();
	virtual ~MyTexture();
};

