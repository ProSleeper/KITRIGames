#include "GameCommon.h"

BaseImageObject::BaseImageObject()
{
	m_pImage = NULL;
	m_bCollider = false; //
	//m_bLife = true;
	//m_fSpeed = 1;
}

BaseImageObject::~BaseImageObject()
{
	Release();
}

void BaseImageObject::Init(
	int _x, int _y, int _w, int _h, IMAGETYPE _type)
{
	m_pImage = IMAGEMGR->GetImage(_type);

	m_fPosX = _x;
	m_fPosY = _y;
	m_iWidth = _w;
	m_iHeight = _h;
}

void BaseImageObject::Init(
	int _x, int _y, IMAGETYPE _type)
{
	m_pImage = IMAGEMGR->GetImage(_type);

	m_fPosX = _x;
	m_fPosY = _y;
	m_iWidth = m_pImage->GetWidth();
	m_iHeight = m_pImage->GetHeight();
}

void BaseImageObject::Render(HDC _backDC)
{
	m_pImage->RenderImage(_backDC, m_fPosX, m_fPosY);
}

void BaseImageObject::Render(
	HDC _backDC, Image* _pback, int _w)
{
	_pback->RenderImage(_backDC, m_fPosX, m_fPosY);
	m_pImage->RenderImage(_backDC, m_fPosX, m_fPosY, _w);
}

