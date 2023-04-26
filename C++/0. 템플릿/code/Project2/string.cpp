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
String::String(const String& str)
{
	String::generate(str.characters);
}
/**
* 문자열 메모리 해제 누락부분 추가
*/
String::~String() {
	if (characters != NULL) {
	   delete characters;
	}
}





/**
* 내부함수
* 문자열 생성
*/
void String::generate(char* constStr, char* addStr)
{
	if (constStr != nullptr)
	{
		length = strlen(constStr) + 1;
		characters = new char[length];

		for (int i = 0; i < length; i++) characters[i] = constStr[i];
		characters[length - 1] = NULL;
	}

	// 기존 문자열에 신규 문자열을 추가하는 형태일 경우
	if (addStr != nullptr)
	{
		int strLength = strlen(addStr);
		int newLength = length + strLength;
		char* newCharacters = new char[newLength];

		// 기초 문자열 마지막 종결문자를 제외한 부분만 복사
		for (int i = 0; i < length - 1; i++) newCharacters[i] = characters[i];

		// 기본 문자열 이후 부터 추가문자열 길이만큼 복사	length = 10
		for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = addStr[i];
		newCharacters[newLength - 1] = NULL;

		delete[] characters;
		characters = newCharacters;
		length = newLength;
	}
}


/**
* 내부함수
* 문자열 비교
*/
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


/**
* 내부함수
* Boyer-Moore 문자열 검색 알고리즘 
*/
int String::bm_match(char txt[], char pat[])
{
	int pt;						
	int pp;						
	int txt_len = strlen(txt);			
	int pat_len = strlen(pat);			
	int skip[UCHAR_MAX + 1];			

	for (pt = 0; pt <= UCHAR_MAX; pt++)		
		skip[pt] = pat_len;

	for (pt = 0; pt < pat_len - 1; pt++)
		skip[pat[pt]] = pat_len - pt - 1;	

	while (pt < txt_len) {
		pp = pat_len - 1; 		
		while (txt[pt] == pat[pp]) {
			if (pp == 0)
				return pt;
			pp--;
			pt--;
		}
		pt += (skip[txt[pt]] > pat_len - pp) ? skip[txt[pt]] : pat_len - pp;
	}

	return -1;
}





/**
* 할당 연산자 오버로딩
*/
String& String::operator= (char* str)
{
	delete[] characters;
	String::generate(str, nullptr);
	return *this;
}
String* String::operator= (const String str)
{
	delete[] characters;
	String::generate(str.characters, nullptr);
	return this;
}
String* String::operator= (String* str)
{
	delete[] characters;
	String::generate(str->characters, nullptr);
	return this;
} 
String* String::operator= (const char* str)
{
	delete[] characters;
	String::generate((char*)str, nullptr);
	return this;
}


/**
* 비교 연산자 오버로딩
*/
bool String::operator==(String& str)
{
	return compare(str.characters);
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


/**
* 할당 및 추가연산자 오버로딩
*/
String& String::operator+=(const char* str) {
	String::generate(nullptr, (char*)str);
	return *this;
}
String& String::operator+=(String* str) {
	String::generate(nullptr, str->characters);
	return *this;
}
String& String::operator+=(String str) {
	String::generate(nullptr, str.characters);
	return *this;
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




/**
* 이 함수는 현재 문자열을 특정 문자를 기준으로 자른 문자열 목록을 반환합니다.
*
* 파라미터
*	char split: 문자열을 자를 구분자입니다.
*
* 반환
*	List<String*>*: 문자열을 문자로 자른 목록을 반환합니다.
*/
List<String*>* String::Split(char split)
{
	List<String*>* splits = new List<String*>();

	int splitLength = 0; int cosuor = 0;
	for (int i = 0; i < length; i++)
	{
		if (characters[i] == split)
		{
			char* newC = new char[splitLength];

			for (int j = 0; j < splitLength; j++) 
			{
				newC[j] = characters[j + cosuor];
			}
			newC[splitLength] = NULL;
			String* newStr = new String(newC);
			splits->Add(newStr);
			splitLength = 0;
			cosuor = i + 1;
		}
		else splitLength++;
	}

	return splits;
}


/**
* @ 개발중
* 이 함수는 현재 문자열을 특정 문자열을 기준으로 자른 문자열 목록을 반환합니다.
*
* 파라미터
*	char split: 문자열을 자를 기준문자열 입니다.
*
* 반환
*	List<String*>*: 문자열을 문자열로 자른 목록을 반환합니다.
*/
List<String*>* String::Split(char* split)
{
	List<String*>* splits = new List<String*>();
	return splits;
}


/**
* 이 함수는 현재 문자열의 시작과 끝의 특정문자( ' ', '\n' )를 제거한 문자열을 반환 및 변경하는 함수입니다.
*
* 반환
*	String*: 변경된 현재 인스턴스를 반환합니다.
*/
String* String::Trim()
{
	int last = 0, first = 0;
	if (characters[length - 1] == '\n' || characters[length - 1] == ' ') {
		last++;
		characters[length - 1] = '`';
	}
	if (characters[0] == '\n' || characters[0] == ' ') {
		first++;
		characters[0] = '`';
	}

	if ((last + first) > 0)
	{
		int nLength = length - (last + first);
		char* nChar = new char[nLength];

		int trimIndex = 0;
		for (int i = 0; i != length; i++)
		{
			if (characters[i] != '`')  nChar[i - trimIndex] = characters[i];
			else trimIndex++;
		}
		nChar[nLength - 1] = NULL;

		delete characters;
		characters = nChar;
	}
	return this;
}


/**
* 이 함수는 특정 문자열과 현재 문자열의 포함여부 결과를 반환합니다.
*
* 파라미터
*	String* str: 현재 문자열과 비교할 비교문자열입니다.
*
* 반환
*	bool: 비교 문자열이 포함되었을 경우 true, 않았을 경우 false를 반환합니다.
*/
bool String::Contain(String* str) {
	int result = bm_match(characters, str->characters);
	if (result == -1) return false;
	else return true;
}





/**
* 코드 변경 필요
*
* int operator> (String str) {
*	return strcmp(characters, str.characters);
* }
*/
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