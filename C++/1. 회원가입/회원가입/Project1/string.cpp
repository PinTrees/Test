#pragma once
#include <iostream>
#include "list.cpp"

using namespace std;

// �������� String �ڷᱸ�� ����
class String {

public:

	// ���ڹ迭�� ������
	char* characters = NULL;

	// ���ڿ��� ����
	int length = 0;

private:

	// ������ �� ������ ���������ÿ��� ���Ǵ� ���ڿ� ���� �Լ�ȭ
	void generate(char* constStr = nullptr, char* addStr = nullptr) {

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
	char* constToN(const char* str) 
	{
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}

public:
	// ������
	String()
	{
		length = 0;
		characters = NULL;
		generate(nullptr);
	}
	~String()
	{
	}

	// ���� template �� ���� ����Ʈ�� ������ 
	// add() �Լ��� �ƴ� [key] = �����ڸ� ����� ������ �Ҵ�� ������ �߻����� Ȯ��
	// T ������ �ʿ����� Ȯ��
	// T = NULL
	// 
	// [����]
	// https://stackoverflow.com/questions/6440483/how-to-check-null-class-in-c
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	String(const int) {
		length = 0;
		characters = NULL;
		generate(nullptr);
	}

	// ���� ���ڿ� ������
	String(const char* str)
	{
		generate(constToN(str));
	}


	// �Ҵ� ������ �������̵�
	String& operator= (char* str) {
		delete[] characters;
		generate(str, nullptr);
		return *this;
	}
	String& operator= (String str) {
		delete[] characters;
		generate(str.characters, nullptr);
		return *this;
	}
	String* operator= (const char* str) {
		delete[] characters;
		generate(constToN(str), nullptr);
		return this;
	}

	// �� ������ �������̵�
	bool operator==(String& str) {
		return compare(str.characters);
		//return !compare(str);  // str �� ������ compare ���� 0 �� �����Ѵ�.
	}
	bool operator==(int n) {
		if (characters == NULL) return true;
		return false;
	}
	bool operator==(const char* str) {
		return compare(str);
	}

	// ������ ����
	// �Ʒ� ���·� ���� �ʿ�
	//int operator> (String str)
	//{
	//	return strcmp(characters, str.characters);
	//}
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

	String& operator+=(const char* str) {
		generate(nullptr, constToN(str));
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

	// �Է�, ��� ������ �������̵�
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

