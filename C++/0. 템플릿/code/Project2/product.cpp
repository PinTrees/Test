#pragma once
#include "product.h"

Product::Product() 
{
}
Product::~Product()
{
	//SAFE_ARRAY_DELETE(scores);
}
Product::Product(String _name, String _uid, char* _type) {
	name = _name;
	uid = _uid;
}
