#pragma once
#include "clothesManager.h"


// subManager.cpp에 정의됨

void ClothesManager::Init() {
    products = new List<Clothes*>();
    
    String* data = FileIO::Instance().ReadAsString(nullptr, fileName);
    if (data == nullptr) return;
    if (data->length < 3) return;

    List<String*>* splits = data->Split(';');
    splits->ForEach([&](String* str) {
        Clothes* p = new Clothes();
        products->Add((Clothes*)p->FromDatabase(*str));
    });
}


void ClothesManager::Input() {
    ConsoleClear();
    cout << "추가할 상품 작성" << endl << endl;

    String name = ConsoleReadLine("이름");
    String size = ConsoleReadLine("사이즈");
    String price = ConsoleReadLine("가격");

    products->Add(new Clothes(name, ToInt(price), ToInt(size)));
}

bool ClothesManager::Save() {
    String saveText = "";
    products->ForEach([&](Clothes* p) {
        saveText += p->ToSaveFormat();
        saveText += ";\n";
    });

    cout << "clothes" << endl << saveText << endl << endl;

    return FileIO::Instance().Save(nullptr, fileName, saveText);
}



void ClothesManager::Print() {
    system("cls");
    cout << "상품 출력" << endl << endl;

    products->ForEach([&](Clothes* p) { p->Print(); });
}


List<Product*>* ClothesManager::Search(String searchText) {
    List<Product*>* searchList = new List<Product*>();

    products->ForEach([&](Clothes* p) {
        if (p->GetName().Contain(&searchText)) {
            searchList->Add((Product*)p);
        }
    });

    return searchList;
}