#pragma once

#define TEXMGR TextureManager::GetInstance()


class MyTexture;
class TextureManager
{
	SINGLETONE(TextureManager);

	map<string, MyTexture*>		m_mapTextures;

public:
	MyTexture* GetTexture(string _TexName);
	void Release();
	int GetTextureCount()
	{
		return (int)m_mapTextures.size();
	}
};

