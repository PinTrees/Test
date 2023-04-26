#pragma once
#include "clothesManager.h"


// subManager.cpp�� ���ǵ�

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
    cout << "�߰��� ��ǰ �ۼ�" << endl << endl;

    String name = ConsoleReadLine("�̸�");
    String size = ConsoleReadLine("������");
    String price = ConsoleReadLine("����");

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
    cout << "��ǰ ���" << endl << endl;

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