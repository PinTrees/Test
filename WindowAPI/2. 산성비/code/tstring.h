#pragma once
#include <iostream>
#include <windows.h>
#include "list.h"

using namespace std;

class TString {

public:
	TCHAR* characters = NULL;
	int	  length = 0;

private:
	// String ���ο����� ����� �Լ�
	void generate(TCHAR* constStr = nullptr, TCHAR* addStr = nullptr);
	bool compare(const TCHAR* str);

public:
	// ������
	TString();
	TString(const int);
	TString(const TCHAR* str);
	TString(const TString& str);
	~TString();



	// ������ �����ε�
	TString& operator=	(TCHAR* str);
	TString* operator=	(TString str);
	TString* operator=	(TString* str);
	TString* operator=	(const TCHAR* str);

	TString& operator+	(const TCHAR* str);
	TString& operator+=	(const TCHAR* str);
	TString& operator+=	(TString* str);
	TString& operator+=	(TString str);

	bool	operator==	(TString& str);
	bool	operator==	(int n);
	bool	operator==	(const TCHAR* str);




	// ���� �Լ� ����
	// ���ڿ��� Ư�� ���ڸ� �������� �ڸ� ����� ��ȯ
	List<TString*>* Split(TCHAR split);
	List<TString*>* Split(TCHAR* split);

	// ���ڿ� �� [ ����, �ٹٲ� ] ���ڸ� ������ ���ڿ��� ��ȯ
	void		   Trim();




	// �Է�, ��� ������ �����ε�
	friend ostream& operator<<(ostream& cout, const TString& ms);
	friend ostream& operator<<(ostream& cout, const TString* ms);
	friend istream& operator>>(istream& cin, TString& ms);




	// ������ ����
	// ���� ���� �ʿ�
	int		operator>	(TString& str);
	bool	operator!=	(const TCHAR* str);
};

