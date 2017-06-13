#include "GameCommon.h"

FrameCheckMgr::FrameCheckMgr()
{
	Init();
}


FrameCheckMgr::~FrameCheckMgr()
{
}

void FrameCheckMgr::Init()
{
	m_FpsTime.SetUpTime(1.0f);
	m_LimitTime.SetUpTime(0.01f);
	/*m_dwOldTime = timeGetTime();
	m_dwOldLimitTime = timeGetTime();*/
}

void FrameCheckMgr::Update()
{
	FpsCheck();
}

void FrameCheckMgr::FpsCheck()
{
	if (m_FpsTime.TimeCheck())
	{		
		m_iFPS = m_iFPSCount;
		m_iFPSCount = 0;
	}
	else
		m_iFPSCount++;
}

bool FrameCheckMgr::LimitFps(int _limitFps)
{
	if (m_LimitTime.TimeCheck())
	{
		return true;
	}

	return false;
}

