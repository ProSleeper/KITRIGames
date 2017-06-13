#pragma once


enum class EDITMODE
{
	EM_ADD_TREE,
	EM_ADD_ENEMY,
	EM_MOVE_OBJECT,
	EM_DELETE_OBJECT,
	EM_MAX
};

#define GAMEMGR GameManager::GetInstance()

class BaseObject;
class Player;
class Rect;
class Enemy;
class Tree;

class WorldCamera;
class WorldAxis;
class WorldGrid;
class CreateObject;
class GameManager
{
	SINGLETONE(GameManager);

	// ī�޶� //
	WorldCamera* m_pCamera;

	// ���� Ŭ���� //
	WorldAxis*   m_pAxis;
	WorldGrid*	 m_pGrid;

	// ������Ʈ //
	Player* m_pPlayer;
	Rect* m_pRect;
	CreateObject* mObjectFactory;
	EDITMODE mMode;
	BaseObject* mMoveObject;
	int mCount = 0;

public:
	void Setup(void);
	void GameLoop(void);
	void Update(float dTime);
	void Render(void);
	void DrawDebugFont();
	void Release(void);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	string CurrentMode();
	D3DXVECTOR3 ClickCoord();
};

