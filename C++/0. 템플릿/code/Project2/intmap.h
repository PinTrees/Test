#pragma once

#include <iostream>
#include <utility>
#include "list.h"

using namespace std;

/**
* int를 Key로 사용하는 Map 자료구조
*/
template<typename T>
class IMapNode
{
public:

	T		value;		 
	int key;		 

	IMapNode* right; 
	IMapNode* left;  

	IMapNode(int _key, T _item, IMapNode* _left, IMapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};

/**
* int를 Key로 사용하는 Map 자료구조
*/
template<typename T> class IntMap
{
private:
	IMapNode<T>* root;

public:
	Iterable<int>		keys;
	Iterable<T>			values;
	int					count;
	bool			    isEmpty;

public:

	IntMap() {
		root = nullptr;
		count = 0;
		keys = Iterable<int>();
		values = Iterable<T>();
	}
	~IntMap()
	{
		keys.clear();
		values.clear();
		clear();
	}

private:

	bool InsertNode(IMapNode<T>* tree, IMapNode<T>* node)
	{
		// 현재 재귀 단계에서의 트리의 루트와 크기 비교 (서브트리의 루트)
		// 크기비교가 가능한 키값을 통해 크기비교 후 데이터 저장
		if (node->key > tree->key) {
			if (tree->left == nullptr) {
				//cout << "save left" << endl;
				tree->left = node;
			}
			else InsertNode(tree->left, node);
		}
		else if (node->key < tree->key)
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
	IMapNode<T>* SearchNode(IMapNode<T>* node, int key)
	{
		if (node == nullptr) {
			return nullptr;
		}
		if (node->key == key)
			return node;
		else if (node->key > key)
			return SearchNode(node->left, key);
		else if (node->key < key)
			return SearchNode(node->right, key);
	}
	IMapNode<T>* SearchMinNode(IMapNode<T>* tree)
	{
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr)return tree;
		else return SearchMinNode(tree->left);
	}
	IMapNode<T>* removeNode(IMapNode<T>* root, int key) {
		String aa;

		if (root == nullptr) { // 삭제할 요소가 없는 경우
			return root;
		}
		if (root->key > key) { // 삭제할 요소가 현재 노드의 왼쪽 서브트리에 있는 경우
			root->left = removeNode(root->left, key);
		}
		else if (root->key < key) { // 삭제할 요소가 현재 노드의 오른쪽 서브트리에 있는 경우
			root->right = removeNode(root->right, key);
		}
		else {

			// 삭제할 노드의 자식 노드 처리 구문
			// right, left가 null일 경우
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right 노드만 존재할 경우
			if (root->left == nullptr && root->right != nullptr) {
				IMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left 노드만 존재할 경우
			else if (root->right == nullptr && root->left != nullptr) {
				IMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// 모든 자식 노드가 존재할 경우
			else
			{
				// 현재 노드의 값을 제거가 아닌 가장 작은 값으로 덮어쓰기함
				IMapNode<T>* temp = SearchMinNode(root->right);
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
	T& Add(int key, T item)
	{
		IMapNode<T>* data = new IMapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.Add(key);
		values.Add(item);

		count++;

		return data->value;
	}
	int remove(int key)
	{
		root = removeNode(root, key);
		return 0;
	}


	void clear(IMapNode<T>* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}
	void clear()
	{
		clear(root);
	}

	// 이 맵에 주어진 [key]가 포함되어 있는지 여부.
	// 맵의 노드중 Key와 정확하게 같은 Key가 있을 경우에만 true를 반환
	bool ContainKey(int key)
	{
		IMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}

	T& GetValueByKey(const int _key)
	{
		int key = (int)_key;
		if (ContainKey(key))
		{
			IMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}

	// [] 배열 연산자 오버라이딩 
	T& operator[] (int key)
	{
		if (ContainKey(key))
		{
			IMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else return Add(key, NULL);
	}
};



/**
* 미 구현
* 내부적으로 키 타입이 int로 고정됨
*/
template<typename K, typename T> class Map
{
private:
	IMapNode<T>* root;

public:
	Iterable<int>			keys;
	Iterable<T>			values;
	int					count;
	bool			    isEmpty;

public:

	Map() {
		root = nullptr;
		count = 0;
		keys = Iterable<K>();
		values = Iterable<T>();
	}
	~Map()
	{
		keys.clear();
		values.clear();
		clear();
	}

private:
	bool InsertNode(IMapNode<T>* tree, IMapNode<T>* node)
	{
		// 현재 재귀 단계에서의 트리의 루트와 크기 비교 (서브트리의 루트)
		// 크기비교가 가능한 키값을 통해 크기비교 후 데이터 저장
		if (node->key > tree->key) {
			if (tree->left == nullptr) {
				//cout << "save left" << endl;
				tree->left = node;
			}
			else InsertNode(tree->left, node);
		}
		else if (node->key < tree->key)
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
	IMapNode<T>* SearchNode(IMapNode<T>* node, int key)
	{
		if (node == nullptr) {
			return nullptr;
		}
		if (node->key == key)
			return node;
		else if (node->key > key)
			return SearchNode(node->left, key);
		else if (node->key < key)
			return SearchNode(node->right, key);
	}
	IMapNode<T>* SearchMinNode(IMapNode<T>* tree)
	{
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr)return tree;
		else return SearchMinNode(tree->left);
	}
	IMapNode<T>* removeNode(IMapNode<T>* root, int key) {
		String aa;

		if (root == nullptr) { // 삭제할 요소가 없는 경우
			return root;
		}
		if (root->key > key) { // 삭제할 요소가 현재 노드의 왼쪽 서브트리에 있는 경우
			root->left = removeNode(root->left, key);
		}
		else if (root->key < key) { // 삭제할 요소가 현재 노드의 오른쪽 서브트리에 있는 경우
			root->right = removeNode(root->right, key);
		}
		else {

			// 삭제할 노드의 자식 노드 처리 구문
			// right, left가 null일 경우
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right 노드만 존재할 경우
			if (root->left == nullptr && root->right != nullptr) {
				IMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left 노드만 존재할 경우
			else if (root->right == nullptr && root->left != nullptr) {
				IMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// 모든 자식 노드가 존재할 경우
			else
			{
				// 현재 노드의 값을 제거가 아닌 가장 작은 값으로 덮어쓰기함
				IMapNode<T>* temp = SearchMinNode(root->right);
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
	T& Add(int key, T item)
	{
		IMapNode<T>* data = new IMapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.Add(key);
		values.Add(item);

		count++;

		return data->value;
	}
	int remove(int key)
	{
		root = removeNode(root, key);
		return 0;
	}


	void clear(IMapNode<T>* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}
	void clear()
	{
		clear(root);
	}

	// 이 맵에 주어진 [key]가 포함되어 있는지 여부.
	// 맵의 노드중 Key와 정확하게 같은 Key가 있을 경우에만 true를 반환
	bool ContainKey(int key)
	{
		IMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}

	T& GetValueByKey(const int _key)
	{
		int key = (int)_key;
		if (ContainKey(key))
		{
			IMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return Add(key, NULL);
		}
	}

	// [] 배열 연산자 오버라이딩 
	T& operator[] (int key)
	{
		if (ContainKey(key))
		{
			IMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else return Add(key, NULL);
	}
};