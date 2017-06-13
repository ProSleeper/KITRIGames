#pragma once
class BaseImageObject : public BaseTransform
{
protected:
	Image* m_pImage;
	PROPERTY_FUNC(Image*, Image, m_pImage)
	
public :
	virtual void Init(
		int _x, int _y, int _w, int _h, IMAGETYPE _type);
	virtual void Init(
		int _x, int _y, IMAGETYPE _type);
	virtual bool Update() { return true; }
	virtual void Render(HDC _backDC);

	virtual void Render(
		HDC _backDC, Image* _pback, int _w);

	virtual void Release() {};

public:
	BaseImageObject();
	virtual ~BaseImageObject();
};

