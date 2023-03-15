#pragma once
#include <iostream>
#include "list.h"
#include "global.h"
#include "string.h"
#include "list.h"
#include "student.h"
#include "stringMap.h"
#include "menu.h"

class Manager {

public:
	SMap<Student*>* students;
	Menu* menu;


	void Init() {
		students = new SMap<Student*>();
		menu = new Menu();

	}


	void Run() {
		while (true)
		{
			String* select = menu->MainMenu();

			if (*select == "1") {
				CreateRank();
			}
			else if (*select == "2") {
				SearchRank();
			}
			else if (*select == "3") {

			}
			else if (*select == "4") {

			}
		}
	}




	void CreateRank() {
		String* subjectSelect = menu->SubjectMenu();
        List<String>* subjects = menu->classSubMenu[subjectSelect->characters];

		system("cls");
		cout << "�л����� �Է�" << endl << endl;

		String input;

		cout << "�̸�";
		cin >> input;

		cout << "�й�";
		cin >> input;

		
		cout << endl << "�л����� �Է�" << endl << endl;

		for (int i = 0; i < subjects->count; i++) {
			cout << subjects->elementAt(i);
			cin >> input;

			// ���� ó�� �Լ� �߰�
		}

		Student* ss = new Student();
		students->add(input.characters, ss);
	}


	void SearchRank() {
		system("cls");
		cout << "�л����� �˻�" << endl << endl;

		String input;

		cout << "�й�";
		cin >> input;
	}
};