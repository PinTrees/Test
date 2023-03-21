#pragma once
#include <iostream>
#include <utility>
#include "list.h";
#include "string.h";

using namespace std;

// ���� ������ �� ������ ���ø����� �ٽ� ����

// ���ڿ� ����Ʈ�� �� �ڷᱸ���� Ȱ���� ��� Ŭ����
template<typename T>
class StringMapNode
{
public:
	// ���� ����� ��
	T value;
	// ���� ����� Ű
	char* key;

	// key �� �������� ū ���� ���
	StringMapNode* right;
	// key �� �������� ���� ���� ���
	StringMapNode* left;

	StringMapNode(char* _key, T _item, StringMapNode* _left, StringMapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};


// ���ڿ��� Key �� ����ϴ� ����Ʈ�� ��
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
		// ���� ��� �ܰ迡���� Ʈ���� ��Ʈ�� ũ�� �� (����Ʈ���� ��Ʈ)
		// ũ��񱳰� ������ Ű���� ���� ũ��� �� ������ ����
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
				StringMapNode<T>* temp = root->right;
				delete root;
				return temp;
			}

			// left ��常 ������ ���
			else if (root->right == nullptr && root->left != nullptr) {
				StringMapNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// ��� �ڽ� ��尡 ������ ���
			else
			{
				// ���� ����� ���� ���Ű� �ƴ� ���� ���� ������ �������
				StringMapNode<T>* temp = SearchMinNode(root->right);
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

	// �� �ʿ� �־��� [key]�� ���ԵǾ� �ִ��� ����.
	// ���� ����� Key�� ��Ȯ�ϰ� ���� Key�� ���� ��쿡�� true�� ��ȯ
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

	// [] �迭 ������ �������̵� 
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