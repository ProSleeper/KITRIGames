#pragma once
class FrameCheckMgr : public Singleton<FrameCheckMgr>
{
	/*DWORD m_dwCurrTime = 0;
	DWORD m_dwOldTime = 0;

	DWORD m_dwCurrLimitTime = 0;
	DWORD m_dwOldLimitTime = 0;*/

	Time m_FpsTime;
	Time m_LimitTime;

	int m_iFPS = 0;
	int m_iFPSCount = 0;

	PROPERTY_FUNC(int, FPS, m_iFPS)

public:
	void Init();
	void Update();
	void FpsCheck();
	bool LimitFps(int _limitFps);

public:
	FrameCheckMgr();
	virtual ~FrameCheckMgr();
};

