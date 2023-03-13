#pragma once
#include <iostream>
#include <stdlib.h>
#include "string.cpp";
#include "login.cpp";
#include "list.cpp"
#include "map.cpp"
#include "stringMap.cpp"



// String << 연산자 오버라이딩
//  메인 함수가 있는 cpp 파일에 오버로딩 해야함을 확인 
// 
// [참조]
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=duehd88&logNo=20201487812
ostream& operator<<(ostream& cout, const String& ms) {
    if(ms.length > 0)
        cout << ms.characters; 
    return cout;
}

istream& operator>>(istream& cin, String& ms) {
    char* tmp = new char[10000];//받고
    cin >> tmp;
    ms = tmp;
    //cout << ms << endl;
    return cin;
}
  







int main()
{
    SMap<String> mainMenu;
    mainMenu["1"] = "회원가입";
    mainMenu["2"] = "로그인";
    mainMenu["3"] = "종료";
    mainMenu["4"] = "종료";
    mainMenu["4"] = "종료";

    Map<const char*, String> loginMenu;
    loginMenu["1"] = "로그아웃";
    loginMenu["2"] = "회원탈퇴";

    LoginManager loginManager;

    while (true)
    {
        String userInput;
    
        cout << "[ 메인메뉴 ]\n" << endl;
        for (int i = 0; i < mainMenu.keys.count; i++) {
            cout << mainMenu.keys.elementAt(i) << ": " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
        }
        cout << endl;


        cout << "선택: ";
        cin >> userInput; 

        if (userInput == "1" || userInput == "회원가입") {
            cout << "\n[ " << mainMenu["1"] << " 메뉴 ]" << endl << endl;
            loginManager.SignUp();
        }
        else if (userInput == "2" || userInput == "로그인") {
            cout << "\n[ " << mainMenu["2"] << " 메뉴 ]" << endl << endl;
          
            loginManager.Login();
        }
        return 0;
    }


    cout << "선택: ";
    cout << "선택: ";
    cout << "선택: ";
    cout << "선택: ";
    cout << "선택: ";
    cout << "선택: ";
    cout << "선택: ";

    system("pause");
}
