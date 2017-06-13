#pragma once

template<typename T>
class Singleton
{
private:
	static T *m_pInstance;

public:
	Singleton() {};
	virtual ~Singleton() {};

	static T* GetInstance();
	void Destroy();
};
