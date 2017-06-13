#pragma once

enum class OBJECT
{
	OB_TREE,
	OB_ENEMY,
	OT_MAX
};

class BaseObject
{
public:

	virtual void Init();
	virtual void Update(float dTime);
	virtual void Render();
	virtual void Release();
	void SetVPos(D3DXVECTOR3 pvPos)
	{
		mvPos.x = pvPos.x;
		mvPos.z = pvPos.z;
	}
	BaseObject();
	virtual ~BaseObject();
protected:
	LPD3DXMESH mCard;
	PROPERTY_FUNC(float, Width, mWidth)
	PROPERTY_FUNC(float, Height, mHeight)
	PROPERTY_FUNC(bool, Use, mbUse)
	PROPERTY_FUNC(D3DXMATRIX, Tm, mmTm)
	PROPERTY_FUNC(D3DXMATRIX, MPos, mmPos)
	PROPERTY_FUNC(D3DXMATRIX, MRot, mmRot)
	PROPERTY_FUNC(D3DXMATRIX, MScale, mmScale)
	GETTER(D3DXVECTOR3, VPos, mvPos)
	PROPERTY_FUNC(D3DXVECTOR3, VDir, mvDir)
	PROPERTY_FUNC(D3DXVECTOR3, VRot, mvRot)
	PROPERTY_FUNC(D3DXVECTOR3, VScale, mvScale)
	PROPERTY_FUNC(D3DXVECTOR3, VOrgPos, mvOrgPos)
	PROPERTY_FUNC(D3DXVECTOR3, VOrgDir, mvOrgDir)
	
};

