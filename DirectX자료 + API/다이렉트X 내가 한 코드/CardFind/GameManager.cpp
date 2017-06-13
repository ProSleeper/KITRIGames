#include "stdafx.h"
#include "WorldGrid.h"
#include "WorldCamera.h"
#include "WorldAxis.h"
#include "MouseRay.h"
#include "Rect.h"
#include "Card.h"
#include "GameManager.h"


GameManager::GameManager()
	: m_pCamera(NULL)
	, m_pGrid(nullptr)
	, mReset(0)
	, mClick(0)
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

	m_Light.Type = D3DLIGHT_DIRECTIONAL; // 태양광
	m_Light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	m_Light.Direction = D3DXVECTOR3(0, -1, 0);
	//             인덱스는 최대 8개까지 가능
	DEVICE->SetLight(0, &m_Light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1));
	// 카메라 셋업 //
	m_pCamera = new WorldCamera;
	m_pCamera->SetUp(D3DXVECTOR3(0, 90, -0.01f));
	//                     카메라 위치

	// 헬퍼 클래스 //
	m_pGrid = new WorldGrid;  // 그리드 아직 안함
	m_pGrid->Setup();
	m_pAxis = new WorldAxis;
	m_pAxis->Setup();
	OBJMGR->CreateObject();

	// 오브젝트 //

	m_pRect = new Rect;
	m_pRect->Init();
}

void GameManager::GameLoop(void)
{
	FRAMEMGR->Update();

	float dTime = FRAMEMGR->GetDeltaTime();

	Update(dTime);
	Render();
}

void GameManager::Update(float dTime)
{
	INPUTMGR->Update();
	OBJMGR->UpdateObject(dTime);
	
	m_pRect->Update(dTime);

	if(INPUTMGR->GetKeyDown(VK_F1))
	{
		mReset++;
		if (mReset > 1)
		{
			mReset = 0;
			OBJMGR->ReleaseObject();
			OBJMGR->CreateObject();
		}
	}

	if (INPUTMGR->GetKeyDown(VK_LBUTTON))
	{
		//두번클릭해야하는 오류 고쳐야하고.. 뭔가 로직을 바꿔야할듯!
		OBJMGR->CollisionObject(dTime);
	}
}

void GameManager::Render(void)
{
	DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.6f, 0.6f, 0.6f, 1), 1, 0);
	
	DEVICE->BeginScene();
	{
		for(int i = 0; i < 8; i++)
		{
			DEVICE->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			DEVICE->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			DEVICE->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, 16);
			DEVICE->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		}
		OBJMGR->RenderObject();
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

	FONTMGR->DrawText(_x, _y += 15, _color, "오브젝트 숫자 : %d", OBJMGR->ListSize());

}

void GameManager::Release(void)
{
	SAFE_DELETE(m_pRect);
	SAFE_DELETE(m_pCamera);
}

void GameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, message, wParam, lParam);
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
