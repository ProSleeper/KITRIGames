#pragma once
class EndingScene : public BaseScene
{
	Image* m_pEndingImage;
	Image* m_pBack;
	Map m_Map;


	Time m_Time;
	RECT m_rcDraw;


public:
	virtual void Init(HDC _hDC);
	virtual void Update();
	virtual void Render();
	virtual void Release();

public :
	EndingScene();
	virtual ~EndingScene();
};

