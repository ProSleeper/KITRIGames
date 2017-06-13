#pragma once
#define BULLETMAX 10

class Player : public BaseTargetObject
{
	bool m_bSpaceKey;
	LISTBULLET m_ListBullets;
	PROPERTYARRAY_FUNC(LISTBULLET*, Bullets, &m_ListBullets)

	Enemy* m_pEnemy;

public:
	virtual bool Update();
	virtual void Render(HDC _backDC);
	//void Release();

	void FireBullet();

	virtual void OnCollisionEnter(BaseTransform* _pCollObj);


public:
	Player();
	virtual ~Player();
};

