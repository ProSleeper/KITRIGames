#pragma once
class RotateEnemy : public BulletEnemy
{
	float m_fRot;
	float m_fRotSpeed;
	float m_fRadius;

public:
	virtual bool Update();

public:
	RotateEnemy();
	virtual ~RotateEnemy();
};

