#include "GameCommon.h"

ImageMgr::ImageMgr()
{
}


ImageMgr::~ImageMgr()
{
}

void ImageMgr::LoadImages(HDC _dc)
{
	m_Image[IT_BACK].LoadBitImage(_dc,
		"back.bmp");
	m_Image[IT_MAP].LoadBitImage(_dc,
		"map.bmp");
	m_Image[IT_LOGO].LoadBitImage(_dc,
		"logo.bmp");
	m_Image[IT_ENDING].LoadBitImage(_dc,
		"ending.bmp");

	m_Image[IT_PLAYER].LoadBitImage(_dc,
		"Player.bmp", RGB(0, 0, 255));
	m_Image[IT_ENEMY].LoadBitImage(_dc,
		"enemy.bmp", RGB(255, 0, 255));

	m_Image[IT_BOSSENEMY].LoadBitImage(_dc,
		"boss.bmp", RGB(255, 0, 255));

	m_Image[IT_BULLET].LoadBitImage(_dc,
		"bullet.bmp", RGB(0, 0, 255)); 

	m_Image[IT_EXPLOSION].LoadBitImage(_dc,
		"explosion.bmp", 8, 1, RGB(0, 0, 0));

	m_Image[IT_HUD].LoadBitImage(_dc,
		"hpbar_boss.bmp");
	m_Image[IT_HUDBACK].LoadBitImage(_dc,
		"hpbarback_boss.bmp");
}
