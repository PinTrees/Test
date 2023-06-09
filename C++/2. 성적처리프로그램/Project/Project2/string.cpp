#pragma once
#include "string.h"

using namespace std;

String::String()
{
	length = 0;
	characters = NULL;
	String::generate(nullptr);
}
String::String(const int)
{
	length = 0;
	characters = NULL;
	String::generate(nullptr);
}
String::String(const char* str)
{
	String::generate((char*)str);
}
String::~String() {}


// 정적 문자열 생성자
void String::generate(char* constStr, char* addStr)
{
	// const char* 형태의 문자열일 경우
	if (constStr != nullptr)
	{
		length = strlen(constStr) + 1;
		characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = constStr[i];
		characters[length - 1] = NULL;
	}

	// 기존 문자열에 신규 문자열을 추가하는 형태일 경우
	if (addStr != nullptr)
	{
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


// 할당 연산자 오버로딩
String& String::operator= (char* str)
{
	delete[] characters;
	String::generate(str, nullptr);
	return *this;
}
String& String::operator= (String str)
{
	delete[] characters;
	String::generate(str.characters, nullptr);
	return *this;
}
String* String::operator= (const char* str)
{
	delete[] characters;
	String::generate((char*)str, nullptr);
	return this;
}



// 비교 연산자 오버로딩
bool String::operator==(String& str)
{
	return compare(str.characters);
	//return !compare(str);  // str 과 같으면 compare 에서 0 을 리턴한다.
}
bool String::operator==(int n)
{
	if (characters == NULL) return true;
	return false;
}
bool String::operator==(const char* str)
{
	return compare(str);
}

bool String::operator!=(const char* str)
{
	return !compare(str);
}

// 사용되지 않음
// 아래 형태로 변경 필요
//int operator> (String str)
//{
//	return strcmp(characters, str.characters);
//}
int String::operator>(String& str)
{
	int size = 0;

	int targetLength = strlen(str.characters);
	if (targetLength != length) return targetLength - length;

	for (int i = 0; i != targetLength; i++) {
		if (characters[i] > str.characters[i]) size++;
	}
	return size;
}
String& String::operator+(const char* str)
{
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
String& String::operator+=(const char* str) {
	String::generate(nullptr, (char*)str);
	return *this;
}






bool String::compare(const char* str) 
{
	int targetLength = strlen(str);
	if (targetLength == 0 || length == 0) return false;
	//if (targetLength  != length) return false;

	for (int i = 0; i != targetLength; i++) {
		if (characters[i] != str[i]) return false;
	}
	return true;
}

