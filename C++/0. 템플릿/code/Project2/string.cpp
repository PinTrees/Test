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
* ���ڿ� �޸� ���� �����κ� �߰�
*/
String::~String() {
	if (characters != NULL) {
	   delete characters;
	}
}





/**
* �����Լ�
* ���ڿ� ����
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

	// ���� ���ڿ��� �ű� ���ڿ��� �߰��ϴ� ������ ���
	if (addStr != nullptr)
	{
		int strLength = strlen(addStr);
		int newLength = length + strLength;
		char* newCharacters = new char[newLength];

		// ���� ���ڿ� ������ ���Ṯ�ڸ� ������ �κи� ����
		for (int i = 0; i < length - 1; i++) newCharacters[i] = characters[i];

		// �⺻ ���ڿ� ���� ���� �߰����ڿ� ���̸�ŭ ����	length = 10
		for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = addStr[i];
		newCharacters[newLength - 1] = NULL;

		delete[] characters;
		characters = newCharacters;
		length = newLength;
	}
}


/**
* �����Լ�
* ���ڿ� ��
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
* �����Լ�
* Boyer-Moore ���ڿ� �˻� �˰��� 
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
* �Ҵ� ������ �����ε�
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
* �� ������ �����ε�
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
* �Ҵ� �� �߰������� �����ε�
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

	// ���� ���ڿ� ������ ���Ṯ�ڸ� ������ �κи� ����
	for (int i = 0; i != length - 1; i++) newCharacters[i] = characters[i];
	// �⺻ ���ڿ� ���� ���� �߰����ڿ� ���̸�ŭ ����	length = 10
	for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = str[i];
	newCharacters[newLength - 1] = NULL;

	delete[] characters;
	characters = newCharacters;
	length = newLength;

	return *this;
}




/**
* �� �Լ��� ���� ���ڿ��� Ư�� ���ڸ� �������� �ڸ� ���ڿ� ����� ��ȯ�մϴ�.
*
* �Ķ����
*	char split: ���ڿ��� �ڸ� �������Դϴ�.
*
* ��ȯ
*	List<String*>*: ���ڿ��� ���ڷ� �ڸ� ����� ��ȯ�մϴ�.
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
* @ ������
* �� �Լ��� ���� ���ڿ��� Ư�� ���ڿ��� �������� �ڸ� ���ڿ� ����� ��ȯ�մϴ�.
*
* �Ķ����
*	char split: ���ڿ��� �ڸ� ���ع��ڿ� �Դϴ�.
*
* ��ȯ
*	List<String*>*: ���ڿ��� ���ڿ��� �ڸ� ����� ��ȯ�մϴ�.
*/
List<String*>* String::Split(char* split)
{
	List<String*>* splits = new List<String*>();
	return splits;
}


/**
* �� �Լ��� ���� ���ڿ��� ���۰� ���� Ư������( ' ', '\n' )�� ������ ���ڿ��� ��ȯ �� �����ϴ� �Լ��Դϴ�.
*
* ��ȯ
*	String*: ����� ���� �ν��Ͻ��� ��ȯ�մϴ�.
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
* �� �Լ��� Ư�� ���ڿ��� ���� ���ڿ��� ���Կ��� ����� ��ȯ�մϴ�.
*
* �Ķ����
*	String* str: ���� ���ڿ��� ���� �񱳹��ڿ��Դϴ�.
*
* ��ȯ
*	bool: �� ���ڿ��� ���ԵǾ��� ��� true, �ʾ��� ��� false�� ��ȯ�մϴ�.
*/
bool String::Contain(String* str) {
	int result = bm_match(characters, str->characters);
	if (result == -1) return false;
	else return true;
}





/**
* �ڵ� ���� �ʿ�
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