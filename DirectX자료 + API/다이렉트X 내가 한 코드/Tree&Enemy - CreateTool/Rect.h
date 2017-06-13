#pragma once

class Rect
{
	GETTER(float, Radius, m_fRadius)

	LPD3DXMESH		 m_pCullSphere;
	// 다이렉트에서 박스, 도넛등 도형들을 만들어놓은 정점!! 편하다

	D3DFVF_XYZ_COLOR m_arrRect[6];

	PROPERTY_FUNC(D3DXVECTOR3, Pos, m_vPos)
	D3DXVECTOR3		 m_vRot;
	D3DXVECTOR3		 m_vScale;
	D3DXVECTOR3		 m_vDir;
	D3DXVECTOR3      m_vOrgDir;

	D3DXMATRIX		 m_mTM;
	D3DXMATRIX		 m_mTrans;
	D3DXMATRIX		 m_mRot;
	D3DXMATRIX		 m_mScale;

public:
	void Init();
	void Update(float dTime);
	void Render();
	void Release();

	D3DXVECTOR3 GetPickPos(MouseRay ray);

public:
	Rect();
	virtual ~Rect();
};

