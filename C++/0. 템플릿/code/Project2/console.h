#pragma once
#include "string.h"

/**
* 이 함수는 사용자가 콘솔창에 입력한 값을 반환합니다.
* 
* 입력을 받기 전 유도문구를 출력합니다.
* 
* 파라미터
*	const char*: 사용자에게 노출되는 입력 유도 문구입니다.
* 
* 반환
*	String: 사용자가 입력한 값을 반환합니다.
*/
static String ConsoleReadLine(const char* inputText) {
	cout << inputText << ": ";

	char s[1000];
	cin.getline(s, 1000, '\n');

	String input = s;
	return input;
}


/**
* (***) 작성중
* 이 함수는 콘솔에 출력할 목록을 받아와 출력합니다.
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

