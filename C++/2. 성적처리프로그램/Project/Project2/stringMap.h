#pragma once
#include <iostream>
#include <utility>
#include "list.h";
#include "string.h";

using namespace std;

// 추후 완전한 맵 형태의 템플릿으로 다시 구현

// 문자열 이진트리 맵 자료구조에 활용할 노드 클래스
template<typename T>
class StringMapNode
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

	Iterable<char*> keys;
	Iterable<T> values;
	int count;

	bool isEmpty;

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
		else if (strcmp(node->key, key) > 0)
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
	T& add(char* key, T item)
	{
		StringMapNode<T>* data = new StringMapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.add(key);
		values.add(item);

		count++;

		return data->value;
	}
	int remove(char* key)
	{
		root = removeNode(root, key);
		return 0;
	}


	void clear(StringMapNode<T>* node)
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
	bool ContainKey(char* key) {
		StringMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}
	T& GetValueByKey(const char* _key)
	{
		char* key = (char*)_key;
		if (ContainKey(key))
		{
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return add(key, NULL);
		}
	}

	// [] 배열 연산자 오버라이딩 
	T& operator[] (char* key)
	{
		if (ContainKey(key))
		{
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return add(key, NULL);
		}
	} 

	T& operator[] (const char* _key)
	{
		char* key = (char*)_key;
		if (ContainKey(key))
		{
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}
		else
		{
			return add(key, NULL);
		}
	}
};