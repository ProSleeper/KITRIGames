#pragma once
class Explosion : public BaseImageObject
{
	int		m_iTotalWidth;
	int		m_iTotalHeight;
	int		m_iTotalTime;

	int		m_iFrameX;
	int		m_iFrameY;
	int		m_iCurrFrameX;
	int		m_iCurrFrameY;
	int		m_iCurrFrame;
	int		m_iTotalFrame;
	int		m_iNextTime;
	int		m_iCurrTime;
	int		m_iOldTime;
	int		m_iCalTime;

	PROPERTY_FUNC(int, TotalTime, m_iTotalTime)
	PROPERTY_FUNC(int, FrameX, m_iFrameX)
	PROPERTY_FUNC(int, FrameY, m_iFrameY)
	PROPERTY_FUNC(int, CurrFrame, m_iCurrFrame)
	PROPERTY_FUNC(int, CurrFrameX, m_iCurrFrameX)
	PROPERTY_FUNC(int, CurrFrameY, m_iCurrFrameY)
	PROPERTY_FUNC(int, CurrTime, m_iCurrTime)

public:
	void Init(int _x, int _y, int _w, int _h,
		int _tw, int _th, int _ttime, IMAGETYPE _type);
	bool Update();
	void Render(HDC _backDC);

public:
	Explosion();
	virtual ~Explosion();
};

