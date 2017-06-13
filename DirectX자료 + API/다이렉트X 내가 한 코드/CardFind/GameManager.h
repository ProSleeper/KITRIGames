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

	// 카메라 //
	WorldCamera* m_pCamera;

	// 헬퍼 클래스 //
	WorldGrid*	 m_pGrid;
	WorldAxis*   m_pAxis;

	// 오브젝트 //
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

