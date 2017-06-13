#include "GameCommon.h"



Time::Time()
{
}


Time::~Time()
{
}

void Time::SetUpTime(float _delTimeSecond)
{
	m_iDelayTime = int(_delTimeSecond * 1000);
	m_dwOldTime = timeGetTime();
}

bool Time::TimeCheck()
{
	m_dwCurrTime = timeGetTime();
	if (m_dwCurrTime > m_dwOldTime + m_iDelayTime)
	{
		m_dwOldTime = m_dwCurrTime;
		return true;
	}

	return false;
}