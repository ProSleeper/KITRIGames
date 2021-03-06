// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include "d3d9.h"
#include "d3dx9.h"
#include "Macro.h"

struct D3DFVF_XYZ_COLOR 
{   // 메모리 선언 순서가 가장 중요
	
	D3DXVECTOR3	vPos;
	DWORD		color;
							// DIFFUSE는 색상!
	enum class FORMAT{FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct D3DFVF_XYZ_NORMAL_TEX1
{   // 메모리 선언 순서가 가장 중요

	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vNormal;
	float u, v;
	// DIFFUSE는 색상!
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