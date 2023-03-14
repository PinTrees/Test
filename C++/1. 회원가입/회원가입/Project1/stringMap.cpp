#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;


// 문자열 이진트리 맵 자료구조에 활용할 노드 클래스
template<typename T> class StringMapNode
{
public:

	// 현재 노드의 값
	T value;

	// 현재 노드의 키
    char* key;

	// key 를 기준으로 큰 값의 노드
	StringMapNode* right;
	// key 를 기준으로 작은 값의 노드
	StringMapNode* left;

	StringMapNode(char* _key, T _item, StringMapNode* _left, StringMapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};





// 문자열을 Key 로 사용하는 이진트리 맵
template<typename T> class SMap
{
private:
	StringMapNode<T>* root;

public:

	// 현재 맵의 Key 목록
	//
	// 데이터 입력 및 삭제에 대한 함수접근이 불가능한 리스트로 변경 필요
	// 
	// 빠르고 효율적인 접근 가능.
	// 리스트 순서 보장 불가
	// 리스트를 반복하는 동안 맵이 수정될 경우 오류가 발생할 수 있음
	Iterable<char*> keys;

	// 현재 맵의 Value 목록
	Iterable<T> values;

	// 맵의 Key, Value 의 개수
	int count;

	// [미 설계]
	// 직관적 맵의 존재 여부
	bool isEmpty;

public:

	// 맵 생성시 루트 및 기초값 초기화
	SMap() {
		root = nullptr;
		count = 0;

		keys = Iterable<char*>();
		values = Iterable<T>();
	}
	~SMap() 
	{ 
		keys.clear(); 
		values.clear();
		clear(); 
	}

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
		if (strcmp(node->key, tree->key) < 0) {
			if (tree->left == nullptr) {
				//cout << "save left" << endl;
				tree->left = node;
			}
			else InsertNode(tree->left, node);
		}
		else if (strcmp(node->key, tree->key) > 0)
		{ 
			if (tree->right == nullptr) {
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
		if (node == nullptr) {
			return nullptr;
		}
		if (strcmp(node->key, key) == 0) 
			return node;
		else if (strcmp(node->key, key)	> 0)
			return SearchNode(node->left, key); 
		else if (strcmp(node->key, key) < 0)
			return SearchNode(node->right, key);
	}
	StringMapNode<T>* SearchMinNode(StringMapNode<T>* tree)
	{
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr)return tree;
		else return SearchMinNode(tree->left);
	}
	StringMapNode<T>* removeNode(StringMapNode<T>* root, char* key) {
		String aa;

		if (root == nullptr) { // 삭제할 요소가 없는 경우
			return root;
		}
		if (strcmp(root->key, key) > 0) { // 삭제할 요소가 현재 노드의 왼쪽 서브트리에 있는 경우
			root->left = removeNode(root->left, key);
		}
		else if (strcmp(root->key, key) < 0) { // 삭제할 요소가 현재 노드의 오른쪽 서브트리에 있는 경우
			root->right = removeNode(root->right, key);
		}

		// key == deleteNode.key 
		// 삭제할 노드
		else { 

			// 삭제할 노드의 자식 노드 처리 구문
			// right, left가 null일 경우
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right 노드만 존재할 경우
			if (root->left == nullptr && root->right != nullptr) { 
				StringMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left 노드만 존재할 경우
			else if (root->right == nullptr && root->left != nullptr) {
				StringMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// 모든 자식 노드가 존재할 경우
			else
			{
				// 현재 노드의 값을 제거가 아닌 가장 작은 값으로 덮어쓰기함
				StringMapNode<T>* temp = SearchMinNode(root->right); 
				// 값 덮어쓰기
				// 이진트리를 유지하기 위해서
				root->value = temp->value;
				root->key = temp->key;

				// 덥어쓰기한 원본 값만 찾아서 제거
				// 큰 숫자중 가장 작은 값이므로 자기자신보다 크고 기존의 오른쪽보다 작거나 같으므로 이진트리가 유지됨
				// 자식이 없는 값을 찾아 교체했으므로 하나만 제거하면 됨
				root->right = removeNode(root->right, temp->key);
			}
		}
		return root;
	}
public:
	// Key, Value를 직관적 함수를 통해 추가
	T& add(char* key, T item)
	{
		StringMapNode<T>* data = new StringMapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.add(key);
		values.add(item);
		// 같은 키로 할당했을 경우 예외처리 필요
		count++;

		return data->value;
	}

	// 특정 노드를 문자열 Key 를 통해 삭제
	// 
	// value를 통한 삭제 구현시 value가 T 형식이므로 이진트리 탐색에 적당한 형태의 비교연산이 필요함
	// value는 key와 달리 같음을 확인할 때 항상 주소값이 같아야 하므로, value의 주소값을 intptr_t로 변환하여 비교하는 형태로 구현가능
	int remove(char* key) 
	{
		root = removeNode(root, key);
		return 0;
	}


	// 이진 탐색트리 모두 삭제
	void clear(StringMapNode<T>* node) 
	{
		if (node == nullptr) return;

		// 재귀함수 이므로 값이 있던 없던 모든 자식노드 제거
		clear(node->left);
		clear(node->right);
	
		//cout << "delete map: " << node << endl;
		delete node;
	}
	void clear()
	{
		clear(root);
	}

	// 이 맵에 주어진 [key]가 포함되어 있는지 여부.
	// 
	// 맵의 노드중 Key와 정확하게 같은 Key가 있을 경우에만 true를 반환
	bool ContainKey(char* key) {
		StringMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}


	// [] 배열 연산자 오버라이딩 
	// 
	// 
	// [main code]
	// map[45] = data; 
	// 
	// [] = 를 함께 쓰기위해서는 반환되는 클래스 또는 자료형이 = 연산자 오버로딩을 지원해야함
	// [] = 을 통한 접근은 생성되어있는 목록만 가능. 신규 추가는 add() 함수를 사용 / NULL 안전 문제
	// 
	// 데이터를 리턴할 떄 변경가능한 형태의 클래스를 반환 &
	// 
	// 
	// [참조]
	// https://stackoverflow.com/questions/11575151/defining-the-operator
	// https://stackoverflow.com/questions/3906978/operator-overload
	// https://edykim.com/ko/post/c-operator-overloading-guidelines/
	//
	// [참고]
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	T& operator[] (char* key)
	{
		// 맵에 Key 존재 여부 확인
		if (ContainKey(key)) {

			// Key의 존재 여부를 확인하지 않고 바로 SearchNode()를 호출하여 반환되는 노드값이 nullptr인지를 검사하는 형태로 변경 가능
			// 존재할 경우 해당 값을 찾아서 반환
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}

		// 맵에 Key가 존재하지 않을 경우
		else
		{
			// 맵에 해당 Key, Value=NULL 를 생성해서 반환
			// Map[100] = 40; 형태의 데이터 삽입을 위해서 없을 경우 값을 생성함
			// 좋지 못한 방식
			return add(key, NULL);
		}
	}

	// 정적 문자열 Key를 통한 값 할당이 필요하므로 배열오퍼레이터 const 오버로딩
	T& operator[] (const char* key)
	{
		// 맵에 Key 존재 여부 확인
		// const char* 를 char*로 변경후 동일한 ContainKey() 함수 사용
		if (ContainKey(constCharToChar(key))) {

			// 존재할 경우 해당 값을 찾아서 반환
			StringMapNode<T>* data = SearchNode(root, constCharToChar(key));
			return  data->value;
		}
		else
		{
			return add(constCharToChar(key), NULL);
		}
	}

	// const char* > char* 변환 함수
	char* constCharToChar(const char* str) {
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}
};