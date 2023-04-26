#pragma once
#include <iostream>
#include <cstdarg>
#include <functional>
#include "listbase.h"

using namespace std;

/**
* 이 클래스는 리스트의 노드입니다.
*/
template<typename T> struct CNode
{
	CNode* next = nullptr;
	CNode* prev = nullptr;
	T value;

	CNode(T _value)
	{
		value = _value;
	}
	CNode(T _value, CNode* _next, CNode* _prev)
	{
		value = _value;
		next = _next;
		prev = _prev;
	}
};


/**
* (***) 변경 예정
* 이 템플릿 클래스는 이중연결 리스트 입니다. 
* 
* 가변인자 생성 기능 추가
* 반복 제어함수 추가
*/
template<typename T>
class List : public ListBase<T>
{
public:
	CNode<T>* first;
	CNode<T>* last;
	int count;

public:
	List() : ListBase<T>()  { 
		first = NULL;
		last = NULL; 
		count = 0;
	}

	/**
	* 이 함수는 가변인자를 받아와 리스트를 초기화 합니다.
	* 
	* 가변인자 배열의 크기를 확인할 수 없으므로 생성시 크기값이 필요합니다.
	* 
	* 파라미터
	*	int size: 리스트를 생성할 크기입니다.
	*	T...:	  생성될 리스트 요소의 가변인자 목록입니다.
	* 
	* new List<int>(10, 1,1,1,1,1,1,1,1,1,1);
	*/
	List(int size, T...)
	{
		first = NULL;
		last = NULL;
		count = 0;

		// 가변인자의 포인터
		va_list list;	
		va_start(list, size); // list는 size의 다음 인자를 가리키게 됨, size의 메모리 크기 이후 부터 스타트

		for (int i = 0; i != size; ++i) {
			Add(va_arg(list, T));	// 지금 현재 가리키고 있는 포인터를 읽어옴과 동시에 T사이즈 만큼 포인터 이동 
			cout << size << endl;
		}

		va_end(list);
		count = size;
	}
	~List()
	{
		clear();
	}
	

	 
public:

	/**
	* 이 함수는 리스트에 요소를 추가합니다.
	* 
	* 파라미터
	*	T item: 추가할 요소입니다.
	* 
	* 반환
	*	int:	현재 리스트의 크기를 반환합니다.
	*/
	int Add(T item)
	{
		CNode<T>* newNode = new CNode<T>(item);
		if (count == 0)
		{
			first = newNode;
			last = newNode;
			newNode->next = NULL;
			newNode->prev = NULL;
		}
		else
		{
			newNode->next = NULL;
			newNode->prev = last;
			last->next = newNode;
			last = newNode;
		}
		++count;

		return count;
	}


	/**
	* 이 함수는 리스트에서 요소와 같은 값을 목록에서 제거합니다.
	*/
	int remove(T item)
	{
		CNode<T>* pThis = first;
		while (pThis)
		{
			if (pThis->value == item)
			{
				if (pThis->prev)
				{
					pThis->prev->next = pThis->next;
				}
				else
				{
					first = pThis->next;
				}
				if (pThis->next)
				{
					pThis->next->prev = pThis->prev;
				}
				else
				{
					last = pThis->prev;
				}
				delete pThis;
				--count;
				break;
			}
			pThis = pThis->next;
		}
		return count;
	}


	/**
	* 이 함수는 람다식을 목록을 순회하며 반복합니다.
	*/
	void ForEach(std::function<void(T)> fptr) override {
		CNode<T>* pThis = first;
		while (pThis)
		{
			(fptr)(pThis->value);
			pThis = pThis->next;
		}
	}


	/**
	* 이 함수는 리스트 내 특정 인덱스의 요소에 접근합니다.
	*/
	T elementAt(int index) {
		CNode<T>* node = nullptr;
		if (first == nullptr) return nullptr;

		if (index == 0) return first->value;

		node = first;
		for (int i = 0; i < index; i++)
		{
			if (node->next != nullptr) node = node->next;
			else return nullptr;
		}
		return node->value;
	}


