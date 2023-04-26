#include "menu.h"

Menu::Menu() {  }
Menu::~Menu() {  }


void Menu::Init() {
}


/**
* 이 함수는 메인메뉴를 출력하고 사용자의 입력값을 반환합니다.
*/
String Menu::MainMenu()
{
	system("cls");

	cout << "메인메뉴" << endl << endl;
	cout << "1. 상품 추가" << endl;
	cout << "2. 상품 출력" << endl;
	cout << "3. 상품 검색" << endl;
	cout << "4. 상품 저장" << endl;
	cout << "5. 종료" << endl << endl;

	String input = ConsoleReadLine("선택");
	return input;
}


/**
* 이 함수는 상품출력메뉴를 출력하고 사용자의 입력값을 반환합니다.
*
* 사용자의 입력값이 범위 내의 값인지 검사 후 범위를 벗어난 경우
* 선택화면을 다시 출력합니다.
*
* 반환
*	String: 사용자의 입력값을 반환합니다.
*/
String Menu::PrintMenu()
{
	while (true)
	{
		system("cls");

		cout << "출력 메뉴" << endl << endl;
		cout << "1. 상품 출력" << endl;
		cout << "2. 의류 출력 " << endl;
		cout << "3. 가전 출력" << endl << endl;

		String input = ConsoleReadLine("선택");
		if (ToInt(input) <= 3)
			return input;
	}
	return "";
}


/**
* 이 함수는 상품추가메뉴를 출력하고 사용자의 입력값을 반환합니다.
*
* 사용자의 입력값이 범위 내의 값인지 검사 후 범위를 벗어난 경우
* 선택화면을 다시 출력합니다.
*
* 반환
*	String 사용자의 입력값을 반환합니다.
*/
String Menu::InputMenu()
{
	while (true)
	{
		system("cls");

		cout << "상품 추가 목록 선택" << endl << endl;
		cout << "1. 상품 추가" << endl;
		cout << "2. 의류 추가 " << endl;
		cout << "3. 가전 추가" << endl << endl;

		String input = ConsoleReadLine("선택");

		if (ToInt(input) <= 3)
			return input;
	}
	return "";
}