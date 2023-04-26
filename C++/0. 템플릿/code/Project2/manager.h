	#pragma once
#include "list.h"
#include "string.h"
#include "product.h"
#include "stringMap.h"
#include "menu.h"
#include "fileManager.h"

#include "goodsManager.h"
#include "clothesManager.h"
#include "electronicManager.h"
#include "console.h"


// 주석 cpp 작성됨

class MainManager 
{
	Menu*					menu;

public:
	MainManager();
	~MainManager();

	void Init();
	void Run();
	void Dispose();


	/** 이 함수는 각 상품 매니저의 상품출력 함수를 연결합니다.*/
	void PrintProduct();

	/** 이 함수는 각 상품 매니저의 상품추가 함수를 연결합니다. */
	void InputProduct();

	/** 이 함수는 모든 매니저의 상품검색 함수를 연결합니다. */
	void SearchProduct();

	/** 이 함수는 모든 매니저의 상품저장 함수를 연결합니다. */
	void SaveProduct();

	/** 이 함수는 입력된 코드에 해당하는 상품매니저를 반환합니다. */
	IManager* GetProductManager(String code);
};