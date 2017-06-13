#include "stdafx.h"
#include "MouseRay.h"
#include "Rect.h"


Rect::Rect()
	: m_vPos(0, 0, 0)
	, m_vRot(0, 0, 0)
	, m_vScale(1, 1, 1)
	, m_vDir(0, 0, 1)
	, m_vOrgDir(0, 0, 1)
	, m_fRadius(1)
{
	D3DXMatrixIdentity(&m_mTM);
	D3DXMatrixIdentity(&m_mTrans);
	D3DXMatrixIdentity(&m_mRot);
	D3DXMatrixIdentity(&m_mScale);
}


Rect::~Rect()
{
	Release();
}

void Rect::Init()
{
	m_arrRect[0].vPos = D3DXVECTOR3(-50, 0, -50);
	m_arrRect[0].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

	m_arrRect[1].vPos = D3DXVECTOR3(-50, 0, 50);
	m_arrRect[1].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

	m_arrRect[2].vPos = D3DXVECTOR3(50, 0, 50);
	m_arrRect[2].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

	m_arrRect[3].vPos = D3DXVECTOR3(-50, 0, -50);
	m_arrRect[3].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

	m_arrRect[4].vPos = D3DXVECTOR3(50, 0, 50);
	m_arrRect[4].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

	m_arrRect[5].vPos = D3DXVECTOR3(50, 0, -50);
	m_arrRect[5].color = D3DXCOLOR(0.5f, 0.8f, 0, 1);

}

void Rect::Update(float dTime)
{
//	m_vPos.z = 10;
	//m_vRot.y += D3DX_PI * dTime;


	D3DXMatrixTranslation(&m_mTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMatrixRotationYawPitchRoll(&m_mRot, m_vRot.y, m_vRot.x, m_vRot.z);

	m_mTM = m_mScale * m_mRot * m_mTrans;
}

void Rect::Render()
{
	DWORD dwState;
	DEVICE->GetRenderState(D3DRS_FILLMODE, &dwState);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_COLOR::FORMAT::FVF));
	DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		2,
		&m_arrRect,
		sizeof(D3DFVF_XYZ_COLOR)
	);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DEVICE->SetRenderState(D3DRS_FILLMODE, dwState);
}

void Rect::Release()
{
}

D3DXVECTOR3 Rect::GetPickPos(MouseRay ray)
{
	D3DXVECTOR3 vResult(0, 0, 0);
	float _u, _v, _dist;

	if (D3DXIntersectTri(&m_arrRect[0].vPos, &m_arrRect[1].vPos, &m_arrRect[2].vPos, &ray.GetPos(), &ray.GetDir(), &_u, &_v, &_dist))
	{
//		MessageBox(NULL, "위쪽 삼각형 픽킹", "성공", MB_OK);
		vResult = ray.GetPos() + ray.GetDir() * _dist;

//		vResult = m_arrRect[0].vPos + (_u * (m_arrRect[1].vPos - m_arrRect[0].vPos)) + (_v * (m_arrRect[2].vPos - m_arrRect[0].vPos));
	}

	if (D3DXIntersectTri(&m_arrRect[3].vPos, &m_arrRect[4].vPos, &m_arrRect[5].vPos, &ray.GetPos(), &ray.GetDir(), &_u, &_v, &_dist))
	{
//		MessageBox(NULL, "아래쪽 삼각형 픽킹", "성공", MB_OK);
		vResult = ray.GetPos() + ray.GetDir() * _dist;
//		vResult = m_arrRect[3].vPos + (_u * (m_arrRect[4].vPos - m_arrRect[3].vPos)) + (_v * (m_arrRect[5].vPos - m_arrRect[3].vPos));
	}

	return vResult;
}
