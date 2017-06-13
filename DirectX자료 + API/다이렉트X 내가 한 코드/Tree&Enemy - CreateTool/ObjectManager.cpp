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
	ray.CreateRay((int)pt.x, (int)pt.y); // �����

	D3DXMATRIX view;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	ray.RayTransForm(view);

	// Ÿ�ٰ� ���� �Ÿ�
	D3DXVECTOR3 vTargetDis = vTargetPos - ray.GetPos();

	// �����ϴ� ����
	float Len = D3DXVec3Dot(&vTargetDis, &ray.GetDir());

	// �ڷ� ������ �ڻ����� -1�� ��ȯ�����μ� �߻��ϴ� true��ȯ�� �����ϱ� ����.
	if(Len < 0)
		return false;

	// ������ ���� ��ǥ
	D3DXVECTOR3 vPos = ray.GetPos() + ray.GetDir() * Len;

	// ������ ������ Ÿ�ٰ� �Ÿ�
	vTargetDis = vPos - vTargetPos;

	// Ÿ�ٰ��� �Ÿ��� ����
	Len = D3DXVec3Length(&vTargetDis);

	// ����

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

