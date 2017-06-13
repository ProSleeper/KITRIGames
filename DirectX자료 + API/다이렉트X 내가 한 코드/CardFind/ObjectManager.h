#pragma once

#define OBJMGR ObjectManager::GetInstance()
class Card;
class ObjectManager
{
public:
	SINGLETONE(ObjectManager)

	void CreateObject();
	void UpdateObject(float dTime);
	bool CollisionObject(float dTime);
	Card* SelectObject(float dTime);
	void RenderObject();
	void ReleaseObject();
	bool IsRaySphere(D3DXVECTOR3 vTargetPos, float fTargetWidth, float fTargetHeight);
	size_t ListSize()
	{
		return mListObject.size();
	}
	/*
	list<BaseObject*>* GetList()
	{
		return &mListObject;
	}*/

private:
	list<Card*> mListObject;
	bool mObjectEditOn;

	Card* mSame[2];
	int mCount;
	random_device rd;
};

