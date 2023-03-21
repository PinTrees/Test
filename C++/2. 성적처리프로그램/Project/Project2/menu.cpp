#include "menu.h"


Menu::Menu() {  }
Menu::~Menu() {  }

// �޴� �ʱ�ȭ
void Menu::Init()
{
	// ���θ޴� ����
	mainMenu["1"] = "���� �Է�";
	mainMenu["2"] = "���� ��ȸ";
	mainMenu["3"] = "���� ���";
	mainMenu["4"] = "����";

	// �а� ���� ���� Key ���� ���� ����
	departmentMenu["1"] = "���� ���α׷���";
	departmentMenu["2"] = "���� �׷��� ������";
	departmentMenu["3"] = "���� ��ȹ";

	// �ش� �а� Key�� �����Ǵ� ���� ����
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

	// �ش� �а� Key�� �����ǵ��� ����� �а� ���� / [�а� Key] = ����
	classMenu["1"] = sub1;
	classMenu["2"] = sub2;
	classMenu["3"] = sub3;
}


// ���θ޴� ��� �� ���� �Լ�
String* Menu::MainMenu()
{
	system("cls");

	cout << "���θ޴�" << endl << endl;
	for (int i = 0; i < mainMenu.count; i++)
	{
		cout << mainMenu.keys.elementAt(i) << ". " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
	}

	String input;
	cout << endl << "����: ";
	cin >> input;

	return &input;
}

// �а� ��� �� ���� �Լ�
String Menu::DepartmentMenu()
{
	system("cls");

	cout << "�а�����" << endl << endl;
	for (int i = 0; i < departmentMenu.count; i++) 
	{
		cout << departmentMenu.keys.elementAt(i) << ". " << departmentMenu[departmentMenu.keys.elementAt(i)] << endl;
	}

	String input;
	cout << endl << "����: ";
	cin >> input;


	if (!departmentMenu.ContainKey(input.characters)) input = "";

	return input;
}
