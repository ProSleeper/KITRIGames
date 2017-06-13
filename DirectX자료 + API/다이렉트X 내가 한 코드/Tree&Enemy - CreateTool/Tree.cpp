#include "stdafx.h"
#include "Tree.h"

void Tree::Init()
{
	
}


void Tree::Update(float dTime)
{
	D3DXMatrixTranslation(&mmPos, mvPos.x, mvPos.y, mvPos.z);
	D3DXMatrixRotationYawPitchRoll(&mmRot, mvRot.y, mvRot.x, mvRot.z);
	D3DXMatrixScaling(&mmScale, mvScale.x, mvScale.y, mvScale.z);

	mmTm = mmScale * mmRot * mmPos;
}

void Tree::Render()
{
	mmTm._42 = 0;
	DEVICE->SetTransform(D3DTS_WORLD, &mmTm);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_COLOR::FORMAT::FVF));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, mTrunk, sizeof(D3DFVF_XYZ_COLOR));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, mLeaf, sizeof(D3DFVF_XYZ_COLOR));
	if (mEditOn)
	{
		mmTm._42 = 1;
		DEVICE->SetTransform(D3DTS_WORLD, &mmTm);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		mCrashSphere->DrawSubset(0);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
}

void Tree::Release()
{
}

Tree::Tree(D3DXVECTOR3 pPos)
{
	mvDir = {0, 1, 0};
	mvPos = pPos;
	mvPos.y += 1.0f;
	mTrunk[0].vPos = D3DXVECTOR3(-0.25f, 1, 0);
	mTrunk[0].color = D3DXCOLOR(1, 0, 0, 1);

	mTrunk[1].vPos = D3DXVECTOR3(0.25f, 1, 0);
	mTrunk[1].color = D3DXCOLOR(1, 0, 0, 1);

	mTrunk[2].vPos = D3DXVECTOR3(-0.25f, 0, 0);
	mTrunk[2].color = D3DXCOLOR(0, 1, 0, 1);

	mTrunk[3].vPos = D3DXVECTOR3(0.25f, 0, 0);
	mTrunk[3].color = D3DXCOLOR(0, 0, 1, 1);

	mLeaf[0][0].vPos = D3DXVECTOR3(-1.0f, 1, 0);
	mLeaf[0][0].color = D3DXCOLOR(0, 1, 0, 1);

	mLeaf[0][1].vPos = D3DXVECTOR3(0.0f, 2, 0);
	mLeaf[0][1].color = D3DXCOLOR(1, 0, 0, 1);

	mLeaf[0][2].vPos = D3DXVECTOR3(1.0f, 1, 0);
	mLeaf[0][2].color = D3DXCOLOR(0, 1, 0, 1);

	mLeaf[1][0].vPos = D3DXVECTOR3(-1.0f, 1.5f, 0.01f);
	mLeaf[1][0].color = D3DXCOLOR(0, 1, 0, 1);

	mLeaf[1][1].vPos = D3DXVECTOR3(0.0f, 2.5f, 0.01f);
	mLeaf[1][1].color = D3DXCOLOR(0, 1, 0, 1);

	mLeaf[1][2].vPos = D3DXVECTOR3(1.0f, 1.5f, 0.01f);
	mLeaf[1][2].color = D3DXCOLOR(0, 0, 1, 1);

	mRadius = 1.0f;
	D3DXCreateSphere(DEVICE, mRadius, 10, 10, &mCrashSphere, nullptr);
}

Tree::~Tree()
{
}
