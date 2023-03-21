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

public:
	// ������
	String();
	~String();


	// NULL ������
	String(const int);
	String(const char* str);


	// �Ҵ� ������ �����ε�
	String& operator= (char* str);
	String& operator= (String str);
	String* operator= (const char* str);

	// �� ������ �����ε�
	bool operator==(String& str);
	bool operator==(int n);
	bool operator==(const char* str);

	bool operator!=(const char* str);

	// ������ ����
	// ���� ���� �ʿ�
	int operator>(String& str);

	// ���ڿ� ���� �����ε�
	String& operator+(const char* str);
	String& operator+=(const char* str);


	bool compare(const char* str);

	// �Է�, ��� ������ �����ε�
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend istream& operator>>(istream& cin, String& ms);
};

