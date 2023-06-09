#pragma once
#include <iostream>
#include <cstdarg>
#include <functional>

/**
* 이 클래스는 목록 템플릿 클래스의 추상구현 인터페이스 클래스입니다.
* 
* 목록 클래스의 통일성을 부여합니다.
* 
* 추상 구현 변수
* length
* 
* 
* 함수
* ForEach : 요소 반복자입니다.
* Add	  : 요소 추가자 입니다.
* Remove  : 요소 제거자 입니다.
* Contain : 요소 검사자 입니다.
* Clear   : 목록을 모두 제거합니다.
* 
*/
template<typename T>
class ListBase {
public:
	T		first;
	T		last;

	bool	isEmpty;
	bool	isNotEmpty;
	 
	int		___length;

	ListBase() {
		first = NULL;
		last = NULL;

		isEmpty = false;
		isNotEmpty = false;

		___length = 0;
	}
	~ListBase() {

	}

	virtual void ForEach(std::function<void(T)> fptr) = 0;
};