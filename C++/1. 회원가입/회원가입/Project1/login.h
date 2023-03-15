#pragma once
#include <iostream>
#include "string.h";
#include "list.h";
#include "map.cpp";
#include "stringMap.h"

using namespace std;

// 유저 클래스
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







// 유저 목록 관리 객체
class UserList {

private:

	// 가입된 유저 목록, Map<String, User> 
	// Key=아이디, Value=유저정보
	// 아이디를 Map의 Key로 사용함으로 중복 방지
	// 
	// [미구현]
	// 고유의 UID 발급을 통한 유저 객체 고유화 필요
	SMap<User> users;

public:
	void initTest();
	// ID 존재 확인 함수
	// 맵에 저장된 Key 와 비교값이 정확히 일치할 경우에만 true 반환
	bool CompareID(String id);

	// 유저 패스워드 존재 확인 함수
	// 맵에 저장된 User.password 와 비교값이 정확히 일치할 경우에만 true 반환
	bool ComaprePassword(String id, String password);

	// 유저 존재 확인 함수
	// 맵에 저장된 User.id / User.password 와 비교값이 정확히 일치할 경우에만 User 객체 반환
	User* CompareUser(String id, String password);
	// 신규 유저 생성 함수
	bool CreateUser(User* user);

	// 유저 삭제 함수
	// 맵에서 User.id 와 비교값이 정확히 같을 경우 삭제
	// 반환값 미 지정
	bool DeleteUser(User* user);
};











// 로그인 시스템 
//
// 로그인 매니저 클래스
// 
// [기능]
// 로그인
// 로그아웃
// 탈퇴
class LoginManager {

public:

	// 유저 목록 객체
	UserList userList;
	// 현재 로그인 중인 유저
	User* currentUser;
	// 메인메뉴 Map<String, String>
	SMap<String> mainMenu;
	// 로그인 메뉴 Map<String, String>
	SMap<String> loginMenu;


private:
	// 시스템 함수
	// 로그인 시스템
	bool login(String id, String password);
	// 회원가입 시스템
	void signUp(String id, String password);
	// 로그아웃 시스템 
	bool logOut();

	// 회원탈퇴 시스템
	bool deleteUser();

public:
	LoginManager();
	~LoginManager();


	void main();

	// 로그인 메뉴 출력 함수
	void LoginMenuUI();
	// 메인메뉴 출력 함수
	void MainManuUI();



	// UI 및 기능 로직 ---------------------------------------------------------------------------------------------------
	// 로그인 UI 로직
	void LoginFunc();
	// 회원가입 UI 로직
	void SinUpFunc();
	// 로그아웃 UI 로직
	void LogOutFunc();
	// 회원탈퇴 UI 로직
	void DeleteUserFunc();
	// UI 및 기능 로직 ---------------------------------------------------------------------------------------------------
};