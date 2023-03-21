#pragma once
#include <iostream>
#include "list.h"

using namespace std;


// 기초적인 String 자료구조 구현
class String {

public:
	char* characters = NULL;
	int length = 0;

private:
	void generate(char* constStr = nullptr, char* addStr = nullptr);

public:
	// 생성자
	String();
	~String();


	// NULL 생성자
	String(const int);
	String(const char* str);


	// 할당 연산자 오버로딩
	String& operator= (char* str);
	String& operator= (String str);
	String* operator= (const char* str);

	// 비교 연산자 오버로딩
	bool operator==(String& str);
	bool operator==(int n);
	bool operator==(const char* str);

	bool operator!=(const char* str);

	// 사용되지 않음
	// 추후 변경 필요
	int operator>(String& str);

	// 문자열 연산 오버로딩
	String& operator+(const char* str);
	String& operator+=(const char* str);


	bool compare(const char* str);

	// 입력, 출력 연산자 오버로딩
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

