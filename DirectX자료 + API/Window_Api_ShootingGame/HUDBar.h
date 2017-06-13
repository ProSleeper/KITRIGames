#pragma once
class HUDBar : public BaseImageObject
{
	Image* m_pBackImage;
	BaseTargetObject* m_pTarget;
	int*		m_pTargetHP;
	int			m_pMaxHP;
	int			m_iDrawWidth;

public:
	void Init(BaseTargetObject* pTarget,
		IMAGETYPE _backType, IMAGETYPE _imageType);
	bool Update();
	void Render(HDC _backDC);

public:
	HUDBar();
	virtual ~HUDBar();
};

