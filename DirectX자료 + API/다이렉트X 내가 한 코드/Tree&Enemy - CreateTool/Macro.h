#pragma once

// 매크로 함수 ================================================================ //
// 주의사항 : 매크로 함수 연결(\)문자 뒤에 주석 넣지 말것!!!! 에러발생!!!

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

// 메모리 해제 및 반환 함수
#define SAFE_DELETE(p)			{ if(p)	{delete		p; p = NULL;} }
#define SAFE_DELETE_ARRAY(p)	{ if(p)	{delete []	p; p = NULL;} }
#define SAFE_RELEASE(p)			{ if(p)	{p->Release(); p = NULL;} }

// 싱글톤
// - 싱글톤 활용 클래스는 생성자와 소멸자를 제거하고 매크로를 적용함
#define SINGLETONE(class_name) \
	private: class_name(void); ~class_name(void); \
	public: static class_name* GetInstance() \
	{\
		static class_name instance;\
		return &instance;\
	}\


// 프로퍼티(getter, setter)
#define PROPERTY_FUNC(type, funcName, value) \
    protected: type value; \
	public: type Get##funcName()		 { return value; } \
	public: void Set##funcName(type _v)  { value = _v;   } \
	private:

#define GETTER(type, funcName, value) \
    protected: type value; \
	public: type Get##funcName()		 { return value; } \
	private:

