#pragma once

enum IMAGETYPE
{
	IT_BACK = 0,	//순서 틀리면 오류 발생.
	IT_MAP,
	IT_LOGO,
	IT_ENDING,
	IT_PLAYER,
	IT_ENEMY,
	IT_BULLET,
	IT_EXPLOSION,
	IT_BOSSENEMY,
	IT_HUD,
	IT_HUDBACK,
	IT_MAX,
};

class ImageMgr : public Singleton<ImageMgr>
{
	Image	m_Image[IT_MAX];

public:
	void LoadImages(HDC _dc);
	Image* GetImage(IMAGETYPE _type)
	{
		return &m_Image[_type];
	}

public:
	ImageMgr();
	virtual ~ImageMgr();
};

