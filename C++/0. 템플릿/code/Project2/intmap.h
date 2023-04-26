#pragma once

#include <iostream>
#include <utility>
#include "list.h"

using namespace std;

/**
* int�� Key�� ����ϴ� Map �ڷᱸ��
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
* int�� Key�� ����ϴ� Map �ڷᱸ��
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
		// ���� ��� �ܰ迡���� Ʈ���� ��Ʈ�� ũ�� �� (����Ʈ���� ��Ʈ)
		// ũ��񱳰� ������ Ű���� ���� ũ��� �� ������ ����
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
		// ���� ���� ��� ����ó��
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

		if (root == nullptr) { // ������ ��Ұ� ���� ���
			return root;
		}
		if (root->key > key) { // ������ ��Ұ� ���� ����� ���� ����Ʈ���� �ִ� ���
			root->left = removeNode(root->left, key);
		}
		else if (root->key < key) { // ������ ��Ұ� ���� ����� ������ ����Ʈ���� �ִ� ���
			root->right = removeNode(root->right, key);
		}
		else {

			// ������ ����� �ڽ� ��� ó�� ����
			// right, left�� null�� ���
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right ��常 ������ ���
			if (root->left == nullptr && root->right != nullptr) {
				IMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left ��常 ������ ���
			else if (root->right == nullptr && root->left != nullptr) {
				IMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// ��� �ڽ� ��尡 ������ ���
			else
			{
				// ���� ����� ���� ���Ű� �ƴ� ���� ���� ������ �������
				IMapNode<T>* temp = SearchMinNode(root->right);
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

	// �� �ʿ� �־��� [key]�� ���ԵǾ� �ִ��� ����.
	// ���� ����� Key�� ��Ȯ�ϰ� ���� Key�� ���� ��쿡�� true�� ��ȯ
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

	// [] �迭 ������ �������̵� 
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
* �� ����
* ���������� Ű Ÿ���� int�� ������
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
		// ���� ��� �ܰ迡���� Ʈ���� ��Ʈ�� ũ�� �� (����Ʈ���� ��Ʈ)
		// ũ��񱳰� ������ Ű���� ���� ũ��� �� ������ ����
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
		// ���� ���� ��� ����ó��
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

		if (root == nullptr) { // ������ ��Ұ� ���� ���
			return root;
		}
		if (root->key > key) { // ������ ��Ұ� ���� ����� ���� ����Ʈ���� �ִ� ���
			root->left = removeNode(root->left, key);
		}
		else if (root->key < key) { // ������ ��Ұ� ���� ����� ������ ����Ʈ���� �ִ� ���
			root->right = removeNode(root->right, key);
		}
		else {

			// ������ ����� �ڽ� ��� ó�� ����
			// right, left�� null�� ���
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}

			// right ��常 ������ ���
			if (root->left == nullptr && root->right != nullptr) {
				IMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left ��常 ������ ���
			else if (root->right == nullptr && root->left != nullptr) {
				IMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// ��� �ڽ� ��尡 ������ ���
			else
			{
				// ���� ����� ���� ���Ű� �ƴ� ���� ���� ������ �������
				IMapNode<T>* temp = SearchMinNode(root->right);
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

	// �� �ʿ� �־��� [key]�� ���ԵǾ� �ִ��� ����.
	// ���� ����� Key�� ��Ȯ�ϰ� ���� Key�� ���� ��쿡�� true�� ��ȯ
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

	// [] �迭 ������ �������̵� 
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