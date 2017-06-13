#include "Singleton.h"

template<typename T>
T* Singleton<T>::m_pInstance = 0;

template<typename T>
T* Singleton<T>::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new T;
	}
	return m_pInstance;
}
template<typename T>
void Singleton<T>::Destroy()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = 0;
	}
}



