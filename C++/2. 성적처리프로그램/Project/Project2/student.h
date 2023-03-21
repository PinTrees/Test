#pragma once
#include "global.h"
#include "string.h"
#include "list.h"
#include "menu.h"

// �л��� �⺻ ���� ���� Ŭ����
// �й�, �̸�, �а�
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

// ���� ���� Ŭ����
class Score {
public:
	Score();
	Score(int score);
	int getScore();

private:
    int score;
};

// �л��� ���� �� ���� ���� ��� Ŭ����
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

