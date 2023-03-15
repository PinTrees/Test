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
	char* constToN(const char* str);

public:
	// 생성자
	String();
	~String();

	// 맵의 template 를 통한 이진트리 생성시 
	// add() 함수가 아닌 [key] = 연산자를 사용한 데이터 할당시 오류가 발생함을 확인
	// T 생성이 필요함을 확인
	// T = NULL
	// 
	// [참조]
	// https://stackoverflow.com/questions/6440483/how-to-check-null-class-in-c
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	// 정적 문자열 생성자
	String(const int);
	String(const char* str);


	// 할당 연산자 오버라이딩
	String& operator= (char* str);
	String& operator= (String str);
	String* operator= (const char* str);

	// 비교 연산자 오버라이딩
	bool operator==(String& str);
	bool operator==(int n);
	bool operator==(const char* str);

	// 사용되지 않음
	// 아래 형태로 변경 필요
	//int operator> (String str)
	//{
	//	return strcmp(characters, str.characters);
	//}
	int operator>(String& str);


	String& operator+(const char* str);
	String& operator+=(const char* str);


	bool compare(const char* str);

	// 입력, 출력 연산자 오버라이딩
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

