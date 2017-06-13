#pragma once
class MyTexture;
class Card : public BaseObject
{
public:
	void Init() override;
	void Update(float dTime) override;
	void Render();
	void Release();
	void CardOn(float dTime);
	void CardOff(float dTime);

	


	Card(D3DXVECTOR3 pPos, string pCardName, int pNumber);
	virtual ~Card();
private:
	D3DMATERIAL9 mMaterial;
	D3DFVF_XYZ_NORMAL_TEX1 mCard[2][4];
	MyTexture* mpTexture[2];
	PROPERTY_FUNC(bool, OnCard, mOnCard)
	PROPERTY_FUNC(bool, CheckCard, mCheckCard)
	PROPERTY_FUNC(bool, OffCard, mOffCard)
	PROPERTY_FUNC(int, CardNumber, mCardNumber)

	float mCurOnTime;
	float mCurOffTime;
	float mMaxTime;
	
};

