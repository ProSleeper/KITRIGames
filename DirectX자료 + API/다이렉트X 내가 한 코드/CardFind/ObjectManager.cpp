#include "stdafx.h"
#include "Card.h"
#include "MouseRay.h"

void ObjectManager::CreateObject()
{
	int arrCardNumber[36] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18};
	
	for (int i = 0; i < 200 ; i++)
	{
		int arr1 = rd() % 36;
		int arr2 = rd() % 36;
		swap(arrCardNumber[arr1], arrCardNumber[arr2]);
	}
	
	int cardNumber = 0;

	char name[50] = {0,};
	
	for(int i = -2; i < 4; i++)
	{
		for(int j = -2; j < 4; j++)
		{
			sprintf_s(name, "CardImage\\Edit\\%d.jpg", arrCardNumber[cardNumber]);
			Card* tCard = new Card(D3DXVECTOR3(j * 8 - 4 + j, 0, i * 11 - 9), name, arrCardNumber[cardNumber++]);
			mListObject.push_back(tCard);
		}
	}
	/*Card* tCard = new Card(D3DXVECTOR3(0, 0, 0));
	mListBullet.push_back(tCard);*/
}

void ObjectManager::UpdateObject(float dTime)
{
	mCount = 0;
	for(auto pObject : mListObject)
	{
		pObject->Update(dTime);
		//pObject->SetEditOn(mObjectEditOn);
		if (pObject->GetCheckCard() == true)
		{
			mSame[mCount] = pObject;
			mCount++;
		}

		if(mCount > 1)
		{
			if(mSame[0]->GetCardNumber() == mSame[1]->GetCardNumber())
			{
				mSame[0]->SetUse(false);
				mSame[1]->SetUse(false);
			}
			else
			{
				mSame[0]->SetOnCard(false);
				mSame[1]->SetOnCard(false);

				mSame[0]->SetOffCard(true);
				mSame[1]->SetOffCard(true);
			}
		}
	}

	for(auto iter = mListObject.begin(); iter != mListObject.end();)
	{
		if((*iter)->GetUse() == false)
		{
			SAFE_DELETE(*iter)
			iter = mListObject.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

bool ObjectManager::CollisionObject(float dTime)
{
	for(auto iter = mListObject.begin(); iter != mListObject.end(); iter++)
	{
		if(IsRaySphere((*iter)->GetVPos(), (*iter)->GetWidth()/2 - 0.2f, (*iter)->GetHeight()/2 - 0.3f))
		{
			/*delete *iter;
			iter = mListBullet.erase(iter);*/
			//MessageBox(NULL, "픽킹성공", "성공", MB_OK);
			(*iter)->SetOnCard(true);
			return true;
		}
	}
	return false;
}

Card* ObjectManager::SelectObject(float dTime)
{
	for(auto iter = mListObject.begin(); iter != mListObject.end();)
	{

		if(IsRaySphere((*iter)->GetVPos(), (*iter)->GetWidth()/2, (*iter)->GetHeight()/2))
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
	for(auto pObject : mListObject)
	{
		pObject->Render();
	}
}


bool ObjectManager::IsRaySphere(D3DXVECTOR3 vTargetPos, float fTargetWidth, float fTargetHeight)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXMGR->GethWnd(), &pt);

	MouseRay ray;
	ray.CreateRay((int)pt.x, (int)pt.y); // 역뷰포팅 + 역프로젝션변환

	D3DXMATRIX view;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	ray.RayTransForm(view);	//역뷰변환

	// 타겟과 나의 거리
	D3DXVECTOR3 vTargetDis = vTargetPos - ray.GetPos();

	// 직교하는 길이
	float Len = D3DXVec3Dot(&vTargetDis, &ray.GetDir());

	// 뒤로 쐈을시 코사인이 -1을 반환함으로서 발생하는 true반환을 방지하기 위함.
	if(Len < 0)
		return false;

	// 직교한 정점 좌표
	D3DXVECTOR3 vPos = ray.GetPos() + ray.GetDir() * Len;

	if (vPos.x > vTargetPos.x - fTargetWidth &&
		vPos.x < vTargetPos.x + fTargetWidth &&
		vPos.z < vTargetPos.z + fTargetHeight &&
		vPos.z > vTargetPos.z - fTargetHeight)
	{
		return true;
	}

	return false;
}


void ObjectManager::ReleaseObject()
{
	for each (auto pObject in mListObject)
	{
		delete pObject;
	}
	mListObject.clear();
}
ObjectManager::ObjectManager() : mObjectEditOn(false)
{
	mListObject.clear();
}

ObjectManager::~ObjectManager()
{
	ReleaseObject();
}

