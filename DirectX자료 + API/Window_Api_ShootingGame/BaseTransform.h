#pragma once
class BaseTransform
{
protected:
	float m_fPosX;
	float m_fPosY;
	int m_iWidth;
	int m_iHeight;

	bool m_bCollider;
	OBJECTTAG m_Tag;

	PROPERTY_FUNC(bool, Collider, m_bCollider)
	PROPERTY_FUNC(OBJECTTAG, Tag, m_Tag)

protected:
	char m_szLayer[32];
public :
	char* GetLayer() 
	{
		return m_szLayer;
	}
	void SetLayer(char* _layer)
	{
		strcpy_s(m_szLayer, _layer);
	}



	PROPERTY_FUNC(float, PosX, m_fPosX)
	PROPERTY_FUNC(float, PosY, m_fPosY)
	PROPERTY_FUNC(int, Width, m_iWidth)
	PROPERTY_FUNC(int, Height, m_iHeight)
public:
	BaseTransform();
	virtual ~BaseTransform();
};

