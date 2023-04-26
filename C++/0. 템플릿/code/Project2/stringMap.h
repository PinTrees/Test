#pragma once
#include <iostream>
#include <utility>
#include "list.h"
#include "string.h"

using namespace std;

/**
* 이 템플릿 클래스는 이진트리맵 자료구조의 노드 클래스입니다.
*/
template<typename T>
class MapNode
{
public:
	
	T		value;		 // 현재 노드의 값
	char*	key;		 // 현재 노드의 키
	
	MapNode* right;		// key 를 기준으로 큰 값의 노드
	MapNode* left;		// key 를 기준으로 작은 값의 노드

	MapNode(char* _key, T _item, MapNode* _left, MapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};


/**
* 이 템플릿 클래스는 문자열을 키로 사용하는 이진트리맵 클래스입니다.
*/
template<typename T> class SMap
{
private:
	MapNode<T>* root;

public:
	Iterable<char*>		keys;
	Iterable<T>			values;
	int					count;
	bool			    isEmpty;

public:

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
	/**
	* 맵 내부 함수
	*/
	bool InsertNode(MapNode<T>* tree, MapNode<T>* node)
	{
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
	MapNode<T>* SearchNode(MapNode<T>* node, char* key)
	{
		if (node == nullptr) {
			return nullptr;
		}
		if (strcmp(node->key, key) == 0)
			return node;
		else if (strcmp(node->key, key) > 0)
			return SearchNode(node->left, key);
		else if (strcmp(node->key, key) < 0)
			return SearchNode(node->right, key);
		else return nullptr;
	}
	MapNode<T>* SearchMinNode(MapNode<T>* tree)
	{
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr)return tree;
		else return SearchMinNode(tree->left);
	}
	MapNode<T>* removeNode(MapNode<T>* root, char* key) {
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
				MapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left 노드만 존재할 경우
			else if (root->right == nullptr && root->left != nullptr) {
				MapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// 모든 자식 노드가 존재할 경우
			else
			{
				// 현재 노드의 값을 제거가 아닌 가장 작은 값으로 덮어쓰기함
				MapNode<T>* temp = SearchMinNode(root->right);
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
	/**
	* 이 함수는 맵에 요소를 추가합니다.
	* 
	* 맵 목록에 요소를 추가합니다.
	* 키 리스트에 키를 추가합니다.
	* 값 리스트에 값을 추가합니다.
	*/
	T& Add(char* key, T item)
	{
		MapNode<T>* data = new MapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.Add(key);
		values.Add(item);

		count++;

		return data->value;
	}

	/**
	* 이 함수는 맵 목록에서 키와 일치하는 요소를 제거합니다.
	*/
	int remove(char* key)
	{
		root = removeNode(root, key);
		return 0;
	}

	/**
	* 이 함수는 노드의 하위노드를 제거합니다.
	*/
	void clear(MapNode<T>* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

	/**
	* 이 함수는 맵의 모든 목록을 제거합니다.
	*/
	void clear()
	{
		clear(root);
	}

	// 이 맵에 주어진 [key]가 포함되어 있는지 여부.
	// 맵의 노드중 Key와 정확하게 같은 Key가 있을 경우에만 true를 반환
	bool ContainKey(char* key)
	{
		MapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}
	bool ContainKey(String key)
	{
		MapNode<T>* data = SearchNode(root, key.characters);
		if (data == nullptr) return false;
		return true;
	}

	T& GetValueByKey(const char* _key)
	{
		char* key = (char*)_key;
		if (ContainKey(key))
		{
			MapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}
	T& GetValueByKey(String _key)
	{ 
		char* key = (char*)_key.characters;
		if (ContainKey(key))
		{
			MapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}

	// [] 배열 연산자 오버라이딩 
	T& operator[] (char* key)
	{
		if (ContainKey(key))
		{
			MapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	} 
	T& operator[] (String _key)
	{
		char* key = _key.characters;
		if (ContainKey(key))
		{
			MapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}

	T& operator[] (const char* _key)
	{
		char* key = (char*)_key;
		if (ContainKey(key))
		{
			MapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}
};