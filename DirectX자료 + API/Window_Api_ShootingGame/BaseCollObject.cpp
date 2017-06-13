#include "GameCommon.h"

BaseCollObject::BaseCollObject()
{
}


BaseCollObject::~BaseCollObject()
{
}

void BaseCollObject::Init(BaseTransform* _pTarget)
{
	m_pTarget = _pTarget;
}

void BaseCollObject::Update()
{
	m_fPosX = m_pTarget->GetPosX();
	m_fPosY = m_pTarget->GetPosY();
	m_iWidth = m_pTarget->GetWidth();
	m_iHeight = m_pTarget->GetHeight();
}

void BaseCollObject::Render(HDC _backDC)
{
	int temp = GetROP2(_backDC);
	SetROP2(_backDC, R2_MASKPEN);
	Rectangle(_backDC, m_fPosX, m_fPosY,
		m_fPosX + m_iWidth, m_fPosY + m_iHeight);
	SetROP2(_backDC, temp);
}