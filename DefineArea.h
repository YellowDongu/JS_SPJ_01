#pragma once

#define DECLARE_SINGLETON(className)\
private:\
	className() {}\
public:\
	static className* getInstance()\
	{\
		static className s_instance;\
		return &s_instance;\
	}\


// 동적할당 - 힙 영역용
#define CREATE_SINGLETON(className)\
private:\
	className();\
	~className();\
	className(const className& rhs) = delete;\
	className operator = (className& rObj) = delete;\
	static className* m_pInstance;\
public:\
	static className* getInstance()\
	{\
		if (!m_pInstance)\
		{\
			m_pInstance = new className;\
		}\
		return m_pInstance;\
	}\
	static void	destroyInstance()\
	{\
		if (m_pInstance)\
		{\
			delete m_pInstance;\
			m_pInstance = nullptr;\
		}\
	}\

// 동적할당 해제
#define DELETE_SINGLETON(className) className::destroyInstance()
// 인스턴스 불러오는 법
#define GET_SINGLETON(className) className::getInstance()

