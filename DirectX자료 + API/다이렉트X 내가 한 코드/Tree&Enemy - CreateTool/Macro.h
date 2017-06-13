#pragma once

// ��ũ�� �Լ� ================================================================ //
// ���ǻ��� : ��ũ�� �Լ� ����(\)���� �ڿ� �ּ� ���� ����!!!! �����߻�!!!

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

// �޸� ���� �� ��ȯ �Լ�
#define SAFE_DELETE(p)			{ if(p)	{delete		p; p = NULL;} }
#define SAFE_DELETE_ARRAY(p)	{ if(p)	{delete []	p; p = NULL;} }
#define SAFE_RELEASE(p)			{ if(p)	{p->Release(); p = NULL;} }

// �̱���
// - �̱��� Ȱ�� Ŭ������ �����ڿ� �Ҹ��ڸ� �����ϰ� ��ũ�θ� ������
#define SINGLETONE(class_name) \
	private: class_name(void); ~class_name(void); \
	public: static class_name* GetInstance() \
	{\
		static class_name instance;\
		return &instance;\
	}\


// ������Ƽ(getter, setter)
#define PROPERTY_FUNC(type, funcName, value) \
    protected: type value; \
	public: type Get##funcName()		 { return value; } \
	public: void Set##funcName(type _v)  { value = _v;   } \
	private:

#define GETTER(type, funcName, value) \
    protected: type value; \
	public: type Get##funcName()		 { return value; } \
	private:

