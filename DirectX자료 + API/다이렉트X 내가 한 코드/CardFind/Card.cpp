#include "stdafx.h"
#include "MyTexture.h"
#include "Card.h"

Card::Card(D3DXVECTOR3 pPos, string pCardName, int pNumber) : mOnCard(false), mOffCard(false), mCheckCard(false), mCurOnTime(0), mCurOffTime(0), mMaxTime(0.5f), mCardNumber(pNumber)
{
	mWidth = 7;
	mHeight = 10;
	ZeroMemory(&mMaterial, sizeof(mMaterial));
	mvPos = pPos;
	mpTexture[0] = TEXMGR->GetTexture("CardImage\\Edit\\Back.jpg");
	mpTexture[1] = TEXMGR->GetTexture(pCardName);

	mCard[0][0].vPos = D3DXVECTOR3(-3.5f, 0.01f, 5.0f);
	mCard[0][0].vNormal = D3DXVECTOR3(0, 1, 0);
	mCard[0][0].u = 0;
	mCard[0][0].v = 0;

	mCard[0][1].vPos = D3DXVECTOR3(3.5f, 0.01f, 5.0f);
	mCard[0][1].vNormal = D3DXVECTOR3(0, 1, 0);
	mCard[0][1].u = 1;
	mCard[0][1].v = 0;

	mCard[0][2].vPos = D3DXVECTOR3(-3.5f, 0.01f, -5.0f);
	mCard[0][2].vNormal = D3DXVECTOR3(0, 1, 0);
	mCard[0][2].u = 0;
	mCard[0][2].v = 1;

	mCard[0][3].vPos = D3DXVECTOR3(3.5f, 0.01f, -5.0f);
	mCard[0][3].vNormal = D3DXVECTOR3(0, 1, 0);
	mCard[0][3].u = 1;
	mCard[0][3].v = 1;


	mCard[1][0].vPos = D3DXVECTOR3(3.5f, 0.0f, 5.0f);
	mCard[1][0].vNormal = D3DXVECTOR3(0, -1, 0);
	mCard[1][0].u = 0;
	mCard[1][0].v = 0;

	mCard[1][1].vPos = D3DXVECTOR3(-3.5f, 0.0f, 5.0f);
	mCard[1][1].vNormal = D3DXVECTOR3(0, -1, 0);
	mCard[1][1].u = 1;
	mCard[1][1].v = 0;

	mCard[1][2].vPos = D3DXVECTOR3(3.5f, 0.0f, -5.0f);
	mCard[1][2].vNormal = D3DXVECTOR3(0, -1, 0);
	mCard[1][2].u = 0;
	mCard[1][2].v = 1;

	mCard[1][3].vPos = D3DXVECTOR3(-3.5f, 0.0f, -5.0f);
	mCard[1][3].vNormal = D3DXVECTOR3(0, -1, 0);
	mCard[1][3].u = 1;
	mCard[1][3].v = 1;

	// 머터리얼
	mMaterial.Diffuse = mMaterial.Ambient
		= D3DXCOLOR(1, 1, 1, 1);
}

Card::~Card()
{
}

void Card::CardOn(float dTime)
{
	mCurOnTime += dTime;
	if(mCurOnTime > mMaxTime)
	{
		mCurOnTime = 0.5f;
		mCheckCard = true;
	}
	//일단 카드 회전하는 선형보간부터 하면 됨!
	D3DXVec3Lerp(&mvRot, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, D3DX_PI), mCurOnTime / mMaxTime);
}

void Card::CardOff(float dTime)
{
	//일단 카드 회전하는 선형보간부터 하면 됨!
	mCurOffTime += dTime;
	if(mCurOffTime > mMaxTime)
	{
		mCurOffTime = 0.5f;
		mOffCard = false;
	}
	//일단 카드 회전하는 선형보간부터 하면 됨!
	D3DXVec3Lerp(&mvRot, &D3DXVECTOR3(0, 0, D3DX_PI), &D3DXVECTOR3(0, 0, 0), mCurOffTime / mMaxTime);
}

void Card::Init()
{
}

void Card::Update(float dTime)
{
	if (mOnCard)
	{
		CardOn(dTime);
		mCurOffTime = 0;
	}
	
	if (mOffCard)
	{
		mCheckCard = false;
		CardOff(dTime);
		mCurOnTime = 0;
	}
	
	D3DXMatrixTranslation(&mmPos, mvPos.x, mvPos.y, mvPos.z);
	D3DXMatrixRotationYawPitchRoll(&mmRot, mvRot.y, mvRot.x, mvRot.z);
	D3DXMatrixScaling(&mmScale, mvScale.x, mvScale.y, mvScale.z);

	mmTm = mmScale * mmRot * mmPos;
}

void Card::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &mmTm);
	DEVICE->SetMaterial(&mMaterial);
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetTexture(0, mpTexture[0]->GetTexture());
	DEVICE->SetFVF(static_cast<DWORD>(D3DFVF_XYZ_NORMAL_TEX1::FORMAT::FVF));
	DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		&mCard[0],
		sizeof(D3DFVF_XYZ_NORMAL_TEX1)
	);
	DEVICE->SetTexture(0, NULL);


	DEVICE->SetTexture(0, mpTexture[1]->GetTexture());
	DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		&mCard[1],
		sizeof(D3DFVF_XYZ_NORMAL_TEX1)
	);
	DEVICE->SetTexture(0, NULL);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);




}

void Card::Release()
{
}




