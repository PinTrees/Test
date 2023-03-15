#ifndef  GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include "LinkedList.h"
using namespace std;

enum class MAIN_MENU 
{ 
	JOIN=1, 
	LOGIN, 
	EXIT
};

enum class LOGIN_MENU 
{
	LOGOUT=1,
	DROP
};

istream& operator>>(istream& i, MAIN_MENU& input);

istream& operator>>(istream& i, LOGIN_MENU& input);


#endif // ! _GLOBAL_H
