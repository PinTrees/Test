#pragma once
#include "list.h"
#include "product.h"
#include "fileManager.h"

class IManager {

public:
	virtual void Print() = 0;
	virtual void Input() = 0;
	virtual bool Save() = 0;
	virtual List<Product*>* Search(String searchText) = 0;
};
