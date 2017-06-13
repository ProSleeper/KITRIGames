#pragma once

#define FRAMEMGR FrameMansger::GetInstance()

class FrameMansger
{
	SINGLETONE(FrameMansger);

	DWORD		m_dwDeltaTime;
	DWORD		m_OldDeltaTime;

	DWORD		m_dwFPS;
	DWORD		m_dwFPSCount;
	DWORD		m_dwOldFPS;

public:
	void Update();
	int GetFPS() { return (int)m_dwFPS; }
	float GetDeltaTime()
	{
		return m_dwDeltaTime / 1000.0f;
	}
};

