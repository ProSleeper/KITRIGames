// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <assert.h>
#include <list>
#include <map>
#include <string>

using namespace std;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include "d3d9.h"
#include "d3dx9.h"
#include "Macro.h"

struct D3DFVF_XYZ_COLOR 
{   // �޸� ���� ������ ���� �߿�
	
	D3DXVECTOR3	vPos;
	DWORD		color;
							// DIFFUSE�� ����!
	enum class FORMAT{FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct D3DFVF_XYZ_NORMAL_TEX1
{   // �޸� ���� ������ ���� �߿�

	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vNormal;
	float u, v;
	// DIFFUSE�� ����!
	enum class FORMAT { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

#include "BaseObject.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "FontManager.h"
#include "FrameMansger.h"
#include "InputManager.h"
#include "Direct3DManager.h"
#include "GameManager.h"