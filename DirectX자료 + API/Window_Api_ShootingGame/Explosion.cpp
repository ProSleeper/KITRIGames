#include "GameCommon.h"



Explosion::Explosion()
{
	m_iTotalWidth = 0;
	m_iTotalHeight = 0;
	m_iTotalTime = 0;

	m_iFrameX = 0;
	m_iFrameY = 0;
	m_iCurrFrameX = 0;
	m_iCurrFrameY = 0;
	m_iCurrFrame = 0;
	m_iTotalFrame = 0;
	m_iNextTime = 0;
	m_iCurrTime = 0;
	m_iOldTime = 0;
	m_iCalTime = 0;
}


Explosion::~Explosion()
{
}

void Explosion::Init(int _x, int _y, int _w, int _h, int _tw, int _th, int _ttime, IMAGETYPE _type)
{
	m_pImage = IMAGEMGR->GetImage(IT_EXPLOSION);

	m_fPosX = _x;
	m_fPosY = _y;
	m_iWidth = _w;
	m_iHeight = _h;
	m_iTotalWidth = _tw;
	m_iTotalHeight = _th;
	m_iTotalTime = _ttime;

	m_iFrameX = m_iTotalWidth / m_iWidth;
	m_iFrameY = m_iTotalHeight / m_iHeight;
	m_iTotalFrame = m_iFrameX * m_iFrameY;
	m_iNextTime = ((float)m_iTotalTime / m_iTotalFrame)
		* 1000;
	m_iOldTime = timeGetTime();
	m_iCalTime = m_iNextTime;
}

bool Explosion::Update()
{

	m_iCurrTime = timeGetTime() - m_iOldTime;

	if (m_iCurrTime >= m_iCalTime)
	{
		m_iCalTime += m_iNextTime;
		m_iCurrFrame++;

		if (m_iCurrFrame >= m_iTotalFrame) return false;

		if (m_iFrameY > 1)
			m_iCurrFrameY = m_iCurrFrame / m_iFrameX;

		m_iCurrFrameX = m_iCurrFrame % m_iFrameX;
	}
	return true;
}

void Explosion::Render(HDC _backDC)
{
	int _x, _y;
	_x = m_iCurrFrameX * m_iWidth;
	_y = m_iCurrFrameY * m_iHeight;

	m_pImage->RenderImage(
		_backDC, m_fPosX, m_fPosY, _x, _y);
}


