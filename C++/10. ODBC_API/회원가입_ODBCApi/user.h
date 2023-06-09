#pragma once


class UserData {
public:
	TCHAR* id;
	TCHAR* pw;
	TCHAR* name;

	UserData(TCHAR* _id, TCHAR* _pw, TCHAR* _name) {
		id = _id;
		pw = _pw;
		name = _name;
	}
};
