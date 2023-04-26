#pragma once
#include "string.h"

/**
* �� �Լ��� ����ڰ� �ܼ�â�� �Է��� ���� ��ȯ�մϴ�.
* 
* �Է��� �ޱ� �� ���������� ����մϴ�.
* 
* �Ķ����
*	const char*: ����ڿ��� ����Ǵ� �Է� ���� �����Դϴ�.
* 
* ��ȯ
*	String: ����ڰ� �Է��� ���� ��ȯ�մϴ�.
*/
static String ConsoleReadLine(const char* inputText) {
	cout << inputText << ": ";

	char s[1000];
	cin.getline(s, 1000, '\n');

	String input = s;
	return input;
}


/**
* (***) �ۼ���
* �� �Լ��� �ֿܼ� ����� ����� �޾ƿ� ����մϴ�.
*/
static void ConsoleWirteLine(int size, String*...) {
	va_list list;
	va_start(list, size); 

	for (int i = 0; i != size; ++i) {
		cout << va_arg(list, String*);
	}
	cout << endl;

	va_end(list);
}


static void ConsoleClear() {
	system("cls");
}


#ifdef MAIN
ostream& operator<<(ostream& cout, const String& ms)
{
	if (ms.length > 0) cout << ms.characters;
	return cout;
}
ostream& operator<<(ostream& cout, const String* ms)
{
	if (ms->length > 0) cout << ms->characters;
	return cout;
}
istream& operator>>(istream& cin, String& ms)
{
	char* tmp = new char[10000];
	cin >> tmp;
	ms = tmp;
	return cin;
}
#endif // AAA == true

