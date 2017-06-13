#pragma once
class EnemyMgr : public Singleton<EnemyMgr>
{
	int m_iTotalEnemyCount;
	LISTOBJECT m_listEnemy;
	PROPERTYARRAY_FUNC(LISTOBJECT*,Enemys,&m_listEnemy)
	PROPERTY_FUNC(int , EnemyCount, m_iTotalEnemyCount)
public:
	void Init();
	void Update();
	void CreateEnemy(int _x, int _y,
		BaseImageObject* _pObj, bool _coll = false);
	void DeleteEnemy(BaseTransform* pTarget);

	void CreateGeneralEnemy();
	void CreateBulletEnemy();
	void CreateRotateEnemy();
	void CreateBossEnemy();


public:
	EnemyMgr();
	virtual ~EnemyMgr();
};


