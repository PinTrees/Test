#pragma once
#include <iostream>
#include "manager.h"
#include "list.h"
#include "global.h"
#include "string.h"
#include "list.h"

// 메뉴
// 성적 입력
// 성적 조회
// 성적 출력
// 종료
// 
// 
// 
// 
// 
// 성적 입력
// 학과선택
// 게이프로그래밍
// 게임기획
// 
// 이름 
// 학번
// 
// 과목 리스트 3과목
// 각각 출력
// 과목: 점수 입력
// 
// 
// 
// 
// 
// 
// 성적조회
// 학번 - 이름   
// 
// 이름으로 검색할 경우 동명이인 발생
// 리스트로 출력 필요
// 
// 
// 
// 
// 
// 성적 출력
// 1. 학과선택
// 2. 전체출력
// 
// 모든 성적 출력
// 학번 이름 과목 리스트 점수
// 
// 
//

 
int main()   
{
    Manager* manager = new Manager();
    manager->Init();
    manager->Run();

    //std::cout << "Hello World!\n";
}
