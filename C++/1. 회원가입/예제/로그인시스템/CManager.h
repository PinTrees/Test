#ifndef CMANAGER_H
#define CMANAGER_H

#include "Global.h"
#include "CUser.h"

class CManager
{
private:
	CLinkedList<CUser*>*   mUserLst;
	CUser*		mNowUser;

public:
	CManager();
	~CManager();

	void Run();
	void Init();
	bool Join();
	bool Login();
	LOGIN_MENU LoginMenu();
	MAIN_MENU MainMenu();
	void Logout();
	void Drop();
	
};
#endif

