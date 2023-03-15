#pragma once
#include <iostream>
#include "string.h";
#include "list.h";
#include "map.cpp";
#include "stringMap.h"
#include "login.h"

using namespace std;

User::User()
{
}
User::User(String id, String password)
{
	this->id = id;
	this->password = password;
}
User::User(const int) {
	id = String(NULL);
	password = String(NULL);
}
User::~User()
{
}


String User::getID()
{
	return id;
}
String User::getPassword()
{
	return password;
}


void User::operator=(User user) {
	id = user.id;
	password = user.password;
}





void UserList::initTest() 
{
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

// ID 존재 확인 함수
// 맵에 저장된 Key 와 비교값이 정확히 일치할 경우에만 true 반환
bool UserList::CompareID(String id) {
	return users.ContainKey(id.characters);
}

// 유저 패스워드 존재 확인 함수
// 맵에 저장된 User.password 와 비교값이 정확히 일치할 경우에만 true 반환
bool UserList::ComaprePassword(String id, String password) {
	return strcmp(users[id.characters].password.characters, password.characters) == 0;
}

// 유저 존재 확인 함수
	// 맵에 저장된 User.id / User.password 와 비교값이 정확히 일치할 경우에만 User 객체 반환
User* UserList::CompareUser(String id, String password) {

	// 아이디 존재 확인
	// 아이디가 존재하지 않을 경우
	// bool isIdCheck = CompareID(id);
	if (!CompareID(id))
	{
		cout << endl << "아이디를 찾을 수 없습니다." << endl;
		return nullptr;
	}

	// 패스워드 존재 확인 함수
	// 패스워드가 존재하지 않을 경우
	// bool isPasswordCheck = ComaprePassword(id.characters, password.characters);
	if (!ComaprePassword(id.characters, password.characters)) {
		cout << endl << "비밀번호가 일치하지 않습니다." << endl;
		return nullptr;
	}

	// ID, Password 모두 존재할 경우 User 객체를 반환
	return new User(id, password); //&users[id.characters];
}

// 신규 유저 생성 함수
bool UserList::CreateUser(User* user) {
	users[user->id.characters] = *user;
	return true;
}

bool UserList::DeleteUser(User* user) {

	// 맵의 Key 값을 통한 삭제
	// 로그인시 신규 User 객체가 생성됨으로 User 객체의 주소값을 통한 삭제 불가 ( remove by value );
	users.remove(user->id.characters);
	return true;
}













// 로그인 시스템 
//
// 로그인 매니저 클래스
// 
// [기능]
// 로그인
// 로그아웃
// 탈퇴


LoginManager::LoginManager()
{
	currentUser = nullptr;

	// 메인메뉴 추가
	mainMenu["1"] = "회원가입";
	mainMenu["2"] = "로그인";
	mainMenu["3"] = "종료";

	// 로그인 메뉴 추가
	loginMenu["1"] = "로그아웃";
	loginMenu["2"] = "회원탈퇴";

	// 테스트 유저 목록 코드
	userList.initTest();
}
LoginManager::~LoginManager()
{

}


	// 시스템 함수
	// 로그인 시스템
bool LoginManager::login(String id, String password)
{
	currentUser = userList.CompareUser(id, password);
	if (userList.CompareUser(id, password) == nullptr)
	{
		return false;
	}
}
// 회원가입 시스템
void LoginManager::signUp(String id, String password)
{
	// 신규 User 객체 생성
	User* user = new User(id, password);

	// 신규유저 추가 함수 호출
	// 성공적으로 추가되었을 경우에만 true 반환
	// 신규유저 추가가 성공적으로 완료되었을 경우
	bool isCreate = userList.CreateUser(user);
	if (isCreate)
	{
		// 회원가입 후 바로 로그인
		currentUser = user;
	}
}
// 로그아웃 시스템 
bool LoginManager::logOut()
{
	// 현재 로그인중인 User 객체 해제
	if (currentUser != nullptr) delete currentUser;
	currentUser = nullptr;

	return true;

}

// 회원탈퇴 시스템
bool LoginManager::deleteUser()
{
	userList.DeleteUser(currentUser);
	if (currentUser != nullptr) delete currentUser;
	currentUser = nullptr;

	return true;
}



void LoginManager::main()
{
	// 로그인 메인 로직
	while (true)
	{
		String userInput; // 사용자 선택 입력값

		// 로그인한 유저가 있을경우
		// 로그인 화면
		if (currentUser != nullptr)
		{
			system("cls");
			LoginMenuUI(); // 로그인 메뉴 출력

			cout << endl << "선택: ";
			cin >> userInput;

			system("cls");

			// 로그아웃 선택시 로그아웃 로직 호출
			if (userInput == "1" || userInput == "로그아웃")
			{
				LogOutFunc();
			}
			// 회원탈퇴 선택시 회원탈퇴 로직 호출
			else if (userInput == "2" || userInput == "회원탈퇴")
			{
				DeleteUserFunc();
			}
		}

		// 로그인한 유저가 없을경우 
		// 메인화면
		else
		{
			system("cls");
			MainManuUI(); // 메인메뉴 UI 출력

			cout << endl << "선택: ";
			cin >> userInput;

			system("cls");

			// 회원가입 선택시 회원가입 로직 호출
			if (userInput == "1" || userInput == "회원가입")
			{
				SinUpFunc();
			}
			// 로그인 선택시 로그인 로직 호출
			else if (userInput == "2" || userInput == "로그인")
			{
				LoginFunc();
			}
			// 종료 선택시 While 탈출
			else if (userInput == "3" || userInput == "종료") break;
			else continue;
		}
	} // while
}


// 로그인 메뉴 출력 함수
void LoginManager::LoginMenuUI()
{
	cout << currentUser->id << " 님 안녕하세요." << endl << endl;
	cout << "[ 로그인 메뉴 ]" << endl << endl;
	for (int i = 0; i < loginMenu.keys.count; i++)
	{
		// entry 리스트 형태의 keys 에 접근하여 순차적 Key 값 획득 가능
		// 획득한 Key 값에 해당하는 Value 값에 접근하는 형태로 구현
		// 비효울적인 로직 / 그러나 맵 목록에 대한 순차적 로직 작성 및 Key 반복을 통한 Value 접근에 용이
		cout << loginMenu.keys.elementAt(i) << ": " << loginMenu[loginMenu.keys.elementAt(i)] << endl;
	}
}

// 메인메뉴 출력 함수
void LoginManager::MainManuUI()
{
	cout << "[ 메인메뉴 ]\n" << endl;
	// 맵에 저장되어있는 목록의 수 많큼 반복
	for (int i = 0; i < mainMenu.keys.count; i++)
	{
		// entry 리스트 형태의 keys 에 접근하여 순차적 Key 값 획득 가능
		// 획득한 Key 값에 해당하는 Value 값에 접근하는 형태로 구현
		// 비효울적인 로직 / 그러나 맵 목록에 대한 순차적 로직 작성 및 Key 반복을 통한 Value 접근에 용이
		cout << mainMenu.keys.elementAt(i) << ": " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
	}
}



// UI 및 기능 로직 ---------------------------------------------------------------------------------------------------
// 로그인 UI 로직
void LoginManager::LoginFunc()
{
	String userInput;

	while (true)
	{
		system("cls");
		cout << "[ " << mainMenu["2"] << " 메뉴 ]" << endl << endl;

		String idInput;
		String passwordInput;

		cout << "아이디 입력: ";
		cin >> idInput;

		cout << "패스워드 입력: ";
		cin >> passwordInput;

		if (!login(idInput, passwordInput))
		{
			cout << endl << "다시 시도하시겠습니까? y/n: ";
			cin >> userInput;

			if (userInput == "y" || userInput == "Y") {}
			else break;
		}
		else break;
	}
}

// 회원가입 UI 로직
void LoginManager::SinUpFunc()
{
	cout << "[ " << mainMenu["1"] << " 메뉴 ]" << endl << endl;

	// String input 
	// 각각의 입력 객체를 통해 ID / Password 를 나눠서 입력받는 형태로 구현
	String idInput;
	String passwordInput;

	// 아이디 중복이 발생할 수 있으믐로 While 을 사용
	while (true)
	{
		cout << "아이디 입력: ";
		cin >> idInput;

		// 아이디 형식 검사 로직 추가

		// 유저목록에 저장된 ID 값과 입력값이 같은지 비교
		// ID 가 이미 존재할 경우
		// 
		// bool isIdExist = userList.CompareID(idInput);
		if (userList.CompareID(idInput))
		{
			cout << "이미 사용중인 아이디 입니다." << endl;
		}
		// 존재하지 않을 경우 While 탈출
		else break;
	} // While

	cout << "패스워드 입력: ";
	cin >> passwordInput;

	// 패스워드 형시 검사 로직 추가

	signUp(idInput, passwordInput);
}

// 로그아웃 UI 로직
void LoginManager::LogOutFunc() {
	cout << "[ " << mainMenu["1"] << " 메뉴 ]" << endl << endl;

	String input;

	cout << "로그아웃 하시겠습니까? y/n: ";
	cin >> input;

	// 로그아웃 선택
	if (input == "y" || input == "Y")
	{
		logOut();
	}
}

// 회원탈퇴 UI 로직
void LoginManager::DeleteUserFunc()
{
	cout << "[ " << mainMenu["2"] << " 메뉴 ]" << endl << endl;

	String input;

	cout << "회원탈퇴 하시겠습니까? y/n: ";
	cin >> input;

	// 회원탈퇴 선택
	if (input == "y" || input == "Y")
	{
		deleteUser();
	}
}