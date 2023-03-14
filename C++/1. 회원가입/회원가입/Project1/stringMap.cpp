#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;


// ���ڿ� ����Ʈ�� �� �ڷᱸ���� Ȱ���� ��� Ŭ����
template<typename T> class StringMapNode
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

	// ���� ���� Key ���
	//
	// ������ �Է� �� ������ ���� �Լ������� �Ұ����� ����Ʈ�� ���� �ʿ�
	// 
	// ������ ȿ������ ���� ����.
	// ����Ʈ ���� ���� �Ұ�
	// ����Ʈ�� �ݺ��ϴ� ���� ���� ������ ��� ������ �߻��� �� ����
	Iterable<char*> keys;

	// ���� ���� Value ���
	Iterable<T> values;

	// ���� Key, Value �� ����
	int count;

	// [�� ����]
	// ������ ���� ���� ����
	bool isEmpty;

public:

	// �� ������ ��Ʈ �� ���ʰ� �ʱ�ȭ
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
	// Key, Value�� ������ �Լ��� ���� �߰�
	T& add(char* key, T item)
	{
		StringMapNode<T>* data = new StringMapNode<T>(key, item, nullptr, nullptr);

		if (root == nullptr) root = data;
		else InsertNode(root, data);

		keys.add(key);
		values.add(item);
		// ���� Ű�� �Ҵ����� ��� ����ó�� �ʿ�
		count++;

		return data->value;
	}

	// Ư�� ��带 ���ڿ� Key �� ���� ����
	// 
	// value�� ���� ���� ������ value�� T �����̹Ƿ� ����Ʈ�� Ž���� ������ ������ �񱳿����� �ʿ���
	// value�� key�� �޸� ������ Ȯ���� �� �׻� �ּҰ��� ���ƾ� �ϹǷ�, value�� �ּҰ��� intptr_t�� ��ȯ�Ͽ� ���ϴ� ���·� ��������
	int remove(char* key) 
	{
		root = removeNode(root, key);
		return 0;
	}


	// ���� Ž��Ʈ�� ��� ����
	void clear(StringMapNode<T>* node) 
	{
		if (node == nullptr) return;

		// ����Լ� �̹Ƿ� ���� �ִ� ���� ��� �ڽĳ�� ����
		clear(node->left);
		clear(node->right);
	
		//cout << "delete map: " << node << endl;
		delete node;
	}
	void clear()
	{
		clear(root);
	}

	// �� �ʿ� �־��� [key]�� ���ԵǾ� �ִ��� ����.
	// 
	// ���� ����� Key�� ��Ȯ�ϰ� ���� Key�� ���� ��쿡�� true�� ��ȯ
	bool ContainKey(char* key) {
		StringMapNode<T>* data = SearchNode(root, key);
		if (data == nullptr) return false;
		return true;
	}


	// [] �迭 ������ �������̵� 
	// 
	// 
	// [main code]
	// map[45] = data; 
	// 
	// [] = �� �Բ� �������ؼ��� ��ȯ�Ǵ� Ŭ���� �Ǵ� �ڷ����� = ������ �����ε��� �����ؾ���
	// [] = �� ���� ������ �����Ǿ��ִ� ��ϸ� ����. �ű� �߰��� add() �Լ��� ��� / NULL ���� ����
	// 
	// �����͸� ������ �� ���氡���� ������ Ŭ������ ��ȯ &
	// 
	// 
	// [����]
	// https://stackoverflow.com/questions/11575151/defining-the-operator
	// https://stackoverflow.com/questions/3906978/operator-overload
	// https://edykim.com/ko/post/c-operator-overloading-guidelines/
	//
	// [����]
	// https://stackoverflow.com/questions/32796932/using-a-custom-class-with-a-custom-template-container
	T& operator[] (char* key)
	{
		// �ʿ� Key ���� ���� Ȯ��
		if (ContainKey(key)) {

			// Key�� ���� ���θ� Ȯ������ �ʰ� �ٷ� SearchNode()�� ȣ���Ͽ� ��ȯ�Ǵ� ��尪�� nullptr������ �˻��ϴ� ���·� ���� ����
			// ������ ��� �ش� ���� ã�Ƽ� ��ȯ
			StringMapNode<T>* data = SearchNode(root, key);
			return  data->value;
		}

		// �ʿ� Key�� �������� ���� ���
		else
		{
			// �ʿ� �ش� Key, Value=NULL �� �����ؼ� ��ȯ
			// Map[100] = 40; ������ ������ ������ ���ؼ� ���� ��� ���� ������
			// ���� ���� ���
			return add(key, NULL);
		}
	}

	// ���� ���ڿ� Key�� ���� �� �Ҵ��� �ʿ��ϹǷ� �迭���۷����� const �����ε�
	T& operator[] (const char* key)
	{
		// �ʿ� Key ���� ���� Ȯ��
		// const char* �� char*�� ������ ������ ContainKey() �Լ� ���
		if (ContainKey(constCharToChar(key))) {

			// ������ ��� �ش� ���� ã�Ƽ� ��ȯ
			StringMapNode<T>* data = SearchNode(root, constCharToChar(key));
			return  data->value;
		}
		else
		{
			return add(constCharToChar(key), NULL);
		}
	}

	// const char* > char* ��ȯ �Լ�
	char* constCharToChar(const char* str) {
		int length = strlen(str) + 1;
		char* characters = new char[length];

		for (int i = 0; i != length; i++) characters[i] = str[i];
		characters[length - 1] = NULL;

		return characters;
	}
};