#include "GameCommon.h"



EffectMgr::EffectMgr()
{
	m_listEffects.clear();
}


EffectMgr::~EffectMgr()
{
	Release();
}


void EffectMgr::CreateEffect(int _x, int _y)
{
	Explosion* pEffect = new Explosion;
	pEffect->Init(_x, _y, 40, 40, 320, 40, 1, IT_EXPLOSION);
	m_listEffects.push_back(pEffect);
}

void EffectMgr::Update()
{
	for (OBJECTITOR itor = m_listEffects.begin();
		itor != m_listEffects.end();)
	{
		BaseImageObject* _pObj =
			(BaseImageObject*)(*itor);

		if (_pObj->Update() == false)
		{
			delete (*itor);
			itor = m_listEffects.erase(itor);
		}
		else
			itor++;
	}

}

void EffectMgr::Render(HDC _backDC)
{
	for (OBJECTITOR itor = m_listEffects.begin();
		itor != m_listEffects.end(); itor++)
	{
		BaseImageObject* _pObj =
			(BaseImageObject*)(*itor);

		_pObj->Render(_backDC);
	}
}

void EffectMgr::Release()
{
	for (OBJECTITOR itor = m_listEffects.begin();
		itor != m_listEffects.end(); itor++)
	{
		delete (*itor);
	}

	m_listEffects.clear();
}
