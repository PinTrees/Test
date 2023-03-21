#include "menu.h"


Menu::Menu() {  }
Menu::~Menu() {  }

// 메뉴 초기화
void Menu::Init()
{
	// 메인메뉴 세팅
	mainMenu["1"] = "성적 입력";
	mainMenu["2"] = "성적 조회";
	mainMenu["3"] = "성적 출력";
	mainMenu["4"] = "종료";

	// 학과 종류 세팅 Key 값을 통한 구분
	departmentMenu["1"] = "게임 프로그래밍";
	departmentMenu["2"] = "게임 그래픽 디자인";
	departmentMenu["3"] = "게임 기획";

	// 해당 학과 Key와 대응되는 과목 세팅
	List<String>* sub1 = new List<String>();
	sub1->add("C++");
	sub1->add("자료구조");
	sub1->add("알고리즘");

	List<String>* sub2 = new List<String>();
	sub2->add("3D MAX");
	sub2->add("Blender");
	sub2->add("Spine 2D");

	List<String>* sub3 = new List<String>();
	sub3->add("기획과목1");
	sub3->add("기획과목2");
	sub3->add("기획과목3");

	// 해당 학과 Key와 대응되도록 과목과 학과 연결 / [학과 Key] = 과목
	classMenu["1"] = sub1;
	classMenu["2"] = sub2;
	classMenu["3"] = sub3;
}


// 메인메뉴 출력 및 선택 함수
String* Menu::MainMenu()
{
	system("cls");

	cout << "메인메뉴" << endl << endl;
	for (int i = 0; i < mainMenu.count; i++)
	{
		cout << mainMenu.keys.elementAt(i) << ". " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
	}

	String input;
	cout << endl << "선택: ";
	cin >> input;

	return &input;
}

// 학과 출력 및 선택 함수
String Menu::DepartmentMenu()
{
	system("cls");

	cout << "학과선택" << endl << endl;
	for (int i = 0; i < departmentMenu.count; i++) 
	{
		cout << departmentMenu.keys.elementAt(i) << ". " << departmentMenu[departmentMenu.keys.elementAt(i)] << endl;
	}

	String input;
	cout << endl << "선택: ";
	cin >> input;


	if (!departmentMenu.ContainKey(input.characters)) input = "";

	return input;
}
