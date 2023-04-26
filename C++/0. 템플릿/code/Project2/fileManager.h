#pragma once
#include <fstream> // ifstream header
#include <iostream>
#include "product.h"
#include "list.h"
#include "stringMap.h"
#include <sstream>

using namespace std;

class FileIO
{
private:
	FileIO(const FileIO& ref) {}
	FileIO& operator=(const FileIO& ref) {}
	FileIO() {}
	~FileIO() {}

public:
	static FileIO& Instance() {
		static FileIO s;
		return s;
	}


	/** �� �Լ��� ��ο� ����� ������ ������ ���ڿ��� ��ȯ�մϴ�. */
	String* ReadAsString	(String* filePath, String fileName);
	
	/** �� �Լ��� ������ ������ �޾� �����ϰ� �۾� ���� ���θ� ��ȯ�մϴ�. */
	bool	Save			(String* filePath, String fileName, String filedata);
};

