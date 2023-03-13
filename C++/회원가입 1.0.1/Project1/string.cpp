#pragma once
#include <iostream>
#include "list.cpp"

using namespace std;

// 기초적 String 자료구조 구현
class String {

public:

	// 문자배열의 포인터
	char* characters = NULL;

	// 문자열의 길이
	int length = 0;

private:
	// 생성자 및 연산자 오버라이팅에서 사용되는 문자열 생성 함수화
	void Generate(char* constStr = nullptr, char* addStr = nullptr) {
		if (constStr != nullptr) {
			length = strlen(constStr) + 1;
			characters = new char[length];

			for (int i = 0; i != length; i++) characters[i] = constStr[i];
			characters[length - 1] = NULL;
		}

		if (addStr != nullptr) {
			int strLength = strlen(addStr);
			int newLength = length + strLength;
			char* newCharacters = new char[newLength];

			// 기초 문자열 마지막 종결문자를 제외한 부분만 복사
			for (int i = 0; i != length - 1; i++) newCharacters[i] = characters[i];
			// 기본 문자열 이후 부터 추가문자열 길이만큼 복사	length = 10
			for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = addStr[i];
			newCharacters[newLength - 1] = NULL;

			delete[] characters;
			characters = newCharacters;
			length = newLength;
		}
	}

	// const char* > char* 변환 함수
	char* constToN(const char* str) {
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}

public:
	// 생성자
	String()
	{
		length = 0;
		characters = NULL;
		Generate(nullptr);
	}
	~String()
	{
	}

	// 맵의 template 를 통한 이진트리 생성시 
	// add() 함수가 아닌 [key] = 연산자를 사용한 데이터 할당시 오류가 발생함을 확인
	// T 기초값을 총한 생성이 필요함을 확인
	// 
	// T = NULL
	// 
	// [참조]
	// https://stackoverflow.com/questions/6440483/how-to-check-null-class-in-c
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	String(const int) {
		length = 0;
		characters = NULL;
		Generate(nullptr);
	}

	// 정적 문자열 생성자
	String(const char* str) {
		Generate(constToN(str));
	}

	int operator> (int str) {
		return strcmp(characters, (char*)str);
	}
	int operator> (String str) {
		return strcmp(characters, str.characters);
	}
	int operator< (String str) {
		return strcmp(characters, str.characters);
	}

	String& operator= (char* str) {
		delete[] characters;
		Generate(str, nullptr);
		return *this;
	}
	String& operator= (String str) {
		delete[] characters;
		Generate(str.characters, nullptr);
		return *this;
	}
	String* operator= (const char* str) {
		delete[] characters;
		Generate(constToN(str), nullptr);
		return this;
	}

	bool operator==(String& str) {
		return compare(str.characters);
		//return !compare(str);  // str 과 같으면 compare 에서 0 을 리턴한다.
	}
	bool operator==(int n) {
		if (characters == NULL) return true;
		return false;
	}
	bool operator==(const char* str) {
		return compare(str);
	}

	//
	int operator>(String& str) {
		int size = 0;

		int targetLength = strlen(str.characters);
		if (targetLength != length) return targetLength - length;

		for (int i = 0; i != targetLength; i++) {
			if (characters[i] > str.characters[i]) size++;
		}
		return size;
	}

	String& operator+(const char* str) {
		int strLength = strlen(str);
		int newLength = length + strLength;
		char* newCharacters = new char[newLength];

		// 기초 문자열 마지막 종결문자를 제외한 부분만 복사
		for (int i = 0; i != length - 1; i++) newCharacters[i] = characters[i];
		// 기본 문자열 이후 부터 추가문자열 길이만큼 복사	length = 10
		for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = str[i];
		newCharacters[newLength - 1] = NULL;

		delete[] characters;
		characters = newCharacters;
		length = newLength;

		return *this;
	}

	String& operator+=(const char* str) {
		Generate(nullptr, constToN(str));
		return *this;
	}



	bool compare(const char* str) {
		int targetLength = strlen(str);
		if (targetLength == 0 || length == 0) return false;
		//if (targetLength  != length) return false;

		for (int i = 0; i != targetLength; i++) {
			if (characters[i] != str[i]) return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

