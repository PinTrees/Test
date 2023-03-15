#pragma once
#include "string.h"
#include "stringMap.h"


// 메뉴
// 성적 입력
// 성적 조회
// 성적 출력
// 종료


// 성적 입력
// 학과선택
// 게이프로그래밍
// 게임기획


// 과목 리스트 3과목
// 각각 출력
// 과목: 점수 입력

class Menu {

public:
	SMap<String> mainMenu;
	SMap<String> classMenu;
	SMap<List<String>*> classSubMenu;

public:
	Menu() {
		Init();
	}
	~Menu() {
	}
	void Init() 
	{
		mainMenu["1"] = "성적 입력";
		mainMenu["2"] = "성적 조회";
		mainMenu["3"] = "성적 출력"; 
		mainMenu["4"] = "종료";

		classMenu["1"] = "게임 프로그래밍";
		classMenu["2"] = "게임 그래픽 디자인";
		classMenu["3"] = "게임 기획";

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

		classSubMenu["1"] = sub1;
		classSubMenu["2"] = sub2;
		classSubMenu["3"] = sub3;
	}

	String* MainMenu() {
		system("cls");
		
		String input;

		cout << "메인메뉴" << endl << endl;
		for (int i = 0; i < mainMenu.count; i++)
			cout << mainMenu.keys.elementAt(i) << ". " << mainMenu[mainMenu.keys.elementAt(i)] << endl;

		cout << endl << "선택: ";
		cin >> input;

		return &input;
	}

	String* SubjectMenu() {
		system("cls");
		
		String input;

		cout << "학과선택" << endl << endl;
		for (int i = 0; i < classMenu.count; i++)
			cout << classMenu.keys.elementAt(i) << ". " << classMenu[classMenu.keys.elementAt(i)] << endl;

		cout << endl << "선택: ";
		cin >> input;

		return &input;
	}

	String* SubjectClassMenu(String* subjectId) {
		system("cls");

		String input;

		cout << "과목점수" << endl << endl;
		for (int i = 0; i < classMenu.count; i++)
			cout << classMenu.keys.elementAt(i) << ". " << classMenu[classMenu.keys.elementAt(i)] << endl;

		cout << endl << "선택: ";
		cin >> input;

		return &input;
	}
};