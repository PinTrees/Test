#pragma once
#include <iostream>
#include "list.h"

using namespace std;

// 주석 cpp 포함

/**
* 미완성
* 이 클래스틑 문자열을 다루기 위한 클래스 입니다.
* 
* 객체 복사 참조 역참조시 메모리 해제 및 할당 확인 필요
*/
class String {

public:
	char* characters = NULL;
	int	  length = 0; 

private:
	/**
	* 내부함수
	*/
	void generate(char* constStr = nullptr, char* addStr = nullptr);
	bool compare(const char* str);
	int bm_match(char[], char[]);

public:
	String();
	String(const int);
	String(const char* str);
	String(const String& str);
	~String();
	
	
	
	
	/** 기초 연산자 오버로딩 */
	String& operator=	(const char& str);
	String& operator=	(char* str);
	String* operator=	(String str);
	String* operator=	(String* str);
	String* operator=	(const char* str);
	
	String& operator+	(const char* str);
	String& operator+=	(const char* str);
	String& operator+=	(String* str);
	String& operator+=	(String str);

	bool	operator==	(String& str);
	bool	operator==	(int n);
	bool	operator==	(const char* str);

	/** 입출력 연산자 오버로딩입니다. */
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend ostream& operator<<(ostream& cout, const String* ms);
	friend istream& operator>>(istream& cin, String& ms);




	/** 이 함수는 현재 문자열을 특정 문자를 기준으로 자른 문자열 목록을 반환합니다. */
	List<String*>* Split(char split);

	/** 이 함수는 현재 문자열을 특정 문자열을 기준으로 자른 문자열 목록을 반환합니다. */
	List<String*>* Split(char* split);

	/** 이 함수는 현재 문자열의 시작과 끝의 특정문자( ' ', '\n' )를 제거한 문자열을 반환 및 변경하는 함수입니다. */
	String*		   Trim();

	/** 이 함수는 특정 문자열과 현재 문자열의 포함여부 결과를 반환합니다. */
	bool		   Contain(String* str);




	/** 삭제 예정 */
	int		operator>	(String& str);
	bool	operator!=	(const char* str);
};

