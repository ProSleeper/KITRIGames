#pragma once
class BaseScene 
{
protected:
	HDC m_hDC;


public:
	virtual void Init(HDC _hDc) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;


	BaseScene();
	virtual ~BaseScene();
};

