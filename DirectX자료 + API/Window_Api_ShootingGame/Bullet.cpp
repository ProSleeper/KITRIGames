#include "GameCommon.h"

Bullet::Bullet()
{	
	m_fAngle = 0.0f;
}

Bullet::~Bullet()
{
}

bool Bullet::Update()
{
	if (m_fPosY < -m_iHeight
		|| m_fPosX < 0
		|| m_fPosX > WINMGR->GetWidth()
		|| m_fPosY > WINMGR->GetHeight()
		)
		m_bLife = false;
	
	// m_fPosY -= m_fSpeed;
	m_fPosY -= m_fSpeed * cos(m_fAngle);
	m_fPosX += m_fSpeed * sin(m_fAngle);

	return m_bLife;
}

void Bullet::ResetBullet(int _x, int _y)
{
	m_fPosX = _x;
	m_fPosY = _y;
}

void Bullet::OnCollisionEnter(BaseTransform* _pColl)
{
	if (strncmp(m_szLayer, _pColl->GetLayer(), 5) != 0)
	{
		m_bLife = false;

		EFFECTMGR->CreateEffect(
			_pColl->GetPosX() + _pColl->GetWidth() / 2,
			_pColl->GetPosY() + _pColl->GetHeight() / 2);

		if (_pColl->GetTag() == TAG_BOSS)
		{
			((BossEnemy*)(_pColl))->OnHit(2);
		}
		else
			((BaseTargetObject*)_pColl)->SetLife(false);
	}

}