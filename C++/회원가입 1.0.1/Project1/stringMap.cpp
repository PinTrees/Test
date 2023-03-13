#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;


// ���ڿ� ����Ʈ�� �� �ڷᱸ���� Ȱ���� Ŭ����
template<typename T> class StringMapNode
{
public:
	// ��
	T value;

    char* key;

	// key�� �������� ū ���� ���
	StringMapNode* right;
	// key�� �������� ���� ���� ���
	StringMapNode* left;

	StringMapNode(char* _key, T _item, StringMapNode* _left, StringMapNode* _right)
	{
		value = _item;
		key = _key;

		right = _right;
		left = _left;
	}
};





// ������ ����Ʈ�� ��
template<typename T> class SMap
{
private:
	StringMapNode<T>* root;

public:
	// ���� ���� key����Ʈ �� value����Ʈ  entry - keys, values
	//
	// !!!! �߰� ���� �ʿ�
	// 
	// [������ Iterable]
	// ������ �Է� �� ������ ���� �Լ������� �Ұ����� ����Ʈ�� ���� �ʿ�
	// 
	// 
	// ������ ȿ������ ���� ����.
	// ����Ʈ ���� ���� �Ұ�
	// ����Ʈ�� �ݺ��ϴ� ���� ���� ������ ��� ������ �߻��� �� ����
	Iterable<char*> keys;
	Iterable<T> values;

	// ���� key, value�� ����
	int count;

	// ������ ���� ���� ����
	bool isEmpty;

public:
	SMap() {
		root = NULL;
		count = 0;
	}
	~SMap() { clear(); }

private:
	// ������ �ؽ�Ű �� ����Ž�� �� ������ ������ �ڷ������� ��ȯ �۾�
	// (int)&key ������ ������ ���� ���� Ű ���� �õ�
	// 
	// [����]
	// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
	// https://stackoverflow.com/questions/14446183/implementing-a-hashmap-in-c-hashing-function-for-templated-data-type

	// ����Ʈ�� Ž�� �Լ� ��Ȱ��ȭ
	// 
	// 
	// ����Ʈ�� ��� �߰� ����Լ�
	bool InsertNode(StringMapNode<T>* tree, StringMapNode<T>* node)
	{
		// ���� ��� �ܰ迡���� Ʈ���� ��Ʈ�� ũ�� �� (����Ʈ���� ��Ʈ)
		// ũ��񱳰� ������ Ű���� ���� ũ��� �� ������ ����
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
		// ���� ���� ��� ����ó��
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
	// Key, Value �� �߰�
	T& add(char* key, T item)
	{
		StringMapNode<T>* data = new StringMapNode<T>(key, item, NULL, NULL);

		if (root == NULL) root = data;
		else InsertNode(root, data);

		keys.add(key);
		values.add(item);
		// ���� Ű�� �Ҵ����� ��� ����ó�� �ʿ�
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

	// [] �迭 ������ �������̵� 
	// 
	// 
	// [map code]
	// return T*;   return T
	// 
	// [main code]
	// map[45] = data; 
	// 
	// �� �ڵ带 �õ��Ͽ����� ������
	// 
	// 
	// [] = �� �Բ� �������ؼ��� ��ȯ�Ǵ� Ŭ���� �Ǵ� �ڷ����� = ������ �����ε��� �����ؾ���
	// += / -= �� ���� �Բ� ��� �Ұ�
	// [] / = ������ Ŭ�������� ���� ����
	// �Ϸ� ������ NULL �� ���� ������ ������
	// 
	// [] = �� ���� ������ �����Ǿ��ִ� ��ϸ� ����. �ű� �߰��� add() �Լ��� ��� / NULL ���� ����
	// 
	// �����͸� ������ �� ���氡���� Ŭ������ ��ȯ & / const
	// 
	// 
	// 
	// [����]
	// https://stackoverflow.com/questions/11575151/defining-the-operator
	// https://stackoverflow.com/questions/3906978/operator-overload
	// https://edykim.com/ko/post/c-operator-overloading-guidelines/
	//
	//
	// [����]
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

	// const char* > char* ��ȯ �Լ�
	char* constToN(const char* str) {
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}
};