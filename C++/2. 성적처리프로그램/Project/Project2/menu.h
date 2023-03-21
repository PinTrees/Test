#pragma once
#include "string.h"
#include "stringMap.h"

class Menu 
{

public:
	SMap<String> mainMenu;
	SMap<String> departmentMenu;
	SMap<List<String>*> classMenu;

public:
	Menu();
	~Menu();
	void Init();

	String* MainMenu();
	String DepartmentMenu();
	//String* ClassMenu(String* subjectId);
};