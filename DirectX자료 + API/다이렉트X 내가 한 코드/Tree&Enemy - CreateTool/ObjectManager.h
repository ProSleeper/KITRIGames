#pragma once

#define OBJMGR ObjectManager::GetInstance()

class ObjectManager
{
public:
	SINGLETONE(ObjectManager)

	void CreateObject(BaseObject* pObject);
	void UpdateObject(float dTime);
	void CollisionObject(float dTime);
	BaseObject* SelectObject(float dTime);
	void RenderObject();
	void ReleaseObject();
	void OnEdit();
	void OffEdit();
	bool IsRaySphere(D3DXVECTOR3 vTargetPos, float fTargetRadius);
	size_t ListSize()
	{
		return mListBullet.size();
	}

private:
	list<BaseObject*> mListBullet;
	bool mObjectEditOn;
};

