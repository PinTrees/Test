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


	/** 이 가상함수는 상속 객체의 직렬화 및 역직렬화를 처리하기위한 순수가상함수입니다. */
	virtual Product* FromDatabase(String data) = 0;
	virtual String*	 ToSaveFormat() = 0;

	/** 이 가상함수는 상속 객체의 출력을 처리하기 위한 순수가상함수 입니다. */
	virtual void Print() = 0;
};