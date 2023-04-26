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
* ForEach
* Add
* Remove
* Contain
* Clear
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