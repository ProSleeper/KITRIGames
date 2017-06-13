#include "stdafx.h"
#include "FrameMansger.h"


FrameMansger::FrameMansger()
	: m_dwDeltaTime(0)
	, m_dwFPS(0)
	, m_dwFPSCount(0)
	, m_dwOldFPS(0)
	, m_OldDeltaTime(0)
{
	m_dwOldFPS = m_OldDeltaTime = GetTickCount();
}


FrameMansger::~FrameMansger()
{
}

void FrameMansger::Update()
{
	DWORD dwCurrTime = GetTickCount();

	m_dwDeltaTime = dwCurrTime - m_OldDeltaTime;

	m_OldDeltaTime = dwCurrTime;

	// FPS
	m_dwFPSCount++;
	if (dwCurrTime >= m_dwOldFPS + 1000)
	{
		m_dwOldFPS = dwCurrTime;
		m_dwFPS = m_dwFPSCount;
		m_dwFPSCount = 0;
	}
}
