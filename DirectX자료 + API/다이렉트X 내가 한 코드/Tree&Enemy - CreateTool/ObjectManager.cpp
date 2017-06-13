#include "stdafx.h"
#include "MouseRay.h"


void ObjectManager::CreateObject(BaseObject* pObject)
{
	mListBullet.push_back(pObject);
}

void ObjectManager::UpdateObject(float dTime)
{
	for(auto pObject : mListBullet)
	{
		pObject->SetEditOn(mObjectEditOn);
		pObject->Update(dTime);
	}

	
}

void ObjectManager::CollisionObject(float dTime)
{
	for(auto iter = mListBullet.begin(); iter != mListBullet.end();)
	{

		if (IsRaySphere((*iter)->GetVPos(), (*iter)->GetRadius()))
		{
			delete *iter;
			iter = mListBullet.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

BaseObject* ObjectManager::SelectObject(float dTime)
{
	for(auto iter = mListBullet.begin(); iter != mListBullet.end();)
	{

		if(IsRaySphere((*iter)->GetVPos(), (*iter)->GetRadius()))
		{
			return (*iter);
		}
		else
		{
			iter++;
		}
	}
	return nullptr;
}

void ObjectManager::RenderObject()
{
	for(auto pObject : mListBullet)
	{
		pObject->Render();
	}
}


bool ObjectManager::IsRaySphere(D3DXVECTOR3 vTargetPos, float fTargetRadius)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXMGR->GethWnd(), &pt);

	MouseRay ray;
	ray.CreateRay((int)pt.x, (int)pt.y); // 뷰공간

	D3DXMATRIX view;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	ray.RayTransForm(view);

	// 타겟과 나의 거리
	D3DXVECTOR3 vTargetDis = vTargetPos - ray.GetPos();

	// 직교하는 길이
	float Len = D3DXVec3Dot(&vTargetDis, &ray.GetDir());

	// 뒤로 쐈을시 코사인이 -1을 반환함으로서 발생하는 true반환을 방지하기 위함.
	if(Len < 0)
		return false;

	// 직교한 정점 좌표
	D3DXVECTOR3 vPos = ray.GetPos() + ray.GetDir() * Len;

	// 직교한 정점과 타겟과 거리
	vTargetDis = vPos - vTargetPos;

	// 타겟과의 거리의 길이
	Len = D3DXVec3Length(&vTargetDis);

	// 판정

	if(Len < fTargetRadius)
		return true;

	return false;
}


void ObjectManager::ReleaseObject()
{
	for each (auto pObject in mListBullet)
	{
		delete pObject;
	}
	mListBullet.clear();
}

void ObjectManager::OffEdit()
{
	mObjectEditOn = false;
}

void ObjectManager::OnEdit()
{
	mObjectEditOn = true;
}

ObjectManager::ObjectManager() : mObjectEditOn(false)
{
	mListBullet.clear();
}

ObjectManager::~ObjectManager()
{
	ReleaseObject();
}

