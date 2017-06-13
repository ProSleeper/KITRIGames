#pragma once
class Enemy : public BaseObject
{
public:
	void Init() override;
	void Update(float dTime) override;
	void Render() override;
	void Release() override;


	Enemy(D3DXVECTOR3 pPos);
	virtual ~Enemy();
private:
	LPD3DXMESH mCylinder;
};