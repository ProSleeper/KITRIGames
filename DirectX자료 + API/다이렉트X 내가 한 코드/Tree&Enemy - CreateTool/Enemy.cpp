#include "stdafx.h"
#include "Enemy.h"


void Enemy::Init()
{
	
}

void Enemy::Update(float dTime)
{
	D3DXMatrixTranslation(&mmPos, mvPos.x, mvPos.y, mvPos.z);
	D3DXMatrixScaling(&mmScale, mvScale.x, mvScale.y, mvScale.z);
	D3DXMatrixRotationYawPitchRoll(&mmRot, mvRot.y, mvRot.x, mvRot.z);
 
	mmTm = mmScale * mmRot * mmPos;
}

void Enemy::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &mmTm);
	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	mCylinder->DrawSubset(0);
	if(mEditOn)
	{
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		mCrashSphere->DrawSubset(0);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Enemy::Release()
{
	SAFE_RELEASE(mCylinder)
}

Enemy::Enemy(D3DXVECTOR3 pPos)
{
	mvPos = pPos;
	mvPos.y += 0.5f;
	mRadius = 0.75f;
	D3DXCreateCylinder(DEVICE, 0.5f, 0.5f, 1, 10, 10, &mCylinder, nullptr);
	D3DXCreateSphere(DEVICE, mRadius, 10, 10, &mCrashSphere, nullptr);
}

Enemy::~Enemy()
{
	Release();
}