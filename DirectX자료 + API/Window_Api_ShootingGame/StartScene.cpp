#include "GameCommon.h"



StartScene::StartScene()
{
	m_pLogoImage = NULL;
	ZeroMemory(&m_bf, sizeof(m_bf));
}


StartScene::~StartScene()
{
}

void StartScene::Init(HDC _hDC)
{
	m_hDC = _hDC;
	m_pBack = IMAGEMGR->GetImage(IT_BACK);
	m_pLogoImage = IMAGEMGR->GetImage(IT_LOGO);
	m_Map.Init(0, 0, 670, 800, IT_MAP);

	m_bf.SourceConstantAlpha = 255;
	m_Time.SetUpTime(0.01f); 
}

void StartScene::Update()
{
	m_Map.Update();
	if (m_Time.TimeCheck())
	{
		if (m_bf.SourceConstantAlpha > 0)
			m_bf.SourceConstantAlpha--;
		
		else
			GAMEMGR->ChangeScene(ST_GAME);
	}
}

void StartScene::Render()
{
	m_Map.Render(m_pBack->GetMemDC());
	m_pLogoImage->RenderImage(m_pBack->GetMemDC(), 0, 0, m_bf);
	


	BitBlt(m_hDC, 0, 0, WINMGR->GetWidth(),
		WINMGR->GetHeight(), m_pBack->GetMemDC(), 0, 0, SRCCOPY);
}

void StartScene::Release()
{

}
