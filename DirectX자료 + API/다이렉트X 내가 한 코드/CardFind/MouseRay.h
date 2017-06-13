#pragma once
class MouseRay
{
	GETTER(D3DXVECTOR3, Pos, m_vPos);
	GETTER(D3DXVECTOR3, Dir, m_vDir);

public:
	void CreateRay(int x, int y);
	void RayTransForm(D3DXMATRIX m);

public:
	MouseRay();
	virtual ~MouseRay();
};

