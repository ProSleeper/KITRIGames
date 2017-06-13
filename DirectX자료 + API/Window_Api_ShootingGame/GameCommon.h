#pragma once
// GameCommon
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"winmm.lib")

#include <list>
using namespace std;

// --------------

#define ROOT2 1.41421f

#define PROPERTY_FUNC(_Type, _FuncName, _Value)\
public : _Type Get##_FuncName()\
{ return _Value;}\
public : void Set##_FuncName(_Type _v)\
{ _Value = _v; }

#define PROPERTYARRAY_FUNC(_Type, _FuncName,_Value)\
public : _Type Get##_FuncName()\
{return _Value;}


#define SINGLETON_FUNC(MgrName) \
private: static MgrName* m_pInstance;\
public: static MgrName* GetInstance()\
{\
	if(m_pInstance == NULL) \
	{ m_pInstance = new MgrName; }\
	return m_pInstance;\
}

#define SINGLETON_INIT(MgrName) \
MgrName* MgrName::m_pInstance = 0;


// KeyState
#define GETKEY(key) \
((GetKeyState(key) & 0x8000) == 0x8000)

#define GETKEYDOWN(key, value, func)\
if((GetAsyncKeyState(key) & 0x8000) == 0x8000 &&\
value == false )\
	{ func(); value = true;}\
if(value)\
{\
	if((GetAsyncKeyState(key) & 0x8001) == 0x0000)\
		{value = false;}\
}

#define GETKEYUP(key, value, func)\
if((GetAsyncKeyState(key) & 0x8000) == 0x8000 &&\
value == false )\
	{ value = true;}\
if(value)\
{\
	if((GetAsyncKeyState(key) & 0x8001) == 0x0000)\
		{ func(); value = false;}\
}

enum OBJECTTAG
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_ENEMY,
	TAG_BOSS,
	TAG_ENEMY_BULLET,
	TAG_PLAYER_BULLET,
	TAG_MAX,
};




#include "Singleton.cpp"
#include "Time.h"

#include "Image.h"
#include "ImageMgr.h"

#include "BaseTransform.h"
#include "BaseImageObject.h"
#include "BaseCollObject.h"
#include "BaseTargetObject.h"
#include "CollisionMgr.h"

#include "WindowMgr.h"

#include "Map.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletEnemy.h"
#include "RotateEnemy.h"
#include "BossEnemy.h"

typedef list<Bullet*>				LISTBULLET;
typedef list<Bullet*>::iterator		BULLETITOR;

typedef list<BaseTransform*>		LISTOBJECT;
typedef LISTOBJECT::iterator		OBJECTITOR;

#include "HUDBar.h"

#include "Player.h"

#include "EffectMgr.h"
#include "EnemyMgr.h"
#include "FrameCheckMgr.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "EndingScene.h"
#include "GameMgr.h"

#define WINMGR WindowMgr::GetInstance()
#define GAMEMGR GameMgr::GetInstance()
#define FRAMEMGR FrameCheckMgr::GetInstance()
#define IMAGEMGR ImageMgr::GetInstance()
#define COLLMGR CollisionMgr::GetInstance()
#define ENEMYMGR EnemyMgr::GetInstance()
#define EFFECTMGR EffectMgr::GetInstance()
