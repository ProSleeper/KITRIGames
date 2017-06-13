#include "GameCommon.h"

BossEnemy::BossEnemy()
{
	m_Tag = TAG_BOSS;
	strcpy_s(m_szLayer, "Enemy_Boss");

	m_iFirePos = 100;
	m_fAngle = 0.0f;
	m_fAngleSpeed = 0.1f;
	m_enType = FT_GENERAL;
	m_fFireDelayTime = 0.2f;
}

BossEnemy::~BossEnemy()
{
}

bool BossEnemy::Update()
{
	if (m_fPosY > m_iFirePos && m_bFire == false
		&& m_bDown == true)
	{
		m_bFire = true;
		m_bDown = false;
		// m_dwOldTime = timeGetTime();
		m_BulletTime.SetUpTime(m_fFireDelayTime);
	}
	else if (m_bDown)
	{
		m_fSpeed = 3.0f;
		m_fPosY += m_fSpeed;
	}

	if (m_bFire)
	{
		switch (m_enType)
		{
		case FT_GENERAL:
			General_Attack();
			break;
		case FT_SKILL1:
			Skill1_Attack();
			break;
		case FT_SKILL2:
			Skill2_Attack();
			break;
		case FT_SKILL3:
			Skill3_Attack();
			break;
		case FT_SKILL4:
			Skill4_Attack();
			break;
		}
	}

	return true;
}

void BossEnemy::General_Attack()
{
	if (m_fSpeed > 0)
	{
		if (m_fPosX + m_iWidth > WINMGR->GetWidth())
			m_fSpeed *= -1;
	}
	else
	{
		if(m_fPosX < 0)
			m_fSpeed *= -1;
	}

	m_fPosX += m_fSpeed;

	//m_dwCurrTime = timeGetTime();
	//if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)
	if(m_BulletTime.TimeCheck())
	{
		Fire();
		// m_dwOldTime = m_dwCurrTime;
	}

	if (m_iHP < 90)
		m_enType = FT_SKILL1;

}

void BossEnemy::Skill1_Attack()
{
	if (m_fSpeed > 0)
	{
		if (m_fPosX + m_iWidth > WINMGR->GetWidth())
			m_fSpeed *= -1;
	}
	else
	{
		if (m_fPosX < 0)
			m_fSpeed *= -1;
	}
	m_fPosX += m_fSpeed;

	//m_dwCurrTime = timeGetTime();
	//if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)
	if (m_BulletTime.TimeCheck())
	{
		Fire(0,3.0f);
		Fire(3.14f / 4, 3.0f);
		Fire(-3.14f/ 4, 3.0f);
		// m_dwOldTime = m_dwCurrTime;
	}

	if (m_iHP < 80)
	{
		m_enType = FT_SKILL2;
		m_fFireDelayTime = 0.05f;
		m_BulletTime.SetUpTime(m_fFireDelayTime);
	}
}

void BossEnemy::Skill2_Attack()
{
	m_fAngle += m_fAngleSpeed;
	// m_dwCurrTime = timeGetTime();
	// if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)
	if (m_BulletTime.TimeCheck())
	{
		Fire(m_fAngle, 5.0f);
		// m_dwOldTime = m_dwCurrTime;
	}

	if (m_iHP < 70)
	{
		m_enType = FT_SKILL3;
		m_fFireDelayTime = 1;
		m_BulletTime.SetUpTime(m_fFireDelayTime);
	}
}

void BossEnemy::Skill3_Attack()
{
	if (m_fSpeed > 0)
	{
		if (m_fPosX + m_iWidth > WINMGR->GetWidth())
			m_fSpeed *= -1;
	}
	else
	{
		if (m_fPosX < 0)
			m_fSpeed *= -1;
	}

	m_fPosX += m_fSpeed;

	//m_dwCurrTime = timeGetTime();
	//if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)
	if (m_BulletTime.TimeCheck())
	{
		
		for (int i = 0; i < 360 / 12; ++i)
		{
			float angle = (3.14f * 2 / 360) 
									* (i * 12);
			Fire(angle, 3.0f);
		}
		
		//m_dwOldTime = m_dwCurrTime;
	}

	if (m_iHP < 50)
		m_enType = FT_SKILL4;
}

void BossEnemy::Skill4_Attack()
{

	if (m_fSpeed > 0)
	{
		if (m_fPosX + m_iWidth > WINMGR->GetWidth())
			m_fSpeed *= -1;
	}
	else
	{
		if (m_fPosX < 0)
			m_fSpeed *= -1;
	}

	m_fPosX += m_fSpeed;
	if (m_BulletTime.TimeCheck())
	{

		for (int i = 0; i < 360 / 12; ++i)
		{
			float angle = (3.14f * 2 / 360)
				* (i * 12);
			Fire(angle, 3.0f);
		}
	}
}