	/**
	* 이 함수는 리스트 내 특정 인덱스에 접근합니다.
	*/
	T operator[] (int index) {
		CNode<T>* node = nullptr;
		if (first == nullptr) return nullptr;

		if (index == 0) return first->value;

		node = first;
		for (int i = 0; i < index; i++)
		{
			if (node->next != nullptr) node = node->next;
			else return nullptr;
		}
		return node->value;
	}


	/**
	* 이 함수는 리스트 내 모든 요소를 제거합니다.
	*/
	void clear()
	{
		CNode<T>* pThis = first;
		while (pThis)
		{
			CNode<T>* pDelete = pThis;

			if (pThis->prev)
				pThis->prev->next = pThis->next;
			if (pThis->next)
				pThis->next->prev = pThis->prev;

			pThis = pThis->next;

			delete pDelete;
			--count;
		}
		first = NULL;
		last = NULL;
	}

	/**
	* 이 함수는 리스트의 크기를 반환합니다.
	*/
	int getSize()
	{
		return count;
	}


	/**
	* 사용되지 않는 함수
	*/
	void printAll()
	{
		if (count > 0)
		{
			CNode<T>* pThis = first;
			while (pThis)
			{
				pThis = pThis->next;
			}
		}
	}
};



/**
* (**) 구현중
* 이 템플릿 클래스는 목록 수정이 불가능 하도록 설계될 클래스입니다.
*/
template<typename T> class Iterable
{
public:
	CNode<T>* first; 
	CNode<T>* last;  
	int count;

public:
	
	Iterable() : first(nullptr), last(nullptr), count(0)
	{
	}
	~Iterable()
	{
		clear();
	}

	void clear()
	{
		CNode<T>* pThis = first;
		while (pThis)
		{
			CNode<T>* pDelete = pThis;

			if (pThis->prev)
			{
				pThis->prev->next = pThis->next;
			}
			if (pThis->next)
			{
				pThis->next->prev = pThis->prev;
			}

			pThis = pThis->next;

			//cout << "delete list node: " << pDelete << endl;
			delete pDelete;
			--count;
		}
		first = nullptr;
		last = nullptr;
	}

	int Add(T item)
	{
		if (count == 0)
		{
			CNode<T>* newNode = new CNode<T>(item, nullptr, nullptr);
			first = newNode;
			last = newNode;
		}
		else
		{
			CNode<T>* newNode = new CNode<T>(item, nullptr, last);
			last->next = newNode;
			last = newNode;
		}
		++count;

		return count;
	}

	void ForEach(std::function<void(T)> fptr) {
		CNode<T>* pThis = first;
		while (pThis)
		{
			(fptr)(pThis->value);
			pThis = pThis->next;
		}
	}

	T elementAt(int index) {
		CNode<T>* node = nullptr;
		if (first == nullptr) return nullptr;

		if (index == 0) return first->value;

		node = first;
		for (int i = 0; i < index; i++)
		{
			if (node->next != nullptr) node = node->next;
			else return nullptr;
		}
		return node->value;
	}
	T operator[] (int index) {
		CNode<T>* node = nullptr;
		if (first == nullptr) return nullptr;

		if (index == 0) return first->value;

		node = first;
		for (int i = 0; i < index; i++)
		{
			if (node->next != nullptr) node = node->next;
			else return nullptr;
		}
		return node->value;
	}

	int remove(T item)
	{
		CNode<T>* pThis = first;
		while (pThis)
		{
			if (pThis->value == item)
			{
				if (pThis->prev)
				{
					pThis->prev->next = pThis->next;
				}
				else
				{
					first = pThis->next;
				}
				if (pThis->next)
				{
					pThis->next->prev = pThis->prev;
				}
				else
				{
					last = pThis->prev;
				}
				delete pThis;
				--count;
				break;
			}
			pThis = pThis->next;
		}
		return count;
	}
	void printAll()
	{
		if (count > 0)
		{
			CNode<T>* pThis = first;
			while (pThis)
			{
				//cout << pThis->value << endl;
				pThis = pThis->next;
			}
		}
	}
};