#include "manager.h"


// UI는 상속 - 프린트 함수

MainManager::MainManager() {
}
MainManager::~MainManager() {
	delete menu;
}

/**
* 이 함수는 각 매니저 싱글톤 클래스를 초기화 합니다.
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
* 이 함수는 메인 실행 로직을 수행합니다.
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
* 이 함수는 각 싱클톤 클래스를 제거합니다.
*/
void MainManager::Dispose() {
	GoodsManager::Instance().Dispose();
	ClothesManager::Instance().Dispose();
	ElectronicManager::Instance().Dispose();
}


/**
* 이 함수는 모든 매니저의 상품목록 저장함수를 연결합니다.
*/
void MainManager::SaveProduct() {
	ConsoleClear();

	GoodsManager::Instance().Save();
	ClothesManager::Instance().Save();
	ElectronicManager::Instance().Save();

	system("PAUSE");
}


/**
* 이 함수는 각 매니저의 상품출력 함수를 연결합니다.
*/
void MainManager::PrintProduct() { 
	GetProductManager(menu->PrintMenu())->Print();
	system("PAUSE");
}


/**
* 이 함수는 각 매니저의 상품저장 함수를 연결합니다.
*/
void MainManager::InputProduct() {
	GetProductManager(menu->InputMenu())->Input();
}


/**
* 이 함수는 모든 매니저의 상품검색함수를 연결합니다.
* 
* 검색완료된 상품목록을 출력합니다.
*/
void MainManager::SearchProduct()
{
	ConsoleClear();
	cout << "상품 검색" << endl << endl;
	String input = ConsoleReadLine("검색어");

	List<Product*>* goodsList = GoodsManager::Instance().Search(input);
	List<Product*>* clothesList = ClothesManager::Instance().Search(input);
	List<Product*>* electronList = ElectronicManager::Instance().Search(input);

	ConsoleClear();
	cout << "[상품 목록] " << goodsList->count  << "개" << endl << endl;
	goodsList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	cout << "[의류 목록] " << clothesList->count << "개" << endl << endl;
	clothesList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	cout << "[가전 목록] " << electronList->count << "개" << endl << endl;
	electronList->ForEach([](Product* p) { p->Print(); });
	cout << endl;

	system("PAUSE");
}



/**
* 이 함수는 입력된 코드에 해당하는 상품매니저를 반환합니다.
*
* 파라미터
*	String code: 상품매니저의 분류 코드
*
* 반환
*	IManager*: 코드상 일치하는 상품매니저
*/
IManager* MainManager::GetProductManager(String code)
{
	int sel = ToInt(code);
	if		(sel == 1)	return (IManager*)&GoodsManager::Instance();
	else if (sel == 2)	return (IManager*)&ClothesManager::Instance();
	else				return (IManager*)&ElectronicManager::Instance();
}