#include "GameCommon.h"



EndingScene::EndingScene()
{
	m_pEndingImage = NULL;
	m_rcDraw.left = 0;
	m_rcDraw.top = 0;
	m_rcDraw.right = WINMGR->GetWidth();
	m_rcDraw.bottom = WINMGR->GetHeight();
}


EndingScene::~EndingScene()
{

}

void EndingScene::Init(HDC _hDC)
{
	m_hDC = _hDC;
	m_pEndingImage = IMAGEMGR->GetImage(
		IT_ENDING);
	m_pBack = IMAGEMGR->GetImage(IT_BACK);
	m_Map.Init(0, 0, 670, 800, IT_MAP);
	m_Time.SetUpTime(0.01f);

}
void EndingScene::Update()
{
	if (m_Time.TimeCheck())
	{
		if (m_rcDraw.top + WINMGR->GetHeight()
			< m_pEndingImage->GetHeight())
			OffsetRect(&m_rcDraw, 0, 1);
	}
}

void EndingScene::Render()
{
	m_Map.Render(m_pBack->GetMemDC());
	m_pEndingImage->RenderImage(m_pBack->GetMemDC(),
		0, 0, WINMGR->GetWidth(),
		WINMGR->GetHeight(), m_rcDraw);

	BitBlt(m_hDC, 0, 0, WINMGR->GetWidth(),
		WINMGR->GetHeight(), m_pBack->GetMemDC(),
		0, 0, SRCCOPY);
}

void EndingScene::Release()
{

}