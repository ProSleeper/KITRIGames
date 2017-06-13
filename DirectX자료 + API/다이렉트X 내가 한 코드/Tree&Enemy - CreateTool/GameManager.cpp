#include "stdafx.h"
#include "WorldAxis.h"
#include "WorldCamera.h"
#include "WorldGrid.h"
#include "MouseRay.h"
#include "GameManager.h"

#include "Player.h"
#include "Rect.h"
#include "Enemy.h"
#include "Tree.h"
#include "CreateObject.h"

GameManager::GameManager()
	: m_pPlayer(NULL)
	, m_pCamera(NULL)
	, m_pAxis(NULL)
	, mMode(EDITMODE::EM_ADD_TREE)
{
}


GameManager::~GameManager()
{
	Release();
}

void GameManager::Setup(void)
{
	DXMGR->Setup();
	INPUTMGR->SetUp();
	FONTMGR->Setup();

	// 카메라 셋업 //
	m_pCamera = new WorldCamera;
	m_pCamera->SetUp(D3DXVECTOR3(0, 5, -5));
	//                     카메라 위치

	// 헬퍼 클래스 //
	m_pAxis = new WorldAxis;
	m_pAxis->Setup();
	m_pGrid = new WorldGrid;  // 그리드 아직 안함
	m_pGrid->Setup();



	// 오브젝트 //
	mObjectFactory = new CreateObject;
	m_pPlayer = new Player;
	m_pPlayer->Init();

	m_pRect = new Rect;
	m_pRect->Init();

	m_pPlayer->SetTarget(m_pRect);
}

void GameManager::GameLoop(void)
{
	FRAMEMGR->Update();

	float dTime = FRAMEMGR->GetDeltaTime();

	Update(dTime);
	Render();
}
POINT pt;
void GameManager::Update(float dTime)
{
	INPUTMGR->Update();
	OBJMGR->UpdateObject(dTime);
	
	m_pPlayer->Update(dTime);
	m_pRect->Update(dTime);

	if(INPUTMGR->GetKeyDown(VK_F1))
	{
		mMode = (mMode == EDITMODE::EM_ADD_TREE) ? EDITMODE::EM_ADD_ENEMY : EDITMODE::EM_ADD_TREE;
		OBJMGR->OffEdit();
	}
	if(INPUTMGR->GetKeyDown(VK_F2))
	{
		mMode = EDITMODE::EM_MOVE_OBJECT;
		OBJMGR->OnEdit();
	}
	if(INPUTMGR->GetKeyDown(VK_F3))
	{
		mMode = EDITMODE::EM_DELETE_OBJECT;
		OBJMGR->OnEdit();
	}

	if (INPUTMGR->GetKeyDown(VK_LBUTTON))
	{
		switch(mMode)
		{
			case EDITMODE::EM_ADD_TREE:
			{
				OBJMGR->CreateObject(mObjectFactory->ClickCreate(OBJECT::OB_TREE, ClickCoord()));
			}
			break;
			case EDITMODE::EM_ADD_ENEMY:
			{
				OBJMGR->CreateObject(mObjectFactory->ClickCreate(OBJECT::OB_ENEMY, ClickCoord()));
			}
			break;
			case EDITMODE::EM_MOVE_OBJECT:
			{
				mMoveObject = OBJMGR->SelectObject(dTime);
			}
			break;
			case EDITMODE::EM_DELETE_OBJECT:
			{
				OBJMGR->CollisionObject(dTime);
			}
			break;
			default:
				break;
		}
	}

	if(INPUTMGR->GetKey(VK_LBUTTON) && mMoveObject != nullptr)
	{
		mMoveObject->SetVPos(ClickCoord());
	}
	if(INPUTMGR->GetKeyUp(VK_LBUTTON))
	{
		mMoveObject = nullptr;
	}
}

void GameManager::Render(void)
{
	DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.6f, 0.6f, 0.6f, 1), 1, 0);
	
	DEVICE->BeginScene();
	{
		// 아래부터 그리기
		m_pPlayer->Render();
		m_pRect->Render();
		OBJMGR->RenderObject();

		// 오브젝트 다 그리고 헬퍼 클레스 그리기
		m_pGrid->Render();
		m_pAxis->Render();

		// 폰트는 가장 마지막
		DrawDebugFont();
	}
	DEVICE->EndScene();
	DEVICE->Present(NULL, NULL, NULL, NULL);
}

void GameManager::DrawDebugFont()
{
	int _x = 10;
	int _y = 10;

	D3DXCOLOR _color = D3DXCOLOR(0, 1, 0, 1);

	FONTMGR->DrawText(_x, _y, _color, "FPS : %d", FRAMEMGR->GetFPS());

	// 주인공 정보
	_y += 15;
	_color = D3DXCOLOR(1, 1, 0, 1);
	FONTMGR->DrawText(_x, _y+=15, _color, "<주인공 정보> : %d");
	FONTMGR->DrawText(_x, _y += 15, _color, "- 컨트롤(←, →, ↑, ↓)");
	FONTMGR->DrawText(_x, _y += 15, _color, "- Pos(%.2f, %.2f, %.2f", m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetPos().z);

	RECT rc;
	GetClientRect(DXMGR->GethWnd(),&rc);
	FONTMGR->DrawText(_x, _y += 15, _color, "픽킹 : %s", m_pPlayer->GetIsPick() ? "성공" : "실패");
	FONTMGR->DrawText(_x, _y += 15, _color, "오브젝트 숫자 : %d", OBJMGR->ListSize());
	FONTMGR->DrawText(_x, _y += 15, _color, "현재 모드: ");
	FONTMGR->DrawText(_x , _y, D3DXCOLOR(1, 0, 0, 1), "           %s", CurrentMode().c_str());
	FONTMGR->DrawText(_x, _y += 15, _color, "마우스 좌표 %d, %d", pt.x, pt.y);
	
}

void GameManager::Release(void)
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pRect);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pAxis);
}

void GameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

string GameManager::CurrentMode()
{
	switch(mMode)
	{
		case EDITMODE::EM_ADD_TREE:
		{
			return "추가-나무";
		}
		break;
		case EDITMODE::EM_ADD_ENEMY:
		{
			return "추가-적";
		}
		break;
		case EDITMODE::EM_MOVE_OBJECT:
		{
			return "이동";
		}
		break;
		case EDITMODE::EM_DELETE_OBJECT:
		{
			return "삭제";
		}
		break;
		default:
			break;
	}
}

D3DXVECTOR3 GameManager::ClickCoord()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXMGR->GethWnd(), &pt);

	MouseRay ray;
	ray.CreateRay((int)pt.x, (int)pt.y); // 뷰공간

	D3DXMATRIX view;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	ray.RayTransForm(view);

	D3DXVECTOR3 _vPos = m_pRect->GetPickPos(ray);
	return _vPos;
}
