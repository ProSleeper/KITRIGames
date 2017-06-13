#pragma once

class Rect;

class Player
{
	PROPERTY_FUNC(Rect*, Target, m_pRect)
	float			 m_fRadius;

	LPD3DXMESH		 m_pCullSphere;

	// 노멀라인
	D3DFVF_XYZ_COLOR m_arrNormalline[2];

	D3DFVF_XYZ_COLOR m_arrVertexs[3];

	PROPERTY_FUNC(D3DXVECTOR3, Pos, m_vPos)
	D3DXVECTOR3		 m_vRot;
	D3DXVECTOR3		 m_vScale;
	D3DXVECTOR3		 m_vDir;
	D3DXVECTOR3      m_vOrgDir;

	D3DXMATRIX		 m_mTM;
	D3DXMATRIX		 m_mTrans;
	D3DXMATRIX		 m_mRot;
	D3DXMATRIX		 m_mScale;

	GETTER(bool, IsPick, m_bIsPick);

public:
	

	void Init();
	void Update(float dTime);
	void Render();
	void Release();


public:
	Player();
	virtual ~Player();
};

