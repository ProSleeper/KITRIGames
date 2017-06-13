#pragma once

#define DXMGR Direct3DManager::GetInstance()
#define DEVICE DXMGR->GetDevice()

class Direct3DManager
{
	SINGLETONE(Direct3DManager);

	LPDIRECT3D9			m_pD3D;
	GETTER(LPDIRECT3DDEVICE9, Device, m_pDevice);		//LPDIRECT3DDEVICE9	m_pDevice;

	// 윈도우 정보
	PROPERTY_FUNC(HWND, hWnd, m_hWnd);
	PROPERTY_FUNC(int, Width, m_nWidth);
	PROPERTY_FUNC(int, Height, m_nHeight);

public:
	void Setup(void);
	void Destroy(void);
	void ReSizeWindow();
};

