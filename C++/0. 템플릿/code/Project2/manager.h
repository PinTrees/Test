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


// �ּ� cpp �ۼ���

class MainManager 
{
	Menu*					menu;

public:
	MainManager();
	~MainManager();

	void Init();
	void Run();
	void Dispose();


	/** �� �Լ��� �� ��ǰ �Ŵ����� ��ǰ��� �Լ��� �����մϴ�.*/
	void PrintProduct();

	/** �� �Լ��� �� ��ǰ �Ŵ����� ��ǰ�߰� �Լ��� �����մϴ�. */
	void InputProduct();

	/** �� �Լ��� ��� �Ŵ����� ��ǰ�˻� �Լ��� �����մϴ�. */
	void SearchProduct();

	/** �� �Լ��� ��� �Ŵ����� ��ǰ���� �Լ��� �����մϴ�. */
	void SaveProduct();

	/** �� �Լ��� �Էµ� �ڵ忡 �ش��ϴ� ��ǰ�Ŵ����� ��ȯ�մϴ�. */
	IManager* GetProductManager(String code);
};