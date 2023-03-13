#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;


// 문자열 이진트리 맵 자료구조에 활용할 클래스
template<typename T> class StringMapNode
{
public:
	// 값
	T value;

    char* key;

	// key를 기준으로 큰 값의 노드
	StringMapNode* right;
	// key를 기준으로 작은 값의 노드
	StringMapNode* left;

	StringMapNode(char* _key, T _item, StringMapNode* _left, StringMapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};





// 기초적 이진트리 맵
template<typename T> class SMap
{
private:
	StringMapNode<T>* root;

public:
	// 현재 맵의 key리스트 및 value리스트  entry - keys, values
	//
	// !!!! 추가 수정 필요
	// 
	// [수정됨 Iterable]
	// 데이터 입력 및 삭제에 대한 함수접근이 불가능한 리스트로 변경 필요
	// 
	// 
	// 빠르고 효율적인 접근 가능.
	// 리스트 순서 보장 불가
	// 리스트를 반복하는 동안 맵이 수정될 경우 오류가 발생할 수 있음
	Iterable<char*> keys;
	Iterable<T> values;

	// 맵의 key, value의 개수
	int count;

	// 직관적 맵의 존재 여부
	bool isEmpty;

public:
	SMap() {
		root = NULL;
		count = 0;
	}
	~SMap() { clear(); }

private:
	// 고유한 해시키 및 이진탐색 비교 연산이 가능한 자료형으로 변환 작업
	// (int)&key 형식의 포인터 값을 통한 키 생성 시도
	// 
	// [참조]
	// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
	// https://stackoverflow.com/questions/14446183/implementing-a-hashmap-in-c-hashing-function-for-templated-data-type

	// 이진트리 탐색 함수 비활성화
	// 
	// 
	// 이진트리 노드 추가 재귀함수
	bool InsertNode(StringMapNode<T>* tree, StringMapNode<T>* node)
	{
		// 현재 재귀 단계에서의 트리의 루트와 크기 비교 (서브트리의 루트)
		// 크기비교가 가능한 키값을 통해 크기비교 후 데이터 저장
		if (strcmp(node->key, tree->key) > 0) {
			if (tree->left == NULL) {
				//cout << "save left" << endl;
				tree->left = node;
			}
			else InsertNode(tree->left, node);
		}
		else if (strcmp(node->key, tree->key) < 0)
		{
			if (tree->right == NULL) {
				//cout << "save right" << endl;
				tree->right = node;
			}
			else InsertNode(tree->right, node);
		}
		// 값이 같을 경우 예외처리
		else return false;
		return true;
	}
	StringMapNode<T>* SearchNode(StringMapNode<T>* node, char* key)
	{
		if (node == NULL) return NULL;
		if (strcmp(node->key, key) == 0)
			return node;
		else if (strcmp(node->key, key)	< 0)
			return SearchNode(node->left, key); 
		else if (strcmp(node->key, key) > 0)
			return SearchNode(node->right, key);
	}

public:
	// Key, Value 값 추가
	T& add(char* key, T item)
	{
		StringMapNode<T>* data = new StringMapNode<T>(key, item, NULL, NULL);

		if (root == NULL) root = data;
		else InsertNode(root, data);

		keys.add(key);
		values.add(item);
		// 같은 키로 할당했을 경우 예외처리 필요
		count++;

		return data->value;
	}
	int remove(T item)
	{

	}
	void clear()
	{
	}

	bool ContainKey(char* key) {
		StringMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}

	// [] 배열 연산자 오버라이딩 
	// 
	// 
	// [map code]
	// return T*;   return T
	// 
	// [main code]
	// map[45] = data; 
	// 
	// 위 코드를 시도하였으나 실패함
	// 
	// 
	// [] = 를 함께 쓰기위해서는 반환되는 클래스 또는 자료형이 = 연산자 오버로딩을 지원해야함
	// += / -= 과 같이 함께 사용 불가
	// [] / = 각각의 클래스에서 직접 구현
	// 하려 했으나 NULL 및 각종 오류로 포기함
	// 
	// [] = 을 통한 접근은 생성되어있는 목록만 가능. 신규 추가는 add() 함수를 사용 / NULL 안전 문제
	// 
	// 데이터를 리턴할 떄 변경가능한 클래스를 반환 & / const
	// 
	// 
	// 
	// [참조]
	// https://stackoverflow.com/questions/11575151/defining-the-operator
	// https://stackoverflow.com/questions/3906978/operator-overload
	// https://edykim.com/ko/post/c-operator-overloading-guidelines/
	//
	//
	// [참고]
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	T& operator[] (char* key)
	{
		if (ContainKey(key)) {
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return add(key, NULL);
		}
	}
	T& operator[] (const char* key)
	{
		if (ContainKey(constToN(key))) {
			StringMapNode<T>* data = SearchNode(root, constToN(key));
			return  data->value;
		}
		else
		{
			return add(constToN(key), NULL);
		}
	}

	// const char* > char* 변환 함수
	char* constToN(const char* str) {
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}
};