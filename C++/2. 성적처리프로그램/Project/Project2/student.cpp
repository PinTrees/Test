#pragma once
#include "student.h"


Student::Student() 
{
	departmentType = nullptr;
}
Student::~Student() 
{
	SAFE_DELETE(departmentType);
}
Student::Student(String _name, String _uid, char* _type) 
{
	name = _name;
	uid = _uid;
	departmentType = _type;
}

// GET - SET
String Student::getUid() 
{ 
	return uid;
}
void Student::setUid(String _uid) 
{ 
	uid = _uid; 
}
char* Student::getDepartmentType()
{
	return departmentType;
}
void Student::setDepartmentType(char* _type)
{
	departmentType = _type;
}
String Student::getName()
{
	return name;
}
void Student::setName(String _name)
{
	name = _name;
}




Score::Score() {}
// 생성시 점수 할당
Score::Score(int _score)
{
	score = _score;
}
int Score::getScore()
{ 
	return score;
}




StudentScore::StudentScore() {}
StudentScore::~StudentScore()
{
	SAFE_ARRAY_DELETE(scores);
}
StudentScore::StudentScore(String name, String uid, char* type)
: Student(name, uid, type) {

}

// 추후 과목이 추가될 수 있으므로 과목 개수 반환 함수 추가
int StudentScore::getScoreCount()
{
	return ARRAY_LEN(scores);
}
// 점수 세팅
int StudentScore::getScore(int index) 
{
	return scores[index]->getScore();
}
void StudentScore::setScore(int index, int rank)
{
	scores[index] = new Score(rank);
}

// 점수 출력 함수
void StudentScore::PrintScore(Menu* menu)
{
	cout << "학번: " << getUid() << endl;
	cout << "이름: " << getName() << endl;
	cout << "학과: " << menu->departmentMenu[getDepartmentType()] << endl;

	for (int i = 0; i < getScoreCount(); i++) {
		cout << menu->classMenu[getDepartmentType()]->elementAt(i) << ": " << getScore(i) << ",\t";
	}

	cout << endl << endl;
}