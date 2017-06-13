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

	// ��ֶ���
	m_arrNormalline[0].vPos = D3DXVECTOR3(0, 0.5f, 0);
	m_arrNormalline[0].color = D3DXCOLOR(0, 1, 0, 1);

	m_arrNormalline[1].vPos = D3DXVECTOR3(0, 0.5f, 15);
	m_arrNormalline[1].color = D3DXCOLOR(0, 1, 0, 1);

	// �޽�
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
	{			//  �� ����! 180��
		m_vRot.y -= D3DX_PI * 0.5f * dTime;
		D3DXVec3TransformNormal(&m_vDir, &m_vOrgDir, &m_mRot);
	}  // ���� �Ѱ��� ���� �߿��ϴ�
	if (INPUTMGR->GetKey(VK_RIGHT))
	{
		m_vRot.y += D3DX_PI * 0.5f * dTime;
		D3DXVec3TransformNormal(&m_vDir, &m_vOrgDir, &m_mRot);
	} // ��͵� �߿��ϴ�


	D3DXMatrixTranslation(&m_mTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMatrixScaling(&m_mScale, m_vScale.x, m_vScale.y, m_vScale.z);
	// �Է��� ����ŭ ������ ������. (ũ������)

	D3DXMatrixRotationYawPitchRoll(&m_mRot, m_vRot.y, m_vRot.x, m_vRot.z);

	m_mTM = m_mScale * m_mRot * m_mTrans;  // �߽��� �������� �����ϰ� �ϰ������ STR
										   // �߽��� �������� ��ŭ �̵��� �� ȸ���ϰ� �ϰ������ SRT
}

void Player::Render()
{
	DWORD dwState;      //d3dcull�� �⺻���� �𸦶� ���.dwState�� d3dcull �ڸ��� ������ ��
	DEVICE->GetRenderState(D3DRS_FILLMODE, &dwState);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  // �޸鵵 ���̰��ϴ� �۾�

	//DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_COLOR::FORMAT::FVF));
	DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST, // �׸��� ���
		1,					// �ﰢ�� ����
		&m_arrVertexs,		// ���ؽ� ����
		sizeof(D3DFVF_XYZ_COLOR) // �������� ������
	);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // �޸� ���̰��ߴٰ� �ٽ� �����·�(�޸�Ⱥ��̰�) �ϴ� �۾� [����]
	DEVICE->SetRenderState(D3DRS_FILLMODE, dwState);

	// ��ֶ���
	DEVICE->DrawPrimitiveUP(
		D3DPT_LINELIST, // �׸��� ���
		1,					// �ﰢ�� ����
		&m_arrNormalline,		// ���ؽ� ����
		sizeof(D3DFVF_XYZ_COLOR) // �������� ������
	);

	// �޽�
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