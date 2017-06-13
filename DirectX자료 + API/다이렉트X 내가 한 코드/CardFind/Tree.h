#pragma once
class Tree : public BaseObject
{
public:

	void Init() override;
	void Update(float dTime) override;
	void Render() override;
	void Release() override;

	Tree(D3DXVECTOR3 pPos);
	virtual ~Tree();
private:
	D3DFVF_XYZ_COLOR mLeaf[2][3];
	D3DFVF_XYZ_COLOR mTrunk[4];
};

