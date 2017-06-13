#pragma once
class BaseTargetObject : public BaseImageObject
{
protected:
	bool m_bLife;
	float m_fSpeed;
	int m_iHP;
	int m_iMaxHP;

	PROPERTY_FUNC(bool, Life, m_bLife);
	PROPERTY_FUNC(float, Speed, m_fSpeed);
	PROPERTY_FUNC(int, HP, m_iHP);
	PROPERTY_FUNC(int, MaxHP, m_iMaxHP);

public:
	virtual void OnCollisionEnter(
				BaseTransform* _pCollObj) {};
	virtual void OnHit(int _damage = -1);

public:
	BaseTargetObject();
	virtual ~BaseTargetObject();
};

