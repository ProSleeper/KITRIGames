#pragma once
class GameScene : public BaseScene
{
	Player* m_Player;
	Image* m_pBack;
	Map m_Map;

	LISTOBJECT m_listObjects;
	PROPERTYARRAY_FUNC(LISTOBJECT*, Objects, &m_listObjects);

	void DeleteObject();
	void DebugView();



public:
	void CreateObject(BaseTransform* _pObj, bool _bColl = false);


	virtual void Init(HDC _hDC);	//�� �װ����� �ʼ�.
	virtual void Update();
	virtual void Render();
	virtual void Release();


	GameScene();
	virtual ~GameScene();
};

