#pragma once
#include <iostream>
#include <cstdarg>
#include <functional>

using namespace std;

// 가변인자 매크로 기능 추가

// 03.29 람다식을 통한 ForEach 반복 제어함수 추가
// 03.29 이터레이터를 통한 외부 반복 제어기능 추가

// 기초적 이중연결 리스트
// 추후 단일연결 리스트로 변경 필요
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

template<typename T>
class List
{
public:
	CNode<T>* first;
	CNode<T>* last;
	int count;

public:
	List() : first(NULL), last(NULL), count(0) { }

	// 리스트 선언시 초기화
	// 가변인자는 배열 형식으로 전달됨
	List(int size, T...)
	{
		first = NULL;
		last = NULL;
		count = 0;

		// 가변인자의 포인터
		va_list list;
		// 매개변수의 파라미터가 배열 형식으로 동작하므로 size의 다음 포인터는 T 가변인자의 첫번쨰 위치로 특정할 수 있음
		va_start(list, size); // list는 size메모리크기의 다음 포인터 위치로 세팅;

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

	void ForEach(std::function<void(T)> fptr) {
		CNode<T>* pThis = first;
		while (pThis)
		{
			(fptr)(pThis->value);
			pThis = pThis->next;
		}
	}

	class Iterator
	{
	private:
		CNode<T>* node;
	public:
		Iterator(CNode<T>* node) : node(node) {}

		bool operator!=(const Iterator& other) const {
			return node != other.node;
		}

		T& operator*() {
			return node->value;
		}

		Iterator& operator++() {
			node = node->next;
			return *this;
		}
	};

	Iterator begin() const {
		return Iterator(first);
	}

	Iterator end() const {
		return Iterator(NULL);
	}


	T GetRandom() {
		return elementAt(rand() % count - 1);
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
//template<typename T>




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

	// 신규노드 추가
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

	void ForEach(std::function<void(T)> fptr) {
		CNode<T>* pThis = first;
		while (pThis)
		{
			(fptr)(pThis->value);
			pThis = pThis->next;
		}
	}
	
	// 이터레이터를 통한 외부 반복기능 추가
	class Iterator
	{
	private:
		CNode<T>* node;
	public:
		Iterator(CNode<T>* node) : node(node) {}

		bool operator!=(const Iterator& other) const {
			return node != other.node;
		}

		T& operator*() {
			return node->value;
		}

		Iterator& operator++() {
			node = node->next;
			return *this;
		}
	};

	Iterator begin() const {
		return Iterator(first);
	}

	Iterator end() const {
		return Iterator(NULL);
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