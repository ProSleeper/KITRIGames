#include "GameCommon.h"

EnemyMgr::EnemyMgr()
{
	m_iTotalEnemyCount = 0;
}

EnemyMgr::~EnemyMgr()
{
}

void EnemyMgr::Init()
{
	//CreateEnemy(10, 10, IT_ENEMY, true);
	//CreateEnemy(300, 10, IT_ENEMY, true);
	//CreateEnemy(500, 10, IT_ENEMY, true);
}


void EnemyMgr::Update()
{
	//if ((int)m_listEnemy.size() <= 5)
	//{
	//	int _rndX = rand() % WINMGR->GetWidth();
	//	CreateEnemy(_rndX, 10, IT_ENEMY, true);
	//}

	if (m_iTotalEnemyCount < 1)
		CreateBulletEnemy();
	else if (m_iTotalEnemyCount < 2)
		CreateBulletEnemy();
	else if (m_iTotalEnemyCount < 3)
		CreateBulletEnemy();
	else if (m_iTotalEnemyCount == 3)
		CreateBossEnemy();
}

void EnemyMgr::DeleteEnemy(BaseTransform* pTarget)
{
	for (OBJECTITOR itor = m_listEnemy.begin();
		itor != m_listEnemy.end();)
	{
		if (*itor == pTarget)
		{
			itor = m_listEnemy.erase(itor);
			break;
		}
		else
			++itor;
	}
}

void EnemyMgr::CreateEnemy(int _x, int _y,
	BaseImageObject* _pObj, bool _coll)
{
	m_iTotalEnemyCount++;

	while (true)
	{
		if (COLLMGR->RePosCheck(_pObj))
			break;
		else
		{
			int _rndX = rand() % WINMGR->GetWidth();
			_pObj->SetPosX(_rndX);
		}
	}

	GAMEMGR->CreateObject(_pObj, _coll);
	m_listEnemy.push_back(_pObj);
}


void EnemyMgr::CreateGeneralEnemy()
{
	if ((int)m_listEnemy.size() <= 5)
	{
		Enemy* _pObj = new Enemy;

		int _rndX = rand() % WINMGR->GetWidth();
		_pObj->Init(_rndX, 10, IT_ENEMY);
		_pObj->SetTag(TAG_ENEMY);
		_pObj->SetSpeed(5.0f);
		CreateEnemy(_rndX, 10, _pObj, true);
	}
}

void EnemyMgr::CreateBulletEnemy()
{
	if ((int)m_listEnemy.size() <= 5)
	{
		BulletEnemy* _pObj = new BulletEnemy;

		int _rndX = rand() % WINMGR->GetWidth();
		_pObj->Init(_rndX, 10, IT_ENEMY);
		_pObj->SetTag(TAG_ENEMY);
		_pObj->SetSpeed(5.0f);
		CreateEnemy(_rndX, 10, _pObj, true);
	}
}

void EnemyMgr::CreateRotateEnemy()
{
	if ((int)m_listEnemy.size() <= 5)
	{
		RotateEnemy* _pObj = new RotateEnemy;

		int _rndX = rand() % WINMGR->GetWidth();
		_pObj->Init(_rndX, 10, IT_ENEMY);
		_pObj->SetTag(TAG_ENEMY);
		_pObj->SetSpeed(5.0f);
		CreateEnemy(_rndX, 10, _pObj, true);
	}
}

void EnemyMgr::CreateBossEnemy()
{
	m_iTotalEnemyCount++;

	BossEnemy* _pObj = new BossEnemy;

	_pObj->Init(
		WINMGR->GetWidth() / 2 - _pObj->GetWidth() / 2,
		-_pObj->GetHeight(),
		IT_BOSSENEMY
	);

	_pObj->SetSpeed(1.0f);
	_pObj->SetHP(100);
	_pObj->SetMaxHP(100);


	GAMEMGR->CreateObject(_pObj, true);
	m_listEnemy.push_back(_pObj);

	HUDBar*  _pHud = new HUDBar;
	_pHud->Init(_pObj, IT_HUDBACK, IT_HUD);
	GAMEMGR->CreateObject(_pHud, false);
}
