#include "CManager.h"

CManager::CManager()
{
	mUserLst = nullptr;
}

CManager::~CManager()
{
	CNode<CUser*>* node = mUserLst->GetmHead()->GetmNext();
	
	while (node)
	{
		if (node->GetmData() != nullptr)
		{
			delete node->GetmData();
		}

		node = node->GetmNext();
	}

	delete mUserLst;
}

void CManager::Init()
{
	mUserLst = new CLinkedList<CUser*>();
}

void CManager::Run()
{
	Init();

	while (1)
	{
		bool endflag = false;		

		MAIN_MENU select = MainMenu();

		switch (select)
		{
		case MAIN_MENU::JOIN:
			Join();
			break;
		case MAIN_MENU::LOGIN:
			if (Login())
			{
				LOGIN_MENU select = LoginMenu();

				switch (select)
				{
				case LOGIN_MENU::LOGOUT:
					mNowUser->SetLogout();
					break;
				case LOGIN_MENU::DROP:
					Drop();
					break;
				}
			}			
			break;
		case MAIN_MENU::EXIT:
			endflag = true;
			break;
		default:
			cout << "잘못입력했습니다" << endl;
			continue;
		}

		if (endflag)
		{
			break;
		}
	}

	
}

bool CManager::Join()
{
	char id[10];
	char pw[10];

	cout << "ID:";
	cin >> id;

	bool flag = false;
	
	CNode<CUser*>* node = mUserLst->GetmHead()->GetmNext();

	while (node)
	{
		if (strcmp(node->GetmData()->GetId(), id)==0)
		{
			flag = true;
			break;
		}
		node = node->GetmNext();
	}

	if (flag)
	{
		cout << "이미 존재하는 아이디입니다" << endl;
		return false;
	}

	cout << "PW:";
	cin >> pw;

	mUserLst->Insert(new CUser(id, pw));

	return true;

}

bool CManager::Login()
{
	char id[10];
	char pw[10];


	cout << "ID:";
	cin >> id;

	bool flag = false;

	CNode<CUser*>* node = mUserLst->GetmHead()->GetmNext();

	while (node)
	{
		if (strcmp(node->GetmData()->GetId(), id) == 0)
		{
			flag = true;
			break;
		}
		node = node->GetmNext();
	}	

	if (!flag)
	{
		cout << "없는 아이디입니다" << endl;
		return false;
	}

	cout << "PW:";
	cin >> pw;

	if(strcmp(node->GetmData()->GetPw(), pw)!=0)
	{
		cout << "패스워드가 틀렸습니다" << endl;
		return false;
	}

	mNowUser = node->GetmData();

	return true;

}

MAIN_MENU CManager::MainMenu()
{
	MAIN_MENU select;	

	while (1)
	{
		cout << "<메뉴>" << endl;
		cout << "1.회원가입" << endl;
		cout << "2.로그인" << endl;
		cout << "3.종료" << endl;
		cout << "선택:";


		cin >> select;

		if (select < MAIN_MENU::JOIN || select>MAIN_MENU::EXIT)
		{
			cout << "잘못입력했습니다" << endl;
			continue;
		}
		break;
	}

	return select;
}

LOGIN_MENU CManager::LoginMenu()
{
	LOGIN_MENU select;

	while (1)
	{		
		cout << "<메뉴>" << endl;
		cout << "1.로그아웃" << endl;
		cout << "2.회원탈퇴" << endl;	
		cout << "선택:";

		
		cin >> select;

		if (select< LOGIN_MENU::LOGOUT || select>LOGIN_MENU::DROP)
		{
			cout << "잘못입력했습니다" << endl;
			continue;
		}
		break;
	}

	return select;
	
}

void CManager::Logout()
{
	mNowUser->SetLogout();
}

void CManager::Drop()
{
	if (mNowUser != nullptr)
	{
		mUserLst->Delete(mNowUser);
		delete mNowUser;
		mNowUser = nullptr;
	}
}