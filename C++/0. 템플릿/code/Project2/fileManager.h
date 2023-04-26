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


	/** 이 함수는 경로에 저장된 파일의 정보를 문자열로 반환합니다. */
	String* ReadAsString	(String* filePath, String fileName);
	
	/** 이 함수는 파일의 정보를 받아 저장하고 작업 성공 여부를 반환합니다. */
	bool	Save			(String* filePath, String fileName, String filedata);
};

