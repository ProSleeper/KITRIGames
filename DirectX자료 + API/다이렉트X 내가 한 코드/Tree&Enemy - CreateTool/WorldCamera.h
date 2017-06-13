#pragma once
class WorldCamera
{
	D3DXMATRIX			m_mView;
	D3DXMATRIX			m_mProj;

	D3DXVECTOR3			m_vEye;			// 카메라 위치
	D3DXVECTOR3			m_vLookAt;		// 카메라 바라보는곳
	D3DXVECTOR3			m_vUp;			// 카메리 업벡터

	POINT				m_ptOrgMouse;	// 마우스 이전위치 값(카메리회전용)
	float				m_fMouseRotX;	// 마우스 x축 감도
	float				m_fMouseRotY;	// 마우스 y축 감도

	bool				m_bRButtonDown;

public:
	void SetUp(D3DXVECTOR3 vEye);
	void ViewTransform(void);
	void ProjectionTransform(void);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	WorldCamera();
	virtual ~WorldCamera();
};

