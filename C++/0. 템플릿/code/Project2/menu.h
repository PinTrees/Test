#pragma once
#include "string.h"
#include "stringMap.h"
#include "intmap.h"
#include "global.h"
#include "console.h"

// �ּ� cpp �ۼ���

class Menu 
{
public:
	Menu();
	~Menu();

	void Init();

	/** �� �Լ��� ���θ޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�. */
	String MainMenu();
	
	/** �� �Լ��� ��ǰ��¸޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�. */
	String PrintMenu();

	/** �� �Լ��� ��ǰ�߰��޴��� ����ϰ� ������� �Է°��� ��ȯ�մϴ�.*/
	String InputMenu();
};