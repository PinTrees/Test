#pragma once
#include "tstring.h"

using namespace std;

TString::TString()
{
	length = 0;
	characters = NULL;
	TString::generate(nullptr);
}
TString::TString(const int)
{
	length = 0;
	characters = NULL;
	TString::generate(nullptr);
}
TString::TString(const TCHAR* str)
{
	TString::generate((TCHAR*)str);
}
TString::TString(const TString& str)
{
	TString::generate(str.characters);
}
TString::~TString() {}


// ���� ���ڿ� ������
void TString::generate(TCHAR* constStr, TCHAR* addStr)
{
	if (constStr != nullptr)
	{
		length = lstrlen(constStr) + 2;
		characters = new TCHAR[length];

		for (int i = 0; i < length; i++) characters[i] = constStr[i];
		characters[length - 1] = '\0\0';
	}

	// ���� ���ڿ��� �ű� ���ڿ��� �߰��ϴ� ������ ���
	if (addStr != nullptr)
	{
		int strLength = lstrlen(addStr);
		int newLength = length + strLength;
		TCHAR* newCharacters = new TCHAR[newLength];

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


// �Ҵ� ������ �����ε�
TString& TString::operator= (TCHAR* str)
{
	delete[] characters;
	TString::generate(str, nullptr);
	return *this;
}
TString* TString::operator= (const TString str)
{
	delete[] characters;
	TString::generate(str.characters, nullptr);
	return this;
}
TString* TString::operator= (TString* str)
{
	delete[] characters;
	TString::generate(str->characters, nullptr);
	return this;
}
TString* TString::operator= (const TCHAR* str)
{
	delete[] characters;
	TString::generate((TCHAR*)str, nullptr);
	return this;
}



// �� ������ �����ε�
bool TString::operator==(TString& str)
{
	return compare(str.characters);
	//return !compare(str);  // str �� ������ compare ���� 0 �� �����Ѵ�.
}
bool TString::operator==(int n)
{
	if (characters == NULL) return true;
	return false;
}
bool TString::operator==(const TCHAR* str)
{
	return compare(str);
}

bool TString::operator!=(const TCHAR* str)
{
	return !compare(str);
}

// ������ ����
// �Ʒ� ���·� ���� �ʿ�
//int operator> (String str)
//{
//	return strcmp(characters, str.characters);
//}
int TString::operator>(TString& str)
{
	int size = 0;

	int targetLength = lstrlen(str.characters);
	if (targetLength != length) return targetLength - length;

	for (int i = 0; i != targetLength; i++) {
		if (characters[i] > str.characters[i]) size++;
	}
	return size;
}
TString& TString::operator+(const TCHAR* str)
{
	int strLength = lstrlen(str);
	int newLength = length + strLength;
	TCHAR* newCharacters = new TCHAR[newLength];

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
TString& TString::operator+=(const TCHAR* str) {
	TString::generate(nullptr, (TCHAR*)str);
	return *this;
}
TString& TString::operator+=(TString* str) {
	TString::generate(nullptr, str->characters);
	return *this;
}
TString& TString::operator+=(TString str) {
	TString::generate(nullptr, str.characters);
	return *this;
}





List<TString*>* TString::Split(TCHAR split)
{
	List<TString*>* splits = new List<TString*>();

	int splitLength = 0; int cosuor = 0;
	for (int i = 0; i < length; i++)
	{
		if (characters[i] == split)
		{
			TCHAR* newC = new TCHAR[splitLength];

			for (int j = 0; j < splitLength; j++)
			{
				newC[j] = characters[j + cosuor];
			}
			newC[splitLength] = NULL;
			TString* newStr = new TString(newC);
			splits->Add(newStr);
			splitLength = 0;
			cosuor = i + 1;
		}
		else splitLength++;
	}

	return splits;
}
List<TString*>* TString::Split(TCHAR* split)
{
	List<TString*>* splits = new List<TString*>();
	return splits;
}


void TString::Trim()
{
	int last = 0, first = 0;
	if (characters[length - 1] == '\n' || characters[length - 1] == ' ') last++;
	if (characters[0] == '\n' || characters[0] == ' ') first++;

	if ((last + first) > 0)
	{
		int nLength = length - (last + first);
		TCHAR* nChar = new TCHAR[nLength];

		int trimIndex = 0;
		for (int i = 0; i != length; i++)
		{
			if (characters[i] != '\n' && characters[i] != ' ')  nChar[i - trimIndex] = characters[i];
			else trimIndex++;
		}
		nChar[nLength - 1] = NULL;

		delete characters;
		characters = nChar;
	}
}





bool TString::compare(const TCHAR* str)
{
	int targetLength = lstrlen(str);
	if (targetLength == 0 || length == 0) return false;
	//if (targetLength  != length) return false;

	for (int i = 0; i != targetLength; i++) {
		if (characters[i] != str[i]) return false;
	}
	return true;
}

