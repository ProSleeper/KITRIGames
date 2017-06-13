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

class Rect;
class Card;
class WorldCamera;
class WorldGrid;
class WorldAxis;
class GameManager
{
	SINGLETONE(GameManager);

	// ī�޶� //
	WorldCamera* m_pCamera;

	// ���� Ŭ���� //
	WorldGrid*	 m_pGrid;
	WorldAxis*   m_pAxis;

	// ������Ʈ //
	Rect* m_pRect;
	int mReset;
	D3DLIGHT9	 m_Light;
	int mClick;
public:
	void Setup(void);
	void GameLoop(void);
	void Update(float dTime);
	void Render(void);
	void DrawDebugFont();
	void Release(void);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	D3DXVECTOR3 ClickCoord();
};

