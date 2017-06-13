#pragma once
class Time
{
	DWORD m_dwCurrTime = 0;
	DWORD m_dwOldTime = 0;
	int m_iDelayTime = 0;

public:
	void SetUpTime(float _delTimeSecond);
	bool TimeCheck();

public:
	Time();
	virtual ~Time();
};

