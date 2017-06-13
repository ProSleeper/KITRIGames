#pragma once
class WorldCamera
{
	D3DXMATRIX			m_mView;
	D3DXMATRIX			m_mProj;

	D3DXVECTOR3			m_vEye;			// ī�޶� ��ġ
	D3DXVECTOR3			m_vLookAt;		// ī�޶� �ٶ󺸴°�
	D3DXVECTOR3			m_vUp;			// ī�޸� ������

	POINT				m_ptOrgMouse;	// ���콺 ������ġ ��(ī�޸�ȸ����)
	float				m_fMouseRotX;	// ���콺 x�� ����
	float				m_fMouseRotY;	// ���콺 y�� ����

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

