#include "GameCommon.h"

HUDBar::HUDBar()
{
	m_pBackImage = NULL;
	m_pTarget = NULL;
	m_pTargetHP = NULL;
	m_pMaxHP = 0;
}


HUDBar::~HUDBar()
{
}

void HUDBar::Init(BaseTargetObject* pTarget,
	IMAGETYPE _backType, IMAGETYPE _imageType)
{
	BaseImageObject::Init(0, 0, _imageType);

	m_pBackImage = IMAGEMGR->GetImage(_backType);

	m_pTarget = pTarget;

	m_fPosX = (m_pTarget->GetPosX()
		+ m_pTarget->GetWidth() / 2) 
		- m_pBackImage->GetWidth() / 2;
	m_fPosY = m_pTarget->GetPosY()
		- m_pBackImage->GetHeight();

}

bool HUDBar::Update()
{
	if (m_pTarget == NULL)
		return false;

	m_fPosX = (m_pTarget->GetPosX()
		+ m_pTarget->GetWidth() / 2)
		- m_pBackImage->GetWidth() / 2;
	m_fPosY = m_pTarget->GetPosY()
		- m_pBackImage->GetHeight();

	m_iDrawWidth = (m_pTarget->GetHP())
		/ (float)m_pTarget->GetMaxHP() * m_pImage->GetWidth();

	return true;
}
void HUDBar::Render(HDC _backDC)
{
	BaseImageObject::Render(
		_backDC, m_pBackImage, m_iDrawWidth);
}
