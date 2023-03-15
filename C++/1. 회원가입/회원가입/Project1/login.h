#pragma once
#include <iostream>
#include "string.h";
#include "list.h";
#include "map.cpp";
#include "stringMap.h"

using namespace std;

// ���� Ŭ����
class User
{
private:

public:
	String id;
	String password;

public:
	String getID();
	String getPassword();

public:

	User();
	User(String id, String password);
	User(const int);
	~User();




	void operator=(User user);
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
	void initTest();
	// ID ���� Ȯ�� �Լ�
	// �ʿ� ����� Key �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� true ��ȯ
	bool CompareID(String id);

	// ���� �н����� ���� Ȯ�� �Լ�
	// �ʿ� ����� User.password �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� true ��ȯ
	bool ComaprePassword(String id, String password);

	// ���� ���� Ȯ�� �Լ�
	// �ʿ� ����� User.id / User.password �� �񱳰��� ��Ȯ�� ��ġ�� ��쿡�� User ��ü ��ȯ
	User* CompareUser(String id, String password);
	// �ű� ���� ���� �Լ�
	bool CreateUser(User* user);

	// ���� ���� �Լ�
	// �ʿ��� User.id �� �񱳰��� ��Ȯ�� ���� ��� ����
	// ��ȯ�� �� ����
	bool DeleteUser(User* user);
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
	bool login(String id, String password);
	// ȸ������ �ý���
	void signUp(String id, String password);
	// �α׾ƿ� �ý��� 
	bool logOut();

	// ȸ��Ż�� �ý���
	bool deleteUser();

public:
	LoginManager();
	~LoginManager();


	void main();

	// �α��� �޴� ��� �Լ�
	void LoginMenuUI();
	// ���θ޴� ��� �Լ�
	void MainManuUI();



	// UI �� ��� ���� ---------------------------------------------------------------------------------------------------
	// �α��� UI ����
	void LoginFunc();
	// ȸ������ UI ����
	void SinUpFunc();
	// �α׾ƿ� UI ����
	void LogOutFunc();
	// ȸ��Ż�� UI ����
	void DeleteUserFunc();
	// UI �� ��� ���� ---------------------------------------------------------------------------------------------------
};