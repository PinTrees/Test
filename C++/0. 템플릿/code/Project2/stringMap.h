#pragma once
#include <iostream>
#include <utility>
#include "list.h"
#include "string.h"

using namespace std;

/**
* �� ���ø� Ŭ������ ����Ʈ���� �ڷᱸ���� ��� Ŭ�����Դϴ�.
*/
template<typename T>
class MapNode
{
public:
	
	T		value;		 // ���� ����� ��
	char*	key;		 // ���� ����� Ű
	
	MapNode* right;		// key �� �������� ū ���� ���
	MapNode* left;		// key �� �������� ���� ���� ���

	MapNode(char* _key, T _item, MapNode* _left, MapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};


/**
* �� ���ø� Ŭ������ ���ڿ��� Ű�� ����ϴ� ����Ʈ���� Ŭ�����Դϴ�.
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
	* �� ���� �Լ�
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
		// ���� ���� ��� ����ó��
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

		if (root == nullptr) { // ������ ��Ұ� ���� ���
			return root;
		}
		if (strcmp(root->key, key) > 0) { // ������ ��Ұ� ���� ����� ���� ����Ʈ���� �ִ� ���
			root->left = removeNode(root->left, key);
		}
		else if (strcmp(root->key, key) < 0) { // ������ ��Ұ� ���� ����� ������ ����Ʈ���� �ִ� ���
			root->right = removeNode(root->right, key);
		}

		// key == deleteNode.key 
		// ������ ���
		else {

			// ������ ����� �ڽ� ��� ó�� ����
			// right, left�� null�� ���
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right ��常 ������ ���
			if (root->left == nullptr && root->right != nullptr) {
				MapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left ��常 ������ ���
			else if (root->right == nullptr && root->left != nullptr) {
				MapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// ��� �ڽ� ��尡 ������ ���
			else
			{
				// ���� ����� ���� ���Ű� �ƴ� ���� ���� ������ �������
				MapNode<T>* temp = SearchMinNode(root->right);
				// �� �����
				// ����Ʈ���� �����ϱ� ���ؼ�
				root->value = temp->value;
				root->key = temp->key;

				// ������� ���� ���� ã�Ƽ� ����
				// ū ������ ���� ���� ���̹Ƿ� �ڱ��ڽź��� ũ�� ������ �����ʺ��� �۰ų� �����Ƿ� ����Ʈ���� ������
				// �ڽ��� ���� ���� ã�� ��ü�����Ƿ� �ϳ��� �����ϸ� ��
				root->right = removeNode(root->right, temp->key);
			}
		}
		return root;
	}

public:
	/**
	* �� �Լ��� �ʿ� ��Ҹ� �߰��մϴ�.
	* 
	* �� ��Ͽ� ��Ҹ� �߰��մϴ�.
	* Ű ����Ʈ�� Ű�� �߰��մϴ�.
	* �� ����Ʈ�� ���� �߰��մϴ�.
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
	* �� �Լ��� �� ��Ͽ��� Ű�� ��ġ�ϴ� ��Ҹ� �����մϴ�.
	*/
	int remove(char* key)
	{
		root = removeNode(root, key);
		return 0;
	}

	/**
	* �� �Լ��� ����� ������带 �����մϴ�.
	*/
	void clear(MapNode<T>* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

	/**
	* �� �Լ��� ���� ��� ����� �����մϴ�.
	*/
	void clear()
	{
		clear(root);
	}

	// �� �ʿ� �־��� [key]�� ���ԵǾ� �ִ��� ����.
	// ���� ����� Key�� ��Ȯ�ϰ� ���� Key�� ���� ��쿡�� true�� ��ȯ
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

	// [] �迭 ������ �������̵� 
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