#pragma once
#include "global.h"
#include "string.h"
#include "list.h"
#include "menu.h"



class Product {
private:
	String uid;
	String name;

	int price;

public:
	Product();
	Product(String name, String uid, char* type);
	Product(String _name, int _price) {
		name = _name;
		price = _price;
	}
	virtual ~Product();


	void	SetName(String n)	{ name = n; }
	String	GetName()			{ return name; }

	void	SetPrice(int p)		{ price = p; }
	int		GetPrice()			{ return price; }

	void	SetUid(String u)	{ uid = u; }
	String	GetUid()			{ return uid; }


	/** �� �����Լ��� ��� ��ü�� ����ȭ �� ������ȭ�� ó���ϱ����� ���������Լ��Դϴ�. */
	virtual Product* FromDatabase(String data) = 0;
	virtual String*	 ToSaveFormat() = 0;

	/** �� �����Լ��� ��� ��ü�� ����� ó���ϱ� ���� ���������Լ� �Դϴ�. */
	virtual void Print() = 0;
};