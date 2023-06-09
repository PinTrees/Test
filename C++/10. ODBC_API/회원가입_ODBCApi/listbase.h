#pragma once
#include <iostream>
#include <cstdarg>
#include <functional>

/**
* �� Ŭ������ ��� ���ø� Ŭ������ �߻��� �������̽� Ŭ�����Դϴ�.
* 
* ��� Ŭ������ ���ϼ��� �ο��մϴ�.
* 
* �߻� ���� ����
* length
* 
* 
* �Լ�
* ForEach : ��� �ݺ����Դϴ�.
* Add	  : ��� �߰��� �Դϴ�.
* Remove  : ��� ������ �Դϴ�.
* Contain : ��� �˻��� �Դϴ�.
* Clear   : ����� ��� �����մϴ�.
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