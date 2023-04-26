#include "fileManager.h"


/**
* 이 함수는 경로에 저장된 파일의 정보를 문자열로 반환합니다.
*
* 파라미터
*	String filePath: 파일이 저장될 경로입니다.
*	String fileName: 저장할 파일의 이름입니다.
*
* 반환
*	String*: 파일에 기록된 정보를 문자열로 반환합니다.
*			 파일이 없을경우 nullptr을 반환합니다.
*			 파일의 기록이 없을경우 빈 문자열을 반환합니다.
*/
String* FileIO::ReadAsString(String* filePath, String fileName) {
	ifstream file;

	if (filePath != nullptr) {
		String path = *filePath + "/";
		path += fileName;
		file.open(path.characters);
	}
	else file.open(fileName.characters);

	if (!file.is_open()) return nullptr;

	stringstream fileStringStream;
	fileStringStream << file.rdbuf();

	String* filedata = new String(&*fileStringStream.str().c_str());

	return filedata;
}



/**
* 이 함수는 파일의 정보를 받아 저장하고 작업 성공 여부를 반환합니다.
*
* 파라미터
*	String filePath: 파일이 저장될 경로입니다.
*	String fileName: 저장할 파일의 이름입니다.
*	String fileData: 저장할 파일의 문자열 정보입니다.
*
* 반환
*	bool: 파일 저장 성공여부를 반환합니다.
*/
bool FileIO::Save(String* filePath, String fileName, String filedata) {
	ofstream file;

	if (filePath != nullptr) {
		String path = *filePath + "/";
		path += fileName;
		file.open(path.characters);
	}
	else file.open(fileName.characters);


	if (file.is_open())
	{ 
		file << filedata.characters;
		file.close();
	}
	else {
		cout << "error" << endl;
		return false;
	}

	return true;
}