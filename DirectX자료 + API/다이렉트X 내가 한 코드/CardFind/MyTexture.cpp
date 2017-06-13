#include "stdafx.h"
#include "MyTexture.h"


void MyTexture::Init(string _name)
{
	m_TexName = _name;
	D3DXIMAGE_INFO _info;
	ZeroMemory(&_info, sizeof(_info));

	D3DXCreateTextureFromFileEx(DEVICE, m_TexName.c_str(), 0, 0, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_DEFAULT, D3DXCOLOR(0, 0, 0, 1), &_info, NULL, &m_pTexture);

	if (m_pTexture == NULL)
	{
		char szTemp[50];
		sprintf_s(szTemp, "Texture Load Fail : %s", m_TexName.c_str());
		MessageBox(NULL, szTemp, "Fail", MB_OK);

		return;
	}

	m_nWidth = _info.Width;
	m_nHight = _info.Height;
}

void MyTexture::Release()
{
	SAFE_RELEASE(m_pTexture);
}

MyTexture::MyTexture()
	: m_pTexture(NULL)
	, m_nWidth(0)
	, m_nHight(0)
	, m_TexName("")
{
}


MyTexture::~MyTexture()
{
	Release();
}
