#pragma once
#include "string.h"
#include "stringMap.h"


// �޴�
// ���� �Է�
// ���� ��ȸ
// ���� ���
// ����


// ���� �Է�
// �а�����
// �������α׷���
// ���ӱ�ȹ


// ���� ����Ʈ 3����
// ���� ���
// ����: ���� �Է�

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
		mainMenu["1"] = "���� �Է�";
		mainMenu["2"] = "���� ��ȸ";
		mainMenu["3"] = "���� ���"; 
		mainMenu["4"] = "����";

		classMenu["1"] = "���� ���α׷���";
		classMenu["2"] = "���� �׷��� ������";
		classMenu["3"] = "���� ��ȹ";

		List<String>* sub1 = new List<String>();
		sub1->add("C++");
		sub1->add("�ڷᱸ��");
		sub1->add("�˰���");

		List<String>* sub2 = new List<String>();
		sub2->add("3D MAX");
		sub2->add("Blender");
		sub2->add("Spine 2D");

		List<String>* sub3 = new List<String>();
		sub3->add("��ȹ����1");
		sub3->add("��ȹ����2");
		sub3->add("��ȹ����3");

		classSubMenu["1"] = sub1;
		classSubMenu["2"] = sub2;
		classSubMenu["3"] = sub3;
	}

	String* MainMenu() {
		system("cls");
		
		String input;

		cout << "���θ޴�" << endl << endl;
		for (int i = 0; i < mainMenu.count; i++)
			cout << mainMenu.keys.elementAt(i) << ". " << mainMenu[mainMenu.keys.elementAt(i)] << endl;

		cout << endl << "����: ";
		cin >> input;

		return &input;
	}

	String* SubjectMenu() {
		system("cls");
		
		String input;

		cout << "�а�����" << endl << endl;
		for (int i = 0; i < classMenu.count; i++)
			cout << classMenu.keys.elementAt(i) << ". " << classMenu[classMenu.keys.elementAt(i)] << endl;

		cout << endl << "����: ";
		cin >> input;

		return &input;
	}

	String* SubjectClassMenu(String* subjectId) {
		system("cls");

		String input;

		cout << "��������" << endl << endl;
		for (int i = 0; i < classMenu.count; i++)
			cout << classMenu.keys.elementAt(i) << ". " << classMenu[classMenu.keys.elementAt(i)] << endl;

		cout << endl << "����: ";
		cin >> input;

		return &input;
	}
};