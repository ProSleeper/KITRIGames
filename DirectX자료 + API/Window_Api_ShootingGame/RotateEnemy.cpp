#include "GameCommon.h"

RotateEnemy::RotateEnemy()
{
	strcpy_s(m_szLayer, "Enemy_Rotate");
	m_iFirePos = 90;
	m_fFireDelayTime = 0.2f;

	m_fRot = 0.0f;
	m_fRotSpeed = 0.05f;
	m_fRadius = 5.0f;
}

RotateEnemy::~RotateEnemy()
{
}

bool RotateEnemy::Update()
{
	if (m_fPosY > WINMGR->GetHeight())
		return false;

	if (m_fPosY > m_iFirePos && m_bFire == false
		&& m_bDown == true)
	{
		m_bFire = true;
		m_bDown = false;
		// m_dwOldTime = timeGetTime();
		m_BulletTime.SetUpTime(m_fFireDelayTime);
	}

	if (m_bDown)
		m_fPosY += m_fSpeed;

	if (m_bFire && m_bDown == false)
	{
		m_fRot += m_fRotSpeed;

		if (m_fRot < 3.14f * 2)
		{
			m_fPosX += m_fRadius * cos(m_fRot);
			m_fPosY += m_fRadius * sin(m_fRot);
		}
		else
			m_bDown = true;

		//m_dwCurrTime = timeGetTime();

		//if (m_dwCurrTime > m_dwOldTime + m_iFireDelayTime)
		if(m_BulletTime.TimeCheck())
		{
			Fire();
			//m_dwOldTime = m_dwCurrTime;
		}
	}
	return true;

}
