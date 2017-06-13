#pragma once
class StartScene : public BaseScene
{
	Time m_Time;
	Image* m_pLogoImage;
	Image* m_pBack;
	Map m_Map;

	BLENDFUNCTION m_bf;

public:

	virtual void Init(HDC _hDC);	//이 네가지는 필수.
	virtual void Update();
	virtual void Render();
	virtual void Release();

	StartScene();
	virtual ~StartScene();
};

