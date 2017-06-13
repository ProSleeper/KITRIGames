#include "GameCommon.h"



BaseTargetObject::BaseTargetObject()
{
	m_bLife = true;
	m_fSpeed = 1;
	m_iHP = 1;
	m_iMaxHP = 1;
}

BaseTargetObject::~BaseTargetObject()
{
}

void BaseTargetObject::OnHit(int _damage)
{
	m_iHP -= _damage;
	if (m_iHP <= 0)
	{
 		m_bLife = false;
	}
}
