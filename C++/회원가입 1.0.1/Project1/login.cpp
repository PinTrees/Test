#pragma once
#include <iostream>
#include "string.cpp";
#include "list.cpp";
#include "map.cpp";
#include "stringMap.cpp"

using namespace std;

class User {

private:
	//String uid;
	String password;
	String name;

public:
	String id;

public:
	String getID()
	{
		return id;
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
	~User()
	{
	}

	// NULL ����
	User(const int) {
		id = String(NULL);
	}

	bool SetId() {

	}

	void operator=(User user) {
		id = user.id;
	}
};


class UserList {

private:
	SMap<User> users; 

public:
	bool CompareID(String id) {
		return users.ContainKey(id.characters);
	}

    void CreateUser(User user) {
		users[user.id.characters] = user;
		cout << user.id << "�� ȸ�������� �Ϸ�Ǿ����ϴ�" << endl;
	} 
};

class LoginManager {

public:
	UserList userList;
	User currentUser;

private:


public:
	LoginManager()
	{

	}
	~LoginManager()
	{

	}

	User* Login() {

		return nullptr;
	}
	void SignUp() {
		String idInput;
		String passwordInput;
		User user;

		cout << "���̵� �Է�: ";
		cin >> idInput;
		bool idDuplicate = userList.CompareID(idInput);

		if (idDuplicate)
		{
			cout << "���̵� �ߺ���" << endl;
			SignUp();
		}

		cout << "�н����� �Է�: ";
		cin >> passwordInput;

		/// �н����� �˻� �ʿ�

		user = User(idInput, passwordInput);
		userList.CreateUser(user);
	}
	void LogOut() {

	}
	void Delete() {

	}
};