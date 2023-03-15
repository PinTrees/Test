#pragma once
#include <iostream>
#include "list.h"
#include "string.h"

using namespace std;

// ���� template �� ���� ����Ʈ�� ������ 
// add() �Լ��� �ƴ� [key] = �����ڸ� ����� ������ �Ҵ�� ������ �߻����� Ȯ��
// T ������ �ʿ����� Ȯ��
// T = NULL
// 
// [����]
// https://stackoverflow.com/questions/6440483/how-to-check-null-class-in-c
// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
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
	String::generate(constToN(str));
}
String::~String() {}


// ���� ���ڿ� ������
void String::generate(char* constStr, char* addStr)
{
	// const char* ������ ���ڿ��� ���
	if (constStr != nullptr)
	{
		length = strlen(constStr) + 1;
		characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = constStr[i];
		characters[length - 1] = NULL;
	}

	// ���� ���ڿ��� �ű� ���ڿ��� �߰��ϴ� ������ ���
	if (addStr != nullptr)
	{
		int strLength = strlen(addStr);
		int newLength = length + strLength;
		char* newCharacters = new char[newLength];

		// ���� ���ڿ� ������ ���Ṯ�ڸ� ������ �κи� ����
		for (int i = 0; i != length - 1; i++) newCharacters[i] = characters[i];

		// �⺻ ���ڿ� ���� ���� �߰����ڿ� ���̸�ŭ ����	length = 10
		for (int i = 0; i != strLength; i++) newCharacters[length - 1 + i] = addStr[i];
		newCharacters[newLength - 1] = NULL;

		delete[] characters;
		characters = newCharacters;
		length = newLength;
	}
}
// const char* > char* ��ȯ �Լ�
char* String::constToN(const char* str)
{
	int length = strlen(str) + 1;
	char* characters = new char[length];

	for (int i = 0; i != length; i++) characters[i] = str[i];
	characters[length - 1] = NULL;

	return characters;
}



// �Ҵ� ������ �������̵�
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
	String::generate(constToN(str), nullptr);
	return this;
}



// �� ������ �������̵�
bool String::operator==(String& str)
{
	return compare(str.characters);
	//return !compare(str);  // str �� ������ compare ���� 0 �� �����Ѵ�.
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

// ������ ����
// �Ʒ� ���·� ���� �ʿ�
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
String& String::operator+(const char* str) {
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
String& String::operator+=(const char* str) {
	String::generate(nullptr, constToN(str));
	return *this;
}






bool String::compare(const char* str) {
	int targetLength = strlen(str);
	if (targetLength == 0 || length == 0) return false;
	//if (targetLength  != length) return false;

	for (int i = 0; i != targetLength; i++) {
		if (characters[i] != str[i]) return false;
	}
	return true;
}

