#pragma once
#include "list.h"
#include "string.h"
#include "student.h"
#include "stringMap.h"
#include "menu.h"

class Manager 
{
	// 학번을 Key로 사용하는 학생 점수 목록
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