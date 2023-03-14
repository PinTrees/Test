#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;
// 사용되지 않는 코드
// 사용되지 않는 코드
// 사용되지 않는 코드
// 사용되지 않는 코드
// 사용되지 않는 코드
// 사용되지 않는 코드


// Map<class, class> 형태의 맵을 구현하려 했으나
// Key 값의 적당한 비교연산을 찾지 못함
// Key 값의 포인터를 int형으로 변환하여 비교연산을 시도했으나 const Key를 통한 value 접근이 가능하도록 설계해야하므로 사용불가
// [결론]
// Key 의 byte를 비교가능한 형태의 값으로 변경후 저장


// 이진트리 맵 자료구조에 활용할 클래스
template<typename K, typename T> class MapNode
{
public:
	// 값
	T value;

	// 현재 노드의 키
	// 
	// 맵의 K 값을 기준으로 이진트리를 구성하기위해 크기비교가 가능하도록 포인터를 인트형으로 변환
	// 포인터 > int
	intptr_t key;

	K keyOrg;

	// key를 기준으로 큰 값의 노드
	MapNode* right;

	// key를 기준으로 작은 값의 노드
	MapNode* left;

	MapNode(intptr_t _key, K k, T _item, MapNode* _left, MapNode* _right)
	{
		value = _item;
		keyOrg = k;
		key = _key;
		right = _right;
		left = _left;
	}
};





// 기초적 이진트리 맵
template<typename K, typename T> class Map
{
private:
	MapNode<K, T>* root;

public:

	// 현재 맵의 key리스트 및 value리스트  entry - keys, values
	//
	// 데이터 입력 및 삭제에 대한 함수접근이 불가능한 리스트로 변경 필요
	// 
	// 빠르고 효율적인 접근 가능.
	// 리스트 순서 보장 불가
	// 리스트를 반복하는 동안 맵이 수정될 경우 오류가 발생할 수 있음
	Iterable<K> keys;
	Iterable<T> values;

	// 맵의 key, value의 개수
	int count;

	// 직관적 맵의 존재 여부
	bool isEmpty;

public:
	Map() {
		root = NULL;
		count = 0;
	}
	~Map() { clear(); }

private:
	// 고유한 해시키 및 이진탐색 비교 연산이 가능한 자료형으로 변환 작업
	// (int)&key 형식의 포인터 값을 통한 키 생성 시도
	// 
	// [참조]
	// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
	// https://stackoverflow.com/questions/14446183/implementing-a-hashmap-in-c-hashing-function-for-templated-data-type
	intptr_t hasing(K key)
	{
		//cout << std::hash<K>()(key) << endl;

		// [질문]
		// Map<String, String> map; 생성시
		// map["key"] = "test"; 를 통한 할당을 시도할 경우 아래 라인에서 오류를 반환
		// 
		// [오류 C2064]
		// 항은 1개의 인수를 받아들이는 함수로 계산되지 않습니다. ConsoleApplication1 C : \Users\TaeGi\Downloads\map.cpp 85 
		//
		// [오류 원인 가능성]
		// [] = 연산자를 통한 String class 삽입시 Key class가 생성되지 않은 상태에서 hash 함수를 호출 - 인수 없음
		return std::hash<K>()(key);
	}

	// 이진트리 탐색 함수 비활성화
	// 
	// 
	// 이진트리 노드 추가 재귀함수
	bool InsertNode(MapNode<K, T>* tree, MapNode<K, T>* node)
	{
		// 현재 재귀 단계에서의 트리의 루트와 크기 비교 (서브트리의 루트)
		// 크기비교가 가능한 키값을 통해 크기비교 후 데이터 저장
		if (node->key < tree->key)
		{
			if (tree->left == NULL) tree->left = node;
			else InsertNode(tree->left, node);
		}
		else if (node->key > tree->key)
		{
			if (tree->right == NULL) tree->right = node;
			else InsertNode(tree->right, node);
		}
		// 값이 같을 경우 예외처리
		else return false;
		return true;
	}
	MapNode<K, T>* SearchNode(MapNode<K, T>* node, intptr_t key)
	{
		if (node == NULL) return NULL;
		if (node->key == key)
			return node;
		else if (node->key > key)
			return SearchNode(node->left, key);
		else if (node->key < key)
			return SearchNode(node->right, key);
	}

public:
	// Key, Value 값 추가
	T& add(K key, T item)
	{
		MapNode<K, T>* data = new MapNode<K, T>(hasing(key), key, item, NULL, NULL);

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

	bool Contain(K key) {
		MapNode<K, T>* data = SearchNode(root, hasing(key));
		if (data == nullptr) return false;
		return true;
	}
	int ContainString(char* key) {
		for (int i = 0; i < keys.count; i++) {
			const char* data = keys.elementAtIn(i);

			if (strcmp(key, data) == 0)
				return i;
		}
		return -1;
	}

	K GetKeyHash(K key)
	{
		MapNode<K, T>* data = SearchNode(root, hasing(key));

		// = 를 통한 맵 생성 지원
		// 
		// 요청한 키의 값이 NULL일 경우 노드 신규생성 후 리턴
		// 
		// [example code]
		// map[key] = value;
		if (data == NULL) {
			//cout << "create new map data" << endl;

			add(key, NULL);
			data = SearchNode(root, hasing(key));
		}

		return  data->keyOrg;
	}



	// [] 배열 연산자 오버라이딩 
	// 
	// 
	// [] = 를 함께 쓰기위해서는 반환되는 클래스 또는 자료형이 = 연산자 오버로딩을 지원해야함
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
	T& operator[] (K key)
	{
		/*if (strcmp(typeid(K).name(), "class String") == 0) {
			String* str = static_cast<String*>(key);
			int index = ContainString(str->characters);
			
			if(index != -1)	return values.elementAt(index);
		}*/
		 
		if (Contain(key)) {
			MapNode<K, T>* data = SearchNode(root, hasing(key));
			return  data->value;
		}
		else
		{
			return add(key, NULL);
		}
	}
};