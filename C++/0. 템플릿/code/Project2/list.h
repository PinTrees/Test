#pragma once
#include <iostream>
#include <cstdarg>
#include <functional>
#include "listbase.h"

using namespace std;

/**
* �� Ŭ������ ����Ʈ�� ����Դϴ�.
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
* (***) ���� ����
* �� ���ø� Ŭ������ ���߿��� ����Ʈ �Դϴ�. 
* 
* �������� ���� ��� �߰�
* �ݺ� �����Լ� �߰�
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
	* �� �Լ��� �������ڸ� �޾ƿ� ����Ʈ�� �ʱ�ȭ �մϴ�.
	* 
	* �������� �迭�� ũ�⸦ Ȯ���� �� �����Ƿ� ������ ũ�Ⱚ�� �ʿ��մϴ�.
	* 
	* �Ķ����
	*	int size: ����Ʈ�� ������ ũ���Դϴ�.
	*	T...:	  ������ ����Ʈ ����� �������� ����Դϴ�.
	* 
	* new List<int>(10, 1,1,1,1,1,1,1,1,1,1);
	*/
	List(int size, T...)
	{
		first = NULL;
		last = NULL;
		count = 0;

		// ���������� ������
		va_list list;	
		va_start(list, size); // list�� size�� ���� ���ڸ� ����Ű�� ��, size�� �޸� ũ�� ���� ���� ��ŸƮ

		for (int i = 0; i != size; ++i) {
			Add(va_arg(list, T));	// ���� ���� ����Ű�� �ִ� �����͸� �о�Ȱ� ���ÿ� T������ ��ŭ ������ �̵� 
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
	* �� �Լ��� ����Ʈ�� ��Ҹ� �߰��մϴ�.
	* 
	* �Ķ����
	*	T item: �߰��� ����Դϴ�.
	* 
	* ��ȯ
	*	int:	���� ����Ʈ�� ũ�⸦ ��ȯ�մϴ�.
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
	* �� �Լ��� ����Ʈ���� ��ҿ� ���� ���� ��Ͽ��� �����մϴ�.
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
	* �� �Լ��� ���ٽ��� ����� ��ȸ�ϸ� �ݺ��մϴ�.
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
	* �� �Լ��� ����Ʈ �� Ư�� �ε����� ��ҿ� �����մϴ�.
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
	* �� �Լ��� ����Ʈ �� Ư�� �ε����� �����մϴ�.
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
	* �� �Լ��� ����Ʈ �� ��� ��Ҹ� �����մϴ�.
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
	* �� �Լ��� ����Ʈ�� ũ�⸦ ��ȯ�մϴ�.
	*/
	int getSize()
	{
		return count;
	}


	/**
	* ������ �ʴ� �Լ�
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
* (**) ������
* �� ���ø� Ŭ������ ��� ������ �Ұ��� �ϵ��� ����� Ŭ�����Դϴ�.
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