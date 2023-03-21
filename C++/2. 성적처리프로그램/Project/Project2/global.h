#pragma once
#include <ostream>
#include "string.h"

using namespace std;

#define ARRAY_LEN(X) (sizeof(X)/sizeof(X[0]))
#define SAFE_DELETE(a) if(a != nullptr) { delete a; }
#define SAFE_ARRAY_DELETE(a) if(a != nullptr) { delete[] a; }