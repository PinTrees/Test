#pragma once
#include <iostream>
#include <utility>
#include "list.cpp";
#include "string.cpp";

using namespace std;
// ������ �ʴ� �ڵ�
// ������ �ʴ� �ڵ�
// ������ �ʴ� �ڵ�
// ������ �ʴ� �ڵ�
// ������ �ʴ� �ڵ�
// ������ �ʴ� �ڵ�


// Map<class, class> ������ ���� �����Ϸ� ������
// Key ���� ������ �񱳿����� ã�� ����
// Key ���� �����͸� int������ ��ȯ�Ͽ� �񱳿����� �õ������� const Key�� ���� value ������ �����ϵ��� �����ؾ��ϹǷ� ���Ұ�
// [���]
// Key �� byte�� �񱳰����� ������ ������ ������ ����


// ����Ʈ�� �� �ڷᱸ���� Ȱ���� Ŭ����
template<typename K, typename T> class MapNode
{
public:
	// ��
	T value;

	// ���� ����� Ű
	// 
	// ���� K ���� �������� ����Ʈ���� �����ϱ����� ũ��񱳰� �����ϵ��� �����͸� ��Ʈ������ ��ȯ
	// ������ > int
	intptr_t key;

	K keyOrg;

	// key�� �������� ū ���� ���
	MapNode* right;

	// key�� �������� ���� ���� ���
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





// ������ ����Ʈ�� ��
template<typename K, typename T> class Map
{
private:
	MapNode<K, T>* root;

public:

	// ���� ���� key����Ʈ �� value����Ʈ  entry - keys, values
	//
	// ������ �Է� �� ������ ���� �Լ������� �Ұ����� ����Ʈ�� ���� �ʿ�
	// 
	// ������ ȿ������ ���� ����.
	// ����Ʈ ���� ���� �Ұ�
	// ����Ʈ�� �ݺ��ϴ� ���� ���� ������ ��� ������ �߻��� �� ����
	Iterable<K> keys;
	Iterable<T> values;

	// ���� key, value�� ����
	int count;

	// ������ ���� ���� ����
	bool isEmpty;

public:
	Map() {
		root = NULL;
		count = 0;
	}
	~Map() { clear(); }

private:
	// ������ �ؽ�Ű �� ����Ž�� �� ������ ������ �ڷ������� ��ȯ �۾�
	// (int)&key ������ ������ ���� ���� Ű ���� �õ�
	// 
	// [����]
	// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
	// https://stackoverflow.com/questions/14446183/implementing-a-hashmap-in-c-hashing-function-for-templated-data-type
	intptr_t hasing(K key)
	{
		//cout << std::hash<K>()(key) << endl;

		// [����]
		// Map<String, String> map; ������
		// map["key"] = "test"; �� ���� �Ҵ��� �õ��� ��� �Ʒ� ���ο��� ������ ��ȯ
		// 
		// [���� C2064]
		// ���� 1���� �μ��� �޾Ƶ��̴� �Լ��� ������ �ʽ��ϴ�. ConsoleApplication1 C : \Users\TaeGi\Downloads\map.cpp 85 
		//
		// [���� ���� ���ɼ�]
		// [] = �����ڸ� ���� String class ���Խ� Key class�� �������� ���� ���¿��� hash �Լ��� ȣ�� - �μ� ����
		return std::hash<K>()(key);
	}

	// ����Ʈ�� Ž�� �Լ� ��Ȱ��ȭ
	// 
	// 
	// ����Ʈ�� ��� �߰� ����Լ�
	bool InsertNode(MapNode<K, T>* tree, MapNode<K, T>* node)
	{
		// ���� ��� �ܰ迡���� Ʈ���� ��Ʈ�� ũ�� �� (����Ʈ���� ��Ʈ)
		// ũ��񱳰� ������ Ű���� ���� ũ��� �� ������ ����
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
		// ���� ���� ��� ����ó��
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
	// Key, Value �� �߰�
	T& add(K key, T item)
	{
		MapNode<K, T>* data = new MapNode<K, T>(hasing(key), key, item, NULL, NULL);

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

		// = �� ���� �� ���� ����
		// 
		// ��û�� Ű�� ���� NULL�� ��� ��� �űԻ��� �� ����
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



	// [] �迭 ������ �������̵� 
	// 
	// 
	// [] = �� �Բ� �������ؼ��� ��ȯ�Ǵ� Ŭ���� �Ǵ� �ڷ����� = ������ �����ε��� �����ؾ���
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