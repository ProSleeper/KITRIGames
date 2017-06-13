#include "GameCommon.h"



BaseTransform::BaseTransform()
{
	m_fPosX = 0;
	m_fPosY = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	m_Tag = TAG_NONE;

	strcpy_s(m_szLayer, "None");
}


BaseTransform::~BaseTransform()
{
}
