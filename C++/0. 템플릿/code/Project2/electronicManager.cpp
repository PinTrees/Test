#pragma once
#include "electronicManager.h"

/**
* �� �Լ��� ���Ͽ� ��ϵ� ������ �а� ��ǰ��Ͽ� �߰��մϴ�
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
* �� �Լ��� �ű� ��ǰ�� �����ϰ� ��ǰ��Ͽ� �߰��մϴ�.
* 
* ����ڰ� �Է��� ������ ���� ��ǰ�� �����մϴ�.
* ������ ��ǰ�� ��ǰ��Ͽ� �߰��մϴ�.
*/
void ElectronicManager::Input() {
    system("cls");
    cout << "�߰��� ��ǰ �ۼ�" << endl << endl;

    String name = ConsoleReadLine("�̸�");
    String modelUid = ConsoleReadLine("�𵨸�");
    String price = ConsoleReadLine("����");

    products->Add(new Electronic(name, ToInt(price), modelUid));
}


/**
* �� �Լ��� ���� ��ǰ����� ����մϴ�.
* 
* ����� ��ǰ����� ��� ����մϴ�.
*/
void ElectronicManager::Print() {
    system("cls");
    cout << "��ǰ ���" << endl << endl;

    products->ForEach([&](Electronic* p) { p->Print(); });
}

/**
* �� �Լ��� ����� ��ǰ����� ���Ͽ� �����մϴ�.
* 
* ����� ��ǰ��� ��ü�� ����ȭ �� ���ڿ��� �����Ͽ� ���Ͽ� ���ڿ��� �����մϴ�.
* ���� ���� ���θ� ��ȯ�մϴ�.
* 
* ��ȯ
*   bool: ���� ������ true ��ȯ
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
* �� �Լ��� ����� Ư�����ڿ��� ��ǰ��ϵ��� �̸� �Ǵ� Ư�� ���� ���� ���θ� Ȯ���մϴ�.
* 
* �Ķ����
*   String searchText: ���� ���ڿ��Դϴ�.
* 
* ��ȯ
*   List<Product*>*: ��ǰ����� �񱳹��ڿ��� ���ԵǴ� ��ǰ���
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