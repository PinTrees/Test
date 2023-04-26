#pragma once
#include "string.h"
#include "stringMap.h"
#include "intmap.h"
#include "global.h"
#include "console.h"

// 주석 cpp 작성됨

class Menu 
{
public:
	Menu();
	~Menu();

	void Init();

	/** 이 함수는 메인메뉴를 출력하고 사용자의 입력값을 반환합니다. */
	String MainMenu();
	
	/** 이 함수는 상품출력메뉴를 출력하고 사용자의 입력값을 반환합니다. */
	String PrintMenu();

	/** 이 함수는 상품추가메뉴를 출력하고 사용자의 입력값을 반환합니다.*/
	String InputMenu();
};