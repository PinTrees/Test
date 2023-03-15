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
			cout << "�߸��Է��߽��ϴ�" << endl;
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
		cout << "�̹� �����ϴ� ���̵��Դϴ�" << endl;
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
		cout << "���� ���̵��Դϴ�" << endl;
		return false;
	}

	cout << "PW:";
	cin >> pw;

	if(strcmp(node->GetmData()->GetPw(), pw)!=0)
	{
		cout << "�н����尡 Ʋ�Ƚ��ϴ�" << endl;
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
		cout << "<�޴�>" << endl;
		cout << "1.ȸ������" << endl;
		cout << "2.�α���" << endl;
		cout << "3.����" << endl;
		cout << "����:";


		cin >> select;

		if (select < MAIN_MENU::JOIN || select>MAIN_MENU::EXIT)
		{
			cout << "�߸��Է��߽��ϴ�" << endl;
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
		cout << "<�޴�>" << endl;
		cout << "1.�α׾ƿ�" << endl;
		cout << "2.ȸ��Ż��" << endl;	
		cout << "����:";

		
		cin >> select;

		if (select< LOGIN_MENU::LOGOUT || select>LOGIN_MENU::DROP)
		{
			cout << "�߸��Է��߽��ϴ�" << endl;
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