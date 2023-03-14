#pragma once
#include <iostream>
#include "string.cpp";
#include "list.cpp";
#include "map.cpp";
#include "stringMap.cpp"

using namespace std;

// ���� Ŭ����
class User 
{
private:
	//String uid;
	//String name;

public:
	String id;
	String password;

public:
	String getID()
	{
		return id;
	}
	String getPassword()
	{
		return password;
	}


public:

	User()
	{
	}
	User(String id, String password)
	{
		this->id = id;
		this->password = password;
	}
	// NULL ���� ���� ����
	// ���� ���� ��� �̶� �Ǵ�.
	User(const int) {
		id = String(NULL);
		password = String(NULL);
	}

	~User()
	{
	}




	// = ������ ���۷����͸� ���� ��ü ����;
	void operator=(User user) {
		id = user.id;
		password = user.password;
	}
};







// ���� ��� ���� ��ü
class UserList {

private:

	// ���Ե� ���� ���, Map<String, User> 
	// Key=���̵�, Value=��������
	// ���̵� Map�� Key�� ��������� �ߺ� ����
	// 
	// [�̱���]
	// ������ UID �߱��� ���� ���� ��ü ����ȭ �ʿ�
	SMap<User> users; 

public:
	
	void initTest() {
		users["111"] = User(String("111"), String("111"));
		users["222"] = User(String("222"), String("222"));
		users["333"] = User(String("333"), String("333"));
		users["444"] = User(String("444"), String("444"));
		users["555"] = User(String("555"), String("555"));
		users["666"] = User(String("666"), String("666"));
		users["777"] = User(String("777"), String("777"));
		users["888"] = User(String("888"), String("888"));
		users["999"] = User(String("999"), String("999"));

		users["11"] = User(String("11"), String("11"));
		users["22"] = User(String("22"), String("22"));
		users["33"] = User(String("33"), String("33"));
		users["44"] = User(String("44"), String("44"));
		users["55"] = User(String("55"), String("55"));
		users["66"] = User(String("66"), String("66"));
		users["77"] = User(String("77"), String("77"));
		users["88"] = User(String("88"), String("88"));
		users["99"] = User(String("99"), String("99"));
	}

	// ID ���� Ȯ�� �Լ�
	// �ʿ� ����� Key �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� true ��ȯ
	bool CompareID(String id) {
		return users.ContainKey(id.characters);
	}

	// ���� �н����� ���� Ȯ�� �Լ�
	// �ʿ� ����� User.password �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� true ��ȯ
	bool ComaprePassword(String id, String password) {
		return strcmp(users[id.characters].password.characters, password.characters) == 0;
	}

	// ���� ���� Ȯ�� �Լ�
	// �ʿ� ����� User.id / User.password �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� User ��ü ��ȯ
	User* CompareUser(String id, String password) {

		// ���̵� ���� Ȯ��
		// ���̵� �������� ���� ���
		// bool isIdCheck = CompareID(id);
		if (!CompareID(id))
		{
			cout << endl << "���̵� ã�� �� �����ϴ�." << endl;
			return nullptr;
		}

		// �н����� ���� Ȯ�� �Լ�
		// �н����尡 �������� ���� ���
		// bool isPasswordCheck = ComaprePassword(id.characters, password.characters);
		if (!ComaprePassword(id.characters, password.characters)) {
			cout << endl << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
			return nullptr;
		}

		// ID, Password ��� ������ ��� User ��ü�� ��ȯ
		return new User(id, password); //&users[id.characters];
	}

	// �ű� ���� ���� �Լ�
    bool CreateUser(User* user) {
		users[user->id.characters] = *user;
		return true;
	} 

	// ���� ���� �Լ�
	// �ʿ��� User.id �� �񱳰��� ��Ȯ�� ���� ��� ����
	// ��ȯ�� �� ����
	bool DeleteUser(User* user) {

		// ���� Key ���� ���� ����
		// �α��ν� �ű� User ��ü�� ���������� User ��ü�� �ּҰ��� ���� ���� �Ұ� ( remove by value );
		users.remove(user->id.characters);
		return true;
	}

};











// �α��� �ý��� 
//
// �α��� �Ŵ��� Ŭ����
// 
// [���]
// �α���
// �α׾ƿ�
// Ż��
class LoginManager {

public:

	// ���� ��� ��ü
	UserList userList;

	// ���� �α��� ���� ����
	User* currentUser;



	// ���θ޴� Map<String, String>
	SMap<String> mainMenu;
	// �α��� �޴� Map<String, String>
	SMap<String> loginMenu;


private:
	// �ý��� �Լ�
	// �α��� �ý���
	bool login(String id, String password)
	{
		//currentUser = userList.CompareUser(id, password);
		if (userList.CompareUser(id, password) == nullptr)
		{
			return false;
		}
	}

	// ȸ������ �ý���
	void signUp(String id, String password)
	{
		// �ű� User ��ü ����
		User* user = new User(id, password);

		// �ű����� �߰� �Լ� ȣ��
		// ���������� �߰��Ǿ��� ��쿡�� true ��ȯ
		// �ű����� �߰��� ���������� �Ϸ�Ǿ��� ���
		bool isCreate = userList.CreateUser(user);
		if (isCreate)
		{
			// ȸ������ �� �ٷ� �α���
			currentUser = user;
		}
	}

	// �α׾ƿ� �ý��� 
	bool logOut()
	{
		// ���� �α������� User ��ü ����
		if (currentUser != nullptr) delete currentUser;
		currentUser = nullptr;

		return true;
	}

	// ȸ��Ż�� �ý���
	bool deleteUser()
	{
		userList.DeleteUser(currentUser);
		if (currentUser != nullptr) delete currentUser;
		currentUser = nullptr;

		return true;
	}

public:
	LoginManager()
	{
		currentUser = nullptr;

		// ���θ޴� �߰�
		mainMenu["1"] = "ȸ������";
		mainMenu["2"] = "�α���";
		mainMenu["3"] = "����";

		// �α��� �޴� �߰�
		loginMenu["1"] = "�α׾ƿ�";
		loginMenu["2"] = "ȸ��Ż��";

		// �׽�Ʈ ���� ��� �ڵ�
		//userList.initTest();
	}
	~LoginManager()
	{

	}


	void main() 
	{
		// �α��� ���� ����
		while (true)
		{
			String userInput; // ����� ���� �Է°�

			// �α����� ������ �������
			// �α��� ȭ��
			if (currentUser != nullptr)
			{
				system("cls");
				LoginMenuUI(); // �α��� �޴� ���
				
				cout << endl << "����: ";
				cin >> userInput;

				system("cls");

				// �α׾ƿ� ���ý� �α׾ƿ� ���� ȣ��
				if (userInput == "1" || userInput == "�α׾ƿ�")
				{
					LogOutFunc();
				}
				// ȸ��Ż�� ���ý� ȸ��Ż�� ���� ȣ��
				else if (userInput == "2" || userInput == "ȸ��Ż��") 
				{
					DeleteUserFunc();
				}
			}

			// �α����� ������ ������� 
			// ����ȭ��
			else 
			{
				system("cls");
				MainManuUI(); // ���θ޴� UI ���
				 
				cout << endl << "����: ";
				cin >> userInput;

				system("cls");

				// ȸ������ ���ý� ȸ������ ���� ȣ��
				if (userInput == "1" || userInput == "ȸ������")
				{
					SinUpFunc();
				}
				// �α��� ���ý� �α��� ���� ȣ��
				else if (userInput == "2" || userInput == "�α���")
				{
					LoginFunc();
				}
				// ���� ���ý� While Ż��
				else if (userInput == "3" || userInput == "����") break;
				else continue;
			}
		} // while
	}





	// �α��� �޴� ��� �Լ�
	void LoginMenuUI()
	{
		cout << currentUser->id << " �� �ȳ��ϼ���." <<endl << endl;
		cout << "[ �α��� �޴� ]" << endl << endl;
		for (int i = 0; i < loginMenu.keys.count; i++)
		{
			// entry ����Ʈ ������ keys �� �����Ͽ� ������ Key �� ȹ�� ����
			// ȹ���� Key ���� �ش��ϴ� Value ���� �����ϴ� ���·� ����
			// ��ȿ������ ���� / �׷��� �� ��Ͽ� ���� ������ ���� �ۼ� �� Key �ݺ��� ���� Value ���ٿ� ����
			cout << loginMenu.keys.elementAt(i) << ": " << loginMenu[loginMenu.keys.elementAt(i)] << endl;
		}
	}

	// ���θ޴� ��� �Լ�
	void MainManuUI() 
	{
		cout << "[ ���θ޴� ]\n" << endl;
		// �ʿ� ����Ǿ��ִ� ����� �� ��ŭ �ݺ�
		for (int i = 0; i < mainMenu.keys.count; i++)
		{
			// entry ����Ʈ ������ keys �� �����Ͽ� ������ Key �� ȹ�� ����
			// ȹ���� Key ���� �ش��ϴ� Value ���� �����ϴ� ���·� ����
			// ��ȿ������ ���� / �׷��� �� ��Ͽ� ���� ������ ���� �ۼ� �� Key �ݺ��� ���� Value ���ٿ� ����
			cout << mainMenu.keys.elementAt(i) << ": " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
		}
	}



	// UI �� ��� ���� ---------------------------------------------------------------------------------------------------
	// �α��� UI ����
	void LoginFunc()
	{
		String userInput;
		
		while (true)
		{
			system("cls");
			cout << "[ " << mainMenu["2"] << " �޴� ]" << endl << endl;

			String idInput;
			String passwordInput;

			cout << "���̵� �Է�: ";
			cin >> idInput;

			cout << "�н����� �Է�: ";
			cin >> passwordInput;

			if (!login(idInput, passwordInput))
			{
				cout << endl << "�ٽ� �õ��Ͻðڽ��ϱ�? y/n: ";
				cin >> userInput;

				if (userInput == "y" || userInput == "Y") { }
				else break;
			}
			else break;
		} 
	}

	// ȸ������ UI ����
	void SinUpFunc() 
	{
		cout << "[ " << mainMenu["1"] << " �޴� ]" << endl << endl;

		// String input 
		// ������ �Է� ��ü�� ���� ID / Password �� ������ �Է¹޴� ���·� ����
		String idInput;
		String passwordInput;

		// ���̵� �ߺ��� �߻��� �� �����ʷ� While �� ���
		while (true)
		{
			cout << "���̵� �Է�: ";
			cin >> idInput;

			// ���̵� ���� �˻� ���� �߰�

			// ������Ͽ� ����� ID ���� �Է°��� ������ ��
			// ID �� �̹� ������ ���
			// 
			// bool isIdExist = userList.CompareID(idInput);
			if (userList.CompareID(idInput))
			{
				cout << "�̹� ������� ���̵� �Դϴ�." << endl;
			}
			// �������� ���� ��� While Ż��
			else break;
		} // While

		cout << "�н����� �Է�: ";
		cin >> passwordInput;

		// �н����� ���� �˻� ���� �߰�

		signUp(idInput, passwordInput);
	}

	// �α׾ƿ� UI ����
	void LogOutFunc() {
		cout << "[ " << mainMenu["1"] << " �޴� ]" << endl << endl;

		String input;

		cout << "�α׾ƿ� �Ͻðڽ��ϱ�? y/n: ";
		cin >> input;

		// �α׾ƿ� ����
		if (input == "y" || input == "Y")
		{
			logOut();
		}
	}

	// ȸ��Ż�� UI ����
	void DeleteUserFunc()
	{
		cout << "[ " << mainMenu["2"] << " �޴� ]" << endl << endl;

		String input;

		cout << "ȸ��Ż�� �Ͻðڽ��ϱ�? y/n: ";
		cin >> input;

		// ȸ��Ż�� ����
		if (input == "y" || input == "Y")
		{
			deleteUser();
		}
	}
	// UI �� ��� ���� ---------------------------------------------------------------------------------------------------
};