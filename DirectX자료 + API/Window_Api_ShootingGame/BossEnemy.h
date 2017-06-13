#pragma once

enum FIRE_TYPE {
	FT_GENERAL,
	FT_SKILL1,
	FT_SKILL2,
	FT_SKILL3,
	FT_SKILL4,
};

class BossEnemy : public BulletEnemy
{
	FIRE_TYPE m_enType;
	float m_fAngle;
	float m_fAngleSpeed;

public :
	virtual bool Update();
	void General_Attack();
	void Skill1_Attack();
	void Skill2_Attack();
	void Skill3_Attack();
	void Skill4_Attack();
	
public:
	BossEnemy();
	virtual ~BossEnemy();
};

