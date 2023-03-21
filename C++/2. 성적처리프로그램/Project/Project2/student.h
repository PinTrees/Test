#pragma once
#include "global.h"
#include "string.h"
#include "list.h"
#include "menu.h"

// 학생의 기본 정보 저장 클래스
// 학번, 이름, 학과
class Student
{
public:
	Student();
	Student(String _name, String _uid, char* _type);
	~Student();

	String getUid();
	void setUid(String _uid);

	char* getDepartmentType();
	void setDepartmentType(char* _type);

	String getName();
	void setName(String _name);
private:
	String uid;
	String name;
	char* departmentType;
};

// 점수 저장 클래스
class Score {
public:
	Score();
	Score(int score);
	int getScore();

private:
    int score;
};

// 학생의 정보 및 점수 저장 상속 클래스
class StudentScore : public  Student {
public:
	StudentScore();
	StudentScore(String name, String uid, char* type);
	~StudentScore();

	int getScoreCount();
	int getScore(int index);
	void setScore(int index, int rank);
	void PrintScore(Menu* menu);

private:
	Score* scores[3];
};

