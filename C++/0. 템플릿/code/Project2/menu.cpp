#include "menu.h"

Menu::Menu() {  }
Menu::~Menu() {  }


void Menu::Init() {
}


/**
* �� �Լ��� ���θ޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�.
*/
String Menu::MainMenu()
{
	system("cls");

	cout << "���θ޴�" << endl << endl;
	cout << "1. ��ǰ �߰�" << endl;
	cout << "2. ��ǰ ���" << endl;
	cout << "3. ��ǰ �˻�" << endl;
	cout << "4. ��ǰ ����" << endl;
	cout << "5. ����" << endl << endl;

	String input = ConsoleReadLine("����");
	return input;
}


/**
* �� �Լ��� ��ǰ��¸޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�.
*
* ������� �Է°��� ���� ���� ������ �˻� �� ������ ��� ���
* ����ȭ���� �ٽ� ����մϴ�.
*
* ��ȯ
*	String: ������� �Է°��� ��ȯ�մϴ�.
*/
String Menu::PrintMenu()
{
	while (true)
	{
		system("cls");

		cout << "��� �޴�" << endl << endl;
		cout << "1. ��ǰ ���" << endl;
		cout << "2. �Ƿ� ��� " << endl;
		cout << "3. ���� ���" << endl << endl;

		String input = ConsoleReadLine("����");
		if (ToInt(input) <= 3)
			return input;
	}
	return "";
}


/**
* �� �Լ��� ��ǰ�߰��޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�.
*
* ������� �Է°��� ���� ���� ������ �˻� �� ������ ��� ���
* ����ȭ���� �ٽ� ����մϴ�.
*
* ��ȯ
*	String ������� �Է°��� ��ȯ�մϴ�.
*/
String Menu::InputMenu()
{
	while (true)
	{
		system("cls");

		cout << "��ǰ �߰� ��� ����" << endl << endl;
		cout << "1. ��ǰ �߰�" << endl;
		cout << "2. �Ƿ� �߰� " << endl;
		cout << "3. ���� �߰�" << endl << endl;

		String input = ConsoleReadLine("����");

		if (ToInt(input) <= 3)
			return input;
	}
	return "";
}