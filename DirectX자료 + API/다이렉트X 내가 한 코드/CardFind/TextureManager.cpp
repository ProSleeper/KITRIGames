#include "stdafx.h"
#include "MyTexture.h"
#include "TextureManager.h"

MyTexture * TextureManager::GetTexture(string _TexName)
{
//	m_mapTextures[_TexName]; // 맵의 특징! 자동으로 키가 생김. 벨류는 널값

	if (m_mapTextures[_TexName] != NULL)
		return m_mapTextures[_TexName];

	MyTexture* pTex = new MyTexture;
	pTex->Init(_TexName);

	return (m_mapTextures[_TexName] = pTex);
}

void TextureManager::Release()
{
	for each(auto p in m_mapTextures)
	{
		SAFE_DELETE(p.second);
	}
	m_mapTextures.clear();
}

TextureManager::TextureManager()
{
	m_mapTextures.clear();
}


TextureManager::~TextureManager()
{
	Release();
}
