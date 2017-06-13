#include "stdafx.h"
#include "MouseRay.h"
#include "Rect.h"
#include "Player.h"


Player::Player()
	: m_vPos(0,0,0)
	, m_vRot(0,0,0)
	, m_vScale(1,1,1)
	, m_vDir(0,0,1)
	, m_vOrgDir(0,0,1)
	, m_pCullSphere(NULL)
	, m_pRect(NULL)
	, m_fRadius(0.5f)
{
	D3DXMatrixIdentity(&m_mTM);
	D3DXMatrixIdentity(&m_mTrans);
	D3DXMatrixIdentity(&m_mRot);
	D3DXMatrixIdentity(&m_mScale);
}


Player::~Player()
{
	Release();
}

void Player::Init()
{
	m_arrVertexs[0].vPos = D3DXVECTOR3(-1, 0, 0);
	m_arrVertexs[0].color = D3DXCOLOR(1, 0, 0, 1);

	m_arrVertexs[1].vPos = D3DXVECTOR3(0, 1, 0);
	m_arrVertexs[1].color = D3DXCOLOR(0, 1, 0, 1);

	m_arrVertexs[2].vPos = D3DXVECTOR3(1, 0, 0);
	m_arrVertexs[2].color = D3DXCOLOR(0, 0, 1, 1);

	// 노멀라인
	m_arrNormalline[0].vPos = D3DXVECTOR3(0, 0.5f, 0);
	m_arrNormalline[0].color = D3DXCOLOR(0, 1, 0, 1);

	m_arrNormalline[1].vPos = D3DXVECTOR3(0, 0.5f, 15);
	m_arrNormalline[1].color = D3DXCOLOR(0, 1, 0, 1);

	// 메쉬
	D3DXCreateSphere(DEVICE, m_fRadius, 10, 10, &m_pCullSphere, NULL);
}

void Player::Update(float dTime)
{
	if (INPUTMGR->GetKey(VK_DOWN))
	{
		if (m_pRect)
		{
			D3DXVECTOR3 vTargetDis = (m_vPos - m_vDir * 5.0f * dTime) - m_pRect->GetPos();
			if (D3DXVec3Length(&vTargetDis) > m_fRadius + m_pRect->GetRadius())
			{
				m_vPos -= m_vDir * 5.0f * dTime;
			}
		}
	}
	if (INPUTMGR->GetKey(VK_UP))
	{
		if (m_pRect)
		{
			D3DXVECTOR3 vTargetDis = (m_vPos + m_vDir * 5.0f * dTime) - m_pRect->GetPos();
			if (D3DXVec3Length(&vTargetDis) > m_fRadius + m_pRect->GetRadius())
			{
				m_vPos += m_vDir * 5.0f * dTime;
			}
		}
	}

	if (INPUTMGR->GetKey(VK_LEFT))
	{			//  ▼ 파이! 180도
		m_vRot.y -= D3DX_PI * 0.5f * dTime;
		D3DXVec3TransformNormal(&m_vDir, &m_vOrgDir, &m_mRot);
	}  // 오늘 한것중 가장 중요하다
	if (INPUTMGR->GetKey(VK_RIGHT))
	{
		m_vRot.y += D3DX_PI * 0.5f * dTime;
		D3DXVec3TransformNormal(&m_vDir, &m_vOrgDir, &m_mRot);
	} // 요것도 중요하다


	D3DXMatrixTranslation(&m_mTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMatrixScaling(&m_mScale, m_vScale.x, m_vScale.y, m_vScale.z);
	// 입력한 수만큼 정점을 곱해줌. (크기조정)

	D3DXMatrixRotationYawPitchRoll(&m_mRot, m_vRot.y, m_vRot.x, m_vRot.z);

	m_mTM = m_mScale * m_mRot * m_mTrans;  // 중심을 기준으로 공전하게 하고싶을땐 STR
										   // 중심을 기준으로 얼만큼 이동한 후 회정하게 하고싶을땐 SRT
}

void Player::Render()
{
	DWORD dwState;      //d3dcull의 기본값을 모를때 사용.dwState를 d3dcull 자리에 넣으면 됨
	DEVICE->GetRenderState(D3DRS_FILLMODE, &dwState);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  // 뒷면도 보이게하는 작업

	//DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_COLOR::FORMAT::FVF));
	DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST, // 그리는 방식
		1,					// 삼각형 갯수
		&m_arrVertexs,		// 버텍스 정보
		sizeof(D3DFVF_XYZ_COLOR) // 정점개별 사이즈
	);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // 뒷면 보이게했다가 다시 원상태로(뒷면안보이게) 하는 작업 [복구]
	DEVICE->SetRenderState(D3DRS_FILLMODE, dwState);

	// 노멀라인
	DEVICE->DrawPrimitiveUP(
		D3DPT_LINELIST, // 그리는 방식
		1,					// 삼각형 갯수
		&m_arrNormalline,		// 버텍스 정보
		sizeof(D3DFVF_XYZ_COLOR) // 정점개별 사이즈
	);

	// 메쉬
	m_mTM._42 = 0.5f;
	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pCullSphere->DrawSubset(0);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Player::Release()
{
	SAFE_RELEASE(m_pCullSphere);
}