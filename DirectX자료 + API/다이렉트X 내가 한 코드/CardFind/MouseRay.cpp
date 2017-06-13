#include "stdafx.h"
#include "MouseRay.h"


void MouseRay::CreateRay(int x, int y)
	// �� �������� ���̸� �����°� ���Լ��� ����
{
	m_vPos.x = float(x);
	m_vPos.y = float(y);

	// �� ������
	m_vPos.x = (m_vPos.x * 2.0f / DXMGR->GetWidth()) - 1.0f;
	m_vPos.y = 1.0f - (m_vPos.y * 2.0f / DXMGR->GetHeight());

	// �� ��������
	D3DXMATRIX mProj;
	DEVICE->GetTransform(D3DTS_PROJECTION, &mProj);
	D3DXMatrixInverse(&mProj, 0, &mProj);
	D3DXVec3TransformCoord(&m_vDir, &m_vPos, &mProj);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	m_vPos = D3DXVECTOR3(0, 0, 0);
}

void MouseRay::RayTransForm(D3DXMATRIX m)
{
	D3DXMATRIX invm;
	D3DXMatrixInverse(&invm, 0, &m);

	D3DXVec3TransformCoord(&m_vPos, &m_vPos, &invm);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &invm);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

MouseRay::MouseRay()
	: m_vDir(0,0,0)
	, m_vPos(0,0,0)
{
}


MouseRay::~MouseRay()
{
}
