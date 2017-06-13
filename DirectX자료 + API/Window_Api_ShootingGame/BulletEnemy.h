#pragma once
class BulletEnemy : public BaseTargetObject
{
protected:
	int m_iBulletMaxCount;
	int m_iFirePos;
	float m_fFireDelayTime;

	Time m_BulletTime;

	bool m_bFire;
	bool m_bDown;
	int m_iBulletCount;

public:
	virtual bool Update();
	void Fire(float _angle = 0.0f, float _speed = 8.0f);

public:
	BulletEnemy();
	virtual ~BulletEnemy();
};

