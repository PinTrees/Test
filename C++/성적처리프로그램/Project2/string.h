#pragma once
#include <iostream>
#include "list.h"

using namespace std;


// �������� String �ڷᱸ�� ����
class String {

public:
	char* characters = NULL;
	int length = 0;

private:
	void generate(char* constStr = nullptr, char* addStr = nullptr);
	char* constToN(const char* str);

public:
	// ������
	String();
	~String();

	// ���� template �� ���� ����Ʈ�� ������ 
	// add() �Լ��� �ƴ� [key] = �����ڸ� ����� ������ �Ҵ�� ������ �߻����� Ȯ��
	// T ������ �ʿ����� Ȯ��
	// T = NULL
	// 
	// [����]
	// https://stackoverflow.com/questions/6440483/how-to-check-null-class-in-c
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	// ���� ���ڿ� ������
	String(const int);
	String(const char* str);


	// �Ҵ� ������ �������̵�
	String& operator= (char* str);
	String& operator= (String str);
	String* operator= (const char* str);

	// �� ������ �������̵�
	bool operator==(String& str);
	bool operator==(int n);
	bool operator==(const char* str);

	// ������ ����
	// �Ʒ� ���·� ���� �ʿ�
	//int operator> (String str)
	//{
	//	return strcmp(characters, str.characters);
	//}
	int operator>(String& str);


	String& operator+(const char* str);
	String& operator+=(const char* str);


	bool compare(const char* str);

	// �Է�, ��� ������ �������̵�
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

