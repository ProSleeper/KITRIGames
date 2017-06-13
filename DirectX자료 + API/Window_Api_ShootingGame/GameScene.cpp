#include "GameCommon.h"



GameScene::GameScene()
{
	m_pBack = NULL;
	m_Player = NULL;
}


GameScene::~GameScene()
{
}

void GameScene::CreateObject(BaseTransform* _pObj,
	bool _bColl)
{
	m_listObjects.push_back(_pObj);
	if (_bColl)
	{
		_pObj->SetCollider(true);
		COLLMGR->CreateCollider(_pObj);
	}
}

void GameScene::DeleteObject()
{
	for (OBJECTITOR itor = m_listObjects.begin();
		itor != m_listObjects.end();)
	{
		BaseTargetObject* _pObj = (BaseTargetObject*)*itor;
		if (_pObj->GetLife() == false)
		{
			ENEMYMGR->DeleteEnemy(*itor);

			if (_pObj->GetCollider() == true)
				COLLMGR->DeleteCollider(*itor);

			delete _pObj;
			itor = m_listObjects.erase(itor);
		}
		else
			itor++;
	}
}

void GameScene::DebugView()
{
	int _x = 10;
	int _y = 10;
	char cTextBuffer[128] = { 0, };

	sprintf_s(cTextBuffer, "FPS : %d",
		FRAMEMGR->GetFPS());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	_y += 20;
	sprintf_s(cTextBuffer, "<오브젝트 정보>");
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	sprintf_s(cTextBuffer, "- 오브젝트 갯수 : %d",
		(int)m_listObjects.size());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	_y += 20;
	sprintf_s(cTextBuffer, "<콜라이더 정보>");
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	sprintf_s(cTextBuffer, "- 콜라이더 갯수 : %d",
		(int)COLLMGR->GetCollider()->size());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	_y += 20;
	sprintf_s(cTextBuffer, "<적 정보>");
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	sprintf_s(cTextBuffer, "- 적 갯수 : %d",
		(int)ENEMYMGR->GetEnemys()->size());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	sprintf_s(cTextBuffer, "- 총 적 갯수 : %d",
		(int)ENEMYMGR->GetEnemyCount());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	_y += 20;
	sprintf_s(cTextBuffer, "<이펙트 정보>");
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));

	sprintf_s(cTextBuffer, "- 이펙트 갯수 : %d",
		(int)EFFECTMGR->GetlistEffects()->size());
	TextOut(m_pBack->GetMemDC(), _x, _y += 20,
		cTextBuffer, strlen(cTextBuffer));
}

void GameScene::Init(HDC _hDC)
{
	m_hDC = _hDC;

	
	m_pBack = IMAGEMGR->GetImage(IT_BACK);

	m_Map.Init(0, 0, 670, 800, IT_MAP);
	m_Player = new Player;
	m_Player->Init(WINMGR->GetWidth() / 2,
		WINMGR->GetHeight() - 120, 50, 60, IT_PLAYER);
	m_Player->SetTag(TAG_PLAYER);
	m_Player->SetSpeed(5);

	CreateObject(&m_Map, false);
	CreateObject(m_Player, true);

	ENEMYMGR->Init();
}

void GameScene::Update()
{
	FRAMEMGR->Update();

	for (OBJECTITOR itor = m_listObjects.begin();
		itor != m_listObjects.end(); itor++)
	{
		if (strcmp((*itor)->GetLayer(), "None") == 0)
		{
			BaseImageObject* _pObj =
				(BaseImageObject*)(*itor);
			_pObj->Update();
		}
		else
		{
			BaseTargetObject* _pObj =
				(BaseTargetObject*)(*itor);
			if (_pObj->Update() == false)
			{
				_pObj->SetLife(false);
			}
		}
	}
	COLLMGR->Update();
	ENEMYMGR->Update();
	EFFECTMGR->Update();
	DeleteObject();
}

void GameScene::Render()
{
	for (OBJECTITOR itor = m_listObjects.begin();
		itor != m_listObjects.end(); itor++)
	{
		BaseImageObject* _pObj =
			(BaseImageObject*)(*itor);
		_pObj->Render(m_pBack->GetMemDC());
	}

	COLLMGR->Render(m_pBack->GetMemDC());
	EFFECTMGR->Render(m_pBack->GetMemDC());

	DebugView();

	BitBlt(m_hDC, 0, 0,
		WINMGR->GetWidth(), WINMGR->GetHeight(),
		m_pBack->GetMemDC(), 0, 0, SRCCOPY);
}

void GameScene::Release()
{
	
}