#pragma once
#include <iostream>
#include <windows.h>
#include "list.h"

using namespace std;

class TString {

public:
	TCHAR* characters = NULL;
	int	  length = 0;

private:
	// String 내부에서만 사용할 함수
	void generate(TCHAR* constStr = nullptr, TCHAR* addStr = nullptr);
	bool compare(const TCHAR* str);

public:
	// 생성자
	TString();
	TString(const int);
	TString(const TCHAR* str);
	TString(const TString& str);
	~TString();



	// 연산자 오버로딩
	TString& operator=	(TCHAR* str);
	TString* operator=	(TString str);
	TString* operator=	(TString* str);
	TString* operator=	(const TCHAR* str);

	TString& operator+	(const TCHAR* str);
	TString& operator+=	(const TCHAR* str);
	TString& operator+=	(TString* str);
	TString& operator+=	(TString str);

	bool	operator==	(TString& str);
	bool	operator==	(int n);
	bool	operator==	(const TCHAR* str);




	// 내부 함수 구현
	// 문자열을 특정 문자를 기준으로 자른 목록을 반환
	List<TString*>* Split(TCHAR split);
	List<TString*>* Split(TCHAR* split);

	// 문자열 끝 [ 공백, 줄바꿈 ] 문자를 제거한 문자열을 반환
	void		   Trim();




	// 입력, 출력 연산자 오버로딩
	friend ostream& operator<<(ostream& cout, const TString& ms);
	friend ostream& operator<<(ostream& cout, const TString* ms);
	friend istream& operator>>(istream& cin, TString& ms);




	// 사용되지 않음
	// 추후 변경 필요
	int		operator>	(TString& str);
	bool	operator!=	(const TCHAR* str);
};

