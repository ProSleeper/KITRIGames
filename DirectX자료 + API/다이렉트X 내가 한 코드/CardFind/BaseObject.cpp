#include "stdafx.h"
#include "BaseObject.h"


void BaseObject::Init()
{
}

void BaseObject::Update(float dTime)
{
	D3DXMatrixTranslation(&mmPos, mvPos.x, mvPos.y, mvPos.z);
	D3DXMatrixRotationYawPitchRoll(&mmRot, mvRot.y, mvRot.x, mvRot.z);
	D3DXMatrixScaling(&mmScale, mvScale.x, mvScale.y, mvScale.z);

	mmTm = mmScale * mmRot * mmPos;
}

void BaseObject::Render()
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_COLOR::FORMAT::FVF));
	DEVICE->SetTransform(D3DTS_WORLD, &mmTm);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void BaseObject::Release()
{
}

BaseObject::BaseObject() : mvPos(0, 0, 0), mvOrgPos(0, 0, 0), mvRot(0, 0, 0), mvScale(1, 1, 1), mvDir(0, 0, 1), mvOrgDir(0, 0, 1), mWidth(0), mHeight(0), mbUse(true),mCard(nullptr)
{
	D3DXMatrixIdentity(&mmTm);
	D3DXMatrixIdentity(&mmPos);
	D3DXMatrixIdentity(&mmRot);
	D3DXMatrixIdentity(&mmScale);
}


BaseObject::~BaseObject()
{
	Release();
}
