#pragma once
#include "electronicManager.h"

/**
* 이 함수는 파일에 기록된 정보를 읽고 상품목록에 추가합니다
*/
void ElectronicManager::Init() {
    products = new List<Electronic*>();

    String* data = FileIO::Instance().ReadAsString(nullptr, fileName);
    if (data == nullptr) return;
    if (data->length < 3) return;

    List<String*>* splits = data->Split(';');

    splits->ForEach([&](String* str) {
        Electronic* p = new Electronic();
        products->Add((Electronic*)p->FromDatabase(*str));
    });
}
void ElectronicManager::Dispose() {
    delete products;
}



/**
* 이 함수는 신규 상품을 생성하고 상품목록에 추가합니다.
* 
* 사용자가 입력한 정보를 통해 상품을 생성합니다.
* 생성된 상품을 상품목록에 추가합니다.
*/
void ElectronicManager::Input() {
    system("cls");
    cout << "추가할 상품 작성" << endl << endl;

    String name = ConsoleReadLine("이름");
    String modelUid = ConsoleReadLine("모델명");
    String price = ConsoleReadLine("가격");

    products->Add(new Electronic(name, ToInt(price), modelUid));
}


/**
* 이 함수는 현재 상품목록을 출력합니다.
* 
* 저장된 상품목록을 모두 출력합니다.
*/
void ElectronicManager::Print() {
    system("cls");
    cout << "상품 출력" << endl << endl;

    products->ForEach([&](Electronic* p) { p->Print(); });
}

/**
* 이 함수는 저장된 상품목록을 파일에 저장합니다.
* 
* 저장된 상품목록 객체를 직렬화 후 문자열로 변경하여 파일에 문자열로 저장합니다.
* 저장 성공 여부를 반환합니다.
* 
* 반환
*   bool: 저장 성공시 true 반환
*/
bool ElectronicManager::Save() {
    String saveText = "";
    products->ForEach([&](Electronic* p) {
        saveText += p->ToSaveFormat();
        saveText += ";\n";
    });

    cout << "electronic" << endl << saveText << endl << endl;

    return FileIO::Instance().Save(nullptr, fileName, saveText);
}


/**
* 이 함수는 저장된 특정문자열과 상품목록들의 이름 또는 특정 값과 포함 여부를 확인합니다.
* 
* 파라미터
*   String searchText: 비교할 문자열입니다.
* 
* 반환
*   List<Product*>*: 상품목록중 비교문자열이 포함되는 상품목록
*/
List<Product*>* ElectronicManager::Search(String searchText) {
    List<Product*>* searchList = new List<Product*>();

    products->ForEach([&](Electronic* p) {
        if (p->GetName().Contain(&searchText)
        || p->GetModelUID().Contain(&searchText)) {
            searchList->Add((Product*)p);
        }
    });
     
    return searchList;
}