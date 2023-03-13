#pragma once
#include <iostream>
#include <stdlib.h>
#include "string.cpp";
#include "login.cpp";
#include "list.cpp"
#include "map.cpp"
#include "stringMap.cpp"



// String << ������ �������̵�
//  ���� �Լ��� �ִ� cpp ���Ͽ� �����ε� �ؾ����� Ȯ�� 
// 
// [����]
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=duehd88&logNo=20201487812
ostream& operator<<(ostream& cout, const String& ms) {
    if(ms.length > 0)
        cout << ms.characters; 
    return cout;
}

istream& operator>>(istream& cin, String& ms) {
    char* tmp = new char[10000];//�ް�
    cin >> tmp;
    ms = tmp;
    //cout << ms << endl;
    return cin;
}
  







int main()
{
    SMap<String> mainMenu;
    mainMenu["1"] = "ȸ������";
    mainMenu["2"] = "�α���";
    mainMenu["3"] = "����";
    mainMenu["4"] = "����";
    mainMenu["4"] = "����";

    Map<const char*, String> loginMenu;
    loginMenu["1"] = "�α׾ƿ�";
    loginMenu["2"] = "ȸ��Ż��";

    LoginManager loginManager;

    while (true)
    {
        String userInput;
    
        cout << "[ ���θ޴� ]\n" << endl;
        for (int i = 0; i < mainMenu.keys.count; i++) {
            cout << mainMenu.keys.elementAt(i) << ": " << mainMenu[mainMenu.keys.elementAt(i)] << endl;
        }
        cout << endl;


        cout << "����: ";
        cin >> userInput; 

        if (userInput == "1" || userInput == "ȸ������") {
            cout << "\n[ " << mainMenu["1"] << " �޴� ]" << endl << endl;
            loginManager.SignUp();
        }
        else if (userInput == "2" || userInput == "�α���") {
            cout << "\n[ " << mainMenu["2"] << " �޴� ]" << endl << endl;
          
            loginManager.Login();
        }
        return 0;
    }


    cout << "����: ";
    cout << "����: ";
    cout << "����: ";
    cout << "����: ";
    cout << "����: ";
    cout << "����: ";
    cout << "����: ";

    system("pause");
}
