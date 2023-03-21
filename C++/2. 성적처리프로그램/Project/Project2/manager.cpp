#include "manager.h"

Manager::Manager() {
}
Manager::~Manager() {
	studentScores->clear();
	delete menu;
}

// ����ó�����α׷� �Ŵ��� Ŭ���� ����
void Manager::Init() {
	studentScores = new SMap<StudentScore*>();
	menu = new Menu();
	menu->Init();
}

// ����
void Manager::Run() {
	while (true)
	{
		// ���� �޴� ����
		String* select = menu->MainMenu();

		if (*select == "1")
		{
			CreateScore();
		}
		else if (*select == "2") 
		{
			SearchScore();
		}
		else if (*select == "3")
		{
			PrintScore();
		}
		else if (*select == "4") 
		{
			break;
		}
	}

	return;
}

// ��ü ���� ��� �Լ�
// ����� ��� ������ ����մϴ�.
void Manager::PrintScore() { 

	if (studentScores->count <= 0)
	{
		cout << "����� ������ �����ϴ�." << endl;
	}
	else {
		system("cls");
		cout << "�л� ���� ���" << endl << endl;

		for (int i = 0; i < studentScores->count; i++)
		{
			// ���� ���� ��Ͽ��� Key ���� ���� �� ȹ��
			StudentScore* student = studentScores->GetValueByKey(studentScores->keys.elementAt(i));
			student->PrintScore(menu);
		}
	}

	system("PAUSE");
}

// ���� �ű� �߰� ����
void Manager::CreateScore() {
	while (true)
	{
		// �а� �޴� ����
		String departmentType = menu->DepartmentMenu();

		// �߸��� �а� ���ý� �� ���ڿ� ��ȯ - ����ó���� ���п� DepartmentMenu() ���ο� �����ϱ⿣ �δ�
		if (strcmp(departmentType.characters, "") == 0)
		{
			cout << "�а��� �ٽ� ������ �ּ���." << endl;
			continue;
		}

		// �ش� �а��� �������� �ε�
		List<String>* subjects = menu->classMenu[departmentType.characters];


		system("cls");
		cout << "�л����� �Է�" << endl << endl;

		String inputName, inputUid, inputScore;

		while (true)
		{
			cout << "�й�: ";
			cin >> inputUid;

			// �Էµ� �й��� ���� �ߺ� �˻�
			if (studentScores->ContainKey(inputUid.characters))
			{
				cout << "�̹� ������� �й�. �ٽ� �Է�" << endl;
				inputUid = "";
				continue;
			}
			else break;
		}

		cout << "�̸�: ";
		cin >> inputName;

		// �Է¹��� ���� ���� �ű� �л����� Ŭ���� ����
		// ���� ���� ���� �Է� ���� ��, �������� �����ϴ� ���°� �� ������ ���ٰ� ����
		StudentScore* student = new StudentScore(inputName, inputUid, departmentType.characters);

		cout << endl << "�л����� �Է�" << endl << endl;

		for (int i = 0; i < subjects->count; i++) 
		{
			cout << subjects->elementAt(i) << ": ";
			cin >> inputScore;

			// ���� �����˻� �߰� ���� �ʿ�
			
			student->setScore(i, atoi(inputScore.characters));
		}

		// ������ �ű� ���� �߰�
		studentScores->add(student->getUid().characters, student);
		break;
	}
}


// ���� �˻� ����
// �Է��� �й��� ��ġ�ϴ� ������ ��� - ��µǴ� ������ �׻� 1��
void Manager::SearchScore() {
	system("cls");
	cout << "�л����� �˻�" << endl << endl;

	String input;

	cout << "�й� �Է�: ";
	cin >> input;

	// ����� ������Ͽ� �Է°��� �ִ��� Ȯ�� 
	if (!studentScores->ContainKey(input.characters)) {
		cout << "�й��� ã�� �� �����ϴ�.";
	}
	else 
	{
		system("cls");
		cout << "�л� ���� ��ȸ ���" << endl << endl;

		// �ش� ���� ���
		StudentScore* student = studentScores->GetValueByKey(input.characters);
		student->PrintScore(menu);
	}

	system("PAUSE");
}


