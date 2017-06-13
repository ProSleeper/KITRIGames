#include "GameCommon.h"

Enemy::Enemy()
{
	strcpy_s(m_szLayer, "Enemy_General");

//	ZeroMemory(&m_CollRect, sizeof(m_CollRect));
}

Enemy::~Enemy()
{
}

bool Enemy::Update()
{
	if (m_fPosY > WINMGR->GetHeight())
	{
		return false;
	}

	m_fPosY += m_fSpeed;
//	OffsetRect(&m_CollRect, 0, m_fSpeed);

	return true;
}

//void Enemy::OnCollisionEnter(BaseTransform* _pCollObj)
//{
//	m_bLife = false;
//}
