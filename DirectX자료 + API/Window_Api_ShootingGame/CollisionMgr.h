#pragma once
class CollisionMgr : public Singleton<CollisionMgr>
{
	bool CollTag[TAG_MAX][TAG_MAX] = { 0 };

	list<BaseCollObject*> m_CollObj;
	PROPERTYARRAY_FUNC(list<BaseCollObject*>*,
		Collider, &m_CollObj)

public :
	void CreateCollider(BaseTransform* pTarget);
	void Update();
	void Render(HDC _backDC);
	void Release();

	void DeleteCollider(BaseTransform* pTarget);
	bool IsCollision(BaseCollObject* _pSrc,
		BaseCollObject* _pDest);

	bool GetCollTag(OBJECTTAG _src, OBJECTTAG _target)
	{
		return CollTag[_src][_target];
	}

	bool RePosCheck(BaseTransform* pTarget);

private:
	void SetCollTag(OBJECTTAG _src, OBJECTTAG _target,
		bool _value, bool _setBoth = true);

public:
	CollisionMgr();
	virtual ~CollisionMgr();
};

