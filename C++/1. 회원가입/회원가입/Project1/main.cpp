#pragma once
#include <iostream>
#include <stdlib.h>
#include "login.h"
#include "list.h"
#include "map.cpp"
#include "stringMap.h"
#include "string.h";



// String << 연산자 오버라이딩
//  메인 함수가 있는 cpp 파일에 오버로딩 해야함을 확인 
// 
// [참조]
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=duehd88&logNo=20201487812
ostream& operator<<(ostream& cout, const String& ms)  
{
    if(ms.length > 0) cout << ms.characters; 
    return cout;
}

istream& operator>>(istream& cin, String& ms)
{
    char* tmp = new char[10000];
    cin >> tmp; 
    ms = tmp; 
    return cin; 
}
    
 
 


 
int main()
{     
    LoginManager* loginManager = new LoginManager();
     
    loginManager->main();    
       
    delete loginManager;     

    system("pause");
} 
  