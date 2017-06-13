#pragma once

enum OBJECTTYPE
{
	OT_MAP,
	OT_PLAYER,
	OT_ENEMY,
	OT_MAX
};

enum SCENETYPE
{
	ST_START,
	ST_GAME,
	ST_ENDING,
	ST_MAX,
};

class GameMgr : public Singleton<GameMgr>
{
private:
	HDC		m_hDC;
	SCENETYPE m_enSceneType;
	BaseScene* m_CurrScene;
	BaseScene* m_Scenes[ST_MAX];
	BaseScene* m_NextScene;

public:

	void CreateObject(BaseTransform* _pObj,
		bool _bColl = false);

	void Init();
	void Loop();
	void Update();
	void Render();
	void Release();

	void ChangeScene(SCENETYPE _type);

public:
	GameMgr();
	virtual ~GameMgr();
};

