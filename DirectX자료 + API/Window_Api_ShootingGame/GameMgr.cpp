#include "GameCommon.h"

GameMgr::GameMgr()
{
	m_CurrScene = NULL;
	m_NextScene = NULL;
	m_enSceneType = ST_START;
}

GameMgr::~GameMgr()
{
	Release();
}

void GameMgr::CreateObject(BaseTransform* _pObj,
	bool _bColl)
{
	if (m_enSceneType != ST_GAME) return;
	GameScene* _pScene = (GameScene*)m_CurrScene;
	_pScene->CreateObject(_pObj, _bColl);
}

void GameMgr::Init()
{
	m_hDC = GetDC(WINMGR->GethWnd());
	IMAGEMGR->LoadImages(m_hDC);

	m_Scenes[ST_START] = new StartScene;
	m_Scenes[ST_START]->Init(m_hDC);

	m_Scenes[ST_GAME] = new GameScene;
	m_Scenes[ST_GAME]->Init(m_hDC);

	m_Scenes[ST_ENDING] = new EndingScene;
	m_Scenes[ST_ENDING]->Init(m_hDC);

	m_CurrScene = m_Scenes[m_enSceneType];
}

void GameMgr::Loop()
{
	if (FRAMEMGR->LimitFps(100) == false)
		return;

	Update();
	Render();
}

void GameMgr::Update()
{
	m_CurrScene->Update();

	if (m_NextScene == NULL) return;
	

	m_CurrScene = m_NextScene;
	m_NextScene = NULL;
}

void GameMgr::Render()
{
	m_CurrScene->Render();
}

void GameMgr::Release()
{
	ReleaseDC(WINMGR->GethWnd(), m_hDC);
}

void GameMgr::ChangeScene(SCENETYPE _type)
{
	if (m_enSceneType == _type) return;

	m_enSceneType = _type;
	m_NextScene = m_Scenes[_type];
}