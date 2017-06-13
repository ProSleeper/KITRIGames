#include "stdafx.h"
#include "BaseObject.h"
#include "Tree.h"
#include "Enemy.h"
#include "CreateObject.h"


BaseObject * CreateObject::ClickCreate(OBJECT pObj, D3DXVECTOR3 pPos)
{
	switch (pObj)
	{
		case OBJECT::OB_TREE:
		{
			return new Tree(pPos);
			break;
		}
		case OBJECT::OB_ENEMY:
		{
			return new Enemy(pPos);
			break;
		}
		default:
		{
			assert("肋给等 积己");
			break;
		}
	}
}

CreateObject::CreateObject()
{
}


CreateObject::~CreateObject()
{
}
