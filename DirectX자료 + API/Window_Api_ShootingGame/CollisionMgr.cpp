#include "GameCommon.h"

CollisionMgr::CollisionMgr()
{
	m_CollObj.clear();

	for (int i = 0; i < TAG_MAX; i++)
	{
		for (int j = 0; j < TAG_MAX; j++)
		{
			CollTag[i][j] = true;
		}
	}

	SetCollTag(TAG_PLAYER, TAG_PLAYER_BULLET, false);

	SetCollTag(TAG_ENEMY, TAG_ENEMY, false);
	SetCollTag(TAG_PLAYER_BULLET, TAG_PLAYER_BULLET, false);

	SetCollTag(TAG_ENEMY, TAG_ENEMY_BULLET, false);

	// 치트키
	SetCollTag(TAG_PLAYER, TAG_ENEMY_BULLET, false , false);
}


CollisionMgr::~CollisionMgr()
{
	Release();
}

void CollisionMgr::CreateCollider(BaseTransform* pTarget)
{
	BaseCollObject* _pCollObj = new BaseCollObject;
	_pCollObj->Init(pTarget);
	m_CollObj.push_back(_pCollObj);
}

void CollisionMgr::Update()
{
	for (list<BaseCollObject*>::iterator itor =
		m_CollObj.begin();
		itor != m_CollObj.end();
		itor++)
	{
		(*itor)->Update();
	}

	for (list<BaseCollObject*>::iterator itor =
		m_CollObj.begin();
		itor != m_CollObj.end();
		itor++)
	{
		list<BaseCollObject*>::iterator nextItor = itor;
		nextItor++;

		for (nextItor; nextItor != m_CollObj.end();
			nextItor++)
		{
			if (GetCollTag(
				(*itor)->GetTarget()->GetTag(),
				(*nextItor)->GetTarget()->GetTag()
				)
				&&
				IsCollision((*itor), (*nextItor))
			   )
			{
				// 충돌 처리
				BaseTargetObject* pSrc =
					(BaseTargetObject*)(*itor)->GetTarget();
				BaseTargetObject* pDest =
					(BaseTargetObject*)(*nextItor)->GetTarget();

				pSrc->OnCollisionEnter(pDest);
				pDest->OnCollisionEnter(pSrc);
			}
		}		
	}
}

void CollisionMgr::Render(HDC _backDC)
{
	for (list<BaseCollObject*>::iterator itor =
		m_CollObj.begin();
		itor != m_CollObj.end(); itor++)
	{
		(*itor)->Render(_backDC);
	}
}

void CollisionMgr::Release()
{
	for (list<BaseCollObject*>::iterator itor =
		m_CollObj.begin();
		itor != m_CollObj.end(); itor++)
	{
		delete(*itor);
	}
	m_CollObj.clear();
}


void CollisionMgr::DeleteCollider(BaseTransform* pTarget)
{
	for (list<BaseCollObject*>::iterator itor
		= m_CollObj.begin();
		itor != m_CollObj.end();)
	{
		if ((*itor)->GetTarget() == pTarget)
		{
			delete (*itor);
			itor = m_CollObj.erase(itor);
		}
		else
			itor++;
	}
}


bool CollisionMgr::IsCollision(BaseCollObject* _pSrc,
	BaseCollObject* _pDest)
{
	if (_pSrc->GetPosX() + _pSrc->GetWidth()
		< _pDest->GetPosX())
		return false;

	if (_pDest->GetPosX() + _pDest->GetWidth()
		< _pSrc->GetPosX())
		return false;

	if (_pDest->GetPosY() + _pDest->GetHeight()
		< _pSrc->GetPosY())
		return false;

	if (_pSrc->GetPosY() + _pSrc->GetHeight()
		< _pDest->GetPosY())
		return false;

	return true;

}


void CollisionMgr::SetCollTag(OBJECTTAG _src, OBJECTTAG _target,
	bool _value, bool _setBoth)
{
	CollTag[_src][_target] = _value;

	if(_setBoth)
		CollTag[_target][_src] = _value;
}


bool CollisionMgr::RePosCheck(BaseTransform* pTarget)
{
	if (pTarget->GetPosX() >
		WINMGR->GetWidth() - pTarget->GetWidth())
		return false;

	for (list<BaseCollObject*>::iterator itor = m_CollObj.begin();
		itor != m_CollObj.end(); ++itor)
	{
		BaseCollObject* _pObj = (BaseCollObject*)pTarget;
		if (IsCollision(_pObj, *itor) == true)
			return false;
	}

	return true;
}