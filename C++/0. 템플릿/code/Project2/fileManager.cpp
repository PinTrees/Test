#include "fileManager.h"


/**
* �� �Լ��� ��ο� ����� ������ ������ ���ڿ��� ��ȯ�մϴ�.
*
* �Ķ����
*	String filePath: ������ ����� ����Դϴ�.
*	String fileName: ������ ������ �̸��Դϴ�.
*
* ��ȯ
*	String*: ���Ͽ� ��ϵ� ������ ���ڿ��� ��ȯ�մϴ�.
*			 ������ ������� nullptr�� ��ȯ�մϴ�.
*			 ������ ����� ������� �� ���ڿ��� ��ȯ�մϴ�.
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
* �� �Լ��� ������ ������ �޾� �����ϰ� �۾� ���� ���θ� ��ȯ�մϴ�.
*
* �Ķ����
*	String filePath: ������ ����� ����Դϴ�.
*	String fileName: ������ ������ �̸��Դϴ�.
*	String fileData: ������ ������ ���ڿ� �����Դϴ�.
*
* ��ȯ
*	bool: ���� ���� �������θ� ��ȯ�մϴ�.
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