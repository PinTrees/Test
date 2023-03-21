#pragma once
#include "list.h"
#include "string.h"
#include "student.h"
#include "stringMap.h"
#include "menu.h"

class Manager 
{
	// �й��� Key�� ����ϴ� �л� ���� ���
	SMap<StudentScore*>* studentScores;
	Menu* menu;

public:
	Manager();
	~Manager();

	void Init();
	void Run();

	void PrintScore();
	void CreateScore();
	void SearchScore();
};