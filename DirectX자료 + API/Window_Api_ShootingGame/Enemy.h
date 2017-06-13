#pragma once
class Enemy : public BaseTargetObject
{
public:
	virtual bool Update();

public:
	Enemy();
	virtual ~Enemy();
};

