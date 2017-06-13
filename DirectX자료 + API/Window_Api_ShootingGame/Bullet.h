#pragma once
class Bullet : public BaseTargetObject
{
	float m_fAngle;
	PROPERTY_FUNC(float, Angle, m_fAngle)
public:
	virtual bool Update();
	void ResetBullet(int _x, int _y);
	virtual void OnCollisionEnter(BaseTransform* _pColl);

public:
	Bullet();
	virtual ~Bullet();
};

