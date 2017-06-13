#include "GameCommon.h"



BulletEnemy::BulletEnemy()
{
	strcpy_s(m_szLayer, "Enemy_BulletEnemy");
	//m_dwCurrTime = 0;
	//m_dwOldTime = 0;
	m_iBulletCount = 0;
	m_iBulletMaxCount = 3;
	m_iFirePos = 30;
	m_fFireDelayTime = 0.2f;
	m_bFire = false;
	m_bDown = true;
}


BulletEnemy::~BulletEnemy()
{
}

bool BulletEnemy::Update()
{
	if (m_fPosY > WINMGR->GetHeight())
		return false;

	if (m_fPosY > m_iFirePos  && m_bFire == false
		&& m_bDown == true)
	{
		m_bFire = true;
		m_bDown = false;
		// m_dwOldTime = timeGetTime();
		m_BulletTime.SetUpTime(m_fFireDelayTime);
	}

	if(m_bDown == true)
		m_fPosY += m_fSpeed;

	if (m_bFire && m_bDown == false)
	{
		if (m_iBulletCount > m_iBulletMaxCount)
		{
			m_bFire = false;
			m_iFirePos = m_fPosY + rand() % 300 + 100;
			m_iBulletCount = 0;

			m_bDown = true;
		}
		else
		{
			/*m_dwCurrTime = timeGetTime();
			
			if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)*/
			if(m_BulletTime.TimeCheck())
			{
				Fire();
				m_iBulletCount++;
				//m_dwOldTime = m_dwCurrTime;
			}
		}
	}
	return true;

}

void BulletEnemy::Fire(float _angle, float _speed)
{
	Bullet* _pObj = new Bullet;
	_pObj->Init(0, 0, 16, 22, IT_BULLET);
	_pObj->ResetBullet(m_fPosX + m_iWidth / 2
		- _pObj->GetWidth() / 2,
		m_fPosY + m_iHeight);
	
	_pObj->SetAngle(_angle);
	_pObj->SetSpeed(-_speed);

	_pObj->SetTag(TAG_ENEMY_BULLET);
	_pObj->SetLayer("Enemy_Bullet");

	GAMEMGR->CreateObject(_pObj, true);
}

