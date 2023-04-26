#include "manager.h"


// UI�� ��� - ����Ʈ �Լ�

MainManager::MainManager() {
}
MainManager::~MainManager() {
	delete menu;
}

/**
* �� �Լ��� �� �Ŵ��� �̱��� Ŭ������ �ʱ�ȭ �մϴ�.
*/
void MainManager::Init()
{
	GoodsManager::Instance().Init();
	ClothesManager::Instance().Init();
	ElectronicManager::Instance().Init();

	menu = new Menu();
	menu->Init();
}


/**
* �� �Լ��� ���� ���� ������ �����մϴ�.
*/
void MainManager::Run() {
	while (true) {
		int selectInt = ToInt(menu->MainMenu());

		if (selectInt == (int)MAINMENU::Inupt) {
			InputProduct();
		}
		else if (selectInt == (int)MAINMENU::Print) {
			PrintProduct();
		}
		else if (selectInt == (int)MAINMENU::Search) {
			SearchProduct();
		}
		else if (selectInt == (int)MAINMENU::Save) {
			SaveProduct();
		}
		else if (selectInt == (int)MAINMENU::Exit){
			break;
		}
	}
	return;
}


/**
* �� �Լ��� �� ��Ŭ�� Ŭ������ �����մϴ�.
*/
void MainManager::Dispose() {
	GoodsManager::Instance().Dispose();
	ClothesManager::Instance().Dispose();
	ElectronicManager::Instance().Dispose();
}


/**
* �� �Լ��� ��� �Ŵ����� ��ǰ��� �����Լ��� �����մϴ�.
*/
void MainManager::SaveProduct() {
	ConsoleClear();

	GoodsManager::Instance().Save();
	ClothesManager::Instance().Save();
	ElectronicManager::Instance().Save();

	system("PAUSE");
}


/**
* �� �Լ��� �� �Ŵ����� ��ǰ��� �Լ��� �����մϴ�.
*/
void MainManager::PrintProduct() { 
	GetProductManager(menu->PrintMenu())->Print();
	system("PAUSE");
}


/**
* �� �Լ��� �� �Ŵ����� ��ǰ���� �Լ��� �����մϴ�.
*/
void MainManager::InputProduct() {
	GetProductManager(menu->InputMenu())->Input();
}


/**
* �� �Լ��� ��� �Ŵ����� ��ǰ�˻��Լ��� �����մϴ�.
* 
* �˻��Ϸ�� ��ǰ����� ����մϴ�.
*/
void MainManager::SearchProduct()
{
	ConsoleClear();
	cout << "��ǰ �˻�" << endl << endl;
	String input = ConsoleReadLine("�˻���");

	List<Product*>* goodsList = GoodsManager::Instance().Search(input);
	List<Product*>* clothesList = ClothesManager::Instance().Search(input);
	List<Product*>* electronList = ElectronicManager::Instance().Search(input);

	ConsoleClear();
	cout << "[��ǰ ���] " << goodsList->count  << "��" << endl << endl;
	goodsList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	cout << "[�Ƿ� ���] " << clothesList->count << "��" << endl << endl;
	clothesList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	cout << "[���� ���] " << electronList->count << "��" << endl << endl;
	electronList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	system("PAUSE");
}



/**
* �� �Լ��� �Էµ� �ڵ忡 �ش��ϴ� ��ǰ�Ŵ����� ��ȯ�մϴ�.
*
* �Ķ����
*	String code: ��ǰ�Ŵ����� �з� �ڵ�
*
* ��ȯ
*	IManager*: �ڵ�� ��ġ�ϴ� ��ǰ�Ŵ���
*/
IManager* MainManager::GetProductManager(String code)
{
	int sel = ToInt(code);
	if		(sel == 1)	return (IManager*)&GoodsManager::Instance();
	else if (sel == 2)	return (IManager*)&ClothesManager::Instance();
	else				return (IManager*)&ElectronicManager::Instance();
}