#pragma once
#include <iostream>
#include "list.h"

using namespace std;

// �ּ� cpp ����

/**
* �̿ϼ�
* �� Ŭ�����z ���ڿ��� �ٷ�� ���� Ŭ���� �Դϴ�.
* 
* ��ü ���� ���� �������� �޸� ���� �� �Ҵ� Ȯ�� �ʿ�
*/
class String {

public:
	char* characters = NULL;
	int	  length = 0; 

private:
	/**
	* �����Լ�
	*/
	void generate(char* constStr = nullptr, char* addStr = nullptr);
	bool compare(const char* str);
	int bm_match(char[], char[]);

public:
	String();
	String(const int);
	String(const char* str);
	String(const String& str);
	~String();
	
	
	
	
	/** ���� ������ �����ε� */
	String& operator=	(const char& str);
	String& operator=	(char* str);
	String* operator=	(String str);
	String* operator=	(String* str);
	String* operator=	(const char* str);
	
	String& operator+	(const char* str);
	String& operator+=	(const char* str);
	String& operator+=	(String* str);
	String& operator+=	(String str);

	bool	operator==	(String& str);
	bool	operator==	(int n);
	bool	operator==	(const char* str);

	/** ����� ������ �����ε��Դϴ�. */
	friend ostream& operator<<(ostream& cout, const String& ms);
	friend ostream& operator<<(ostream& cout, const String* ms);
	friend istream& operator>>(istream& cin, String& ms);




	/** �� �Լ��� ���� ���ڿ��� Ư�� ���ڸ� �������� �ڸ� ���ڿ� ����� ��ȯ�մϴ�. */
	List<String*>* Split(char split);

	/** �� �Լ��� ���� ���ڿ��� Ư�� ���ڿ��� �������� �ڸ� ���ڿ� ����� ��ȯ�մϴ�. */
	List<String*>* Split(char* split);

	/** �� �Լ��� ���� ���ڿ��� ���۰� ���� Ư������( ' ', '\n' )�� ������ ���ڿ��� ��ȯ �� �����ϴ� �Լ��Դϴ�. */
	String*		   Trim();

	/** �� �Լ��� Ư�� ���ڿ��� ���� ���ڿ��� ���Կ��� ����� ��ȯ�մϴ�. */
	bool		   Contain(String* str);




	/** ���� ���� */
	int		operator>	(String& str);
	bool	operator!=	(const char* str);
};

