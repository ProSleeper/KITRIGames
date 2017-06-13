#pragma once
class BaseCollObject : public BaseTransform
{
	BaseTransform* m_pTarget;
	PROPERTY_FUNC(BaseTransform*, Target, m_pTarget)

public :
	void Init(BaseTransform* _pTarget);
	void Update();
	void Render(HDC _backDC);

public:
	BaseCollObject();
	virtual ~BaseCollObject();
};

