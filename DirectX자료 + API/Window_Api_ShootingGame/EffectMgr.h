#pragma once
class EffectMgr : public Singleton<EffectMgr>
{
	LISTOBJECT m_listEffects;
	PROPERTYARRAY_FUNC(LISTOBJECT*, listEffects,
		&m_listEffects)

public:
	void CreateEffect(int _x, int _y);
	void Update();
	void Render(HDC _backDC);
	void Release();


	EffectMgr();
	virtual ~EffectMgr();
};

