#pragma once
#include <iostream>

using namespace std;

// 기초 리스트
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

template<typename T> class List
{
public:
	CNode<T>* first;
	CNode<T>* last;
	int count;

public:
	List() : first(NULL), last(NULL), count(0)
	{
	}
	~List()
	{
		clear();
	}

public:
	int add(T item)
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

	int getSize()
	{
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


// Map 의 entry 구현을 위한 리스트 제어함수 제거 모델
template<typename T> class Iterable
{
public:
	CNode<T>* first; // 첫번째 노드
	CNode<T>* last;  // 마지막 노드
	int count;

public:
	// 기초 생성자 호출과 함꼐 초기화
	Iterable() : first(nullptr), last(nullptr), count(0)
	{
	}
	~Iterable()
	{
		clear();
	}

	// 리스트 클리어
	void clear()
	{
		// 현재 노드가 nullptr 일때 까지 순회하며 삭제
		CNode<T>* pThis = first;
		while (pThis)
		{
			CNode<T>* pDelete = pThis;

			// != nullptr
			// 1-2-3    /   2-3-4   /   3-4-5
			// 1-2-4    /   X-X-X   /   2-4-5
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

	// 직관적 신규 노드 추가
	int add(T item)
	{
		// 신규 노드 생성
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

	T elementAtIn(int index) {
		CNode<T>* node = nullptr;
		if (first == nullptr) return nullptr;

		if (index == 0) return first->value;

		node = first;
		for (int i = 0; i < index; i++)
		{
			if (node->next != nullptr) node = node->next;
			else return first->value;
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