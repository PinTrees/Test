#pragma once
#include "goodsManager.h"


/**
* �� �Լ��� ���Ͽ� ��ϵ� ������ �а� ��ǰ��Ͽ� �߰��մϴ�
*/
void GoodsManager::Init() {
    products = new List<Goods*>();

    String* data = FileIO::Instance().ReadAsString(nullptr, fileName);
    if (data == nullptr) return;
    if (data->length < 3) return;

    List<String*>* splits = data->Split(';');

    splits->ForEach([&](String* str) {
        Goods* p = new Goods();
        products->Add((Goods*)p->FromDatabase(*str));
    });
}
void GoodsManager::Dispose() {
    delete products;
}


/**
* �� �Լ��� �ű� ��ǰ�� �����ϰ� ��ǰ��Ͽ� �߰��մϴ�.
*
* ����ڰ� �Է��� ������ ���� ��ǰ�� �����մϴ�.
* ������ ��ǰ�� ��ǰ��Ͽ� �߰��մϴ�.
*/
void GoodsManager::Input() {
    system("cls");
    cout << "�߰��� ��ǰ �ۼ�" << endl << endl;

    String name = ConsoleReadLine("�̸�");
    String weight = ConsoleReadLine("����");;
    String price = ConsoleReadLine("����");;

    products->Add(new Goods(name, ToInt(price), ToInt(weight)));
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
bool GoodsManager::Save() {
    String saveText = "";
    products->ForEach([&](Goods* p) {
        saveText += p->ToSaveFormat();
        saveText += ";\n";
    });

    cout << "goods" << endl << saveText << endl << endl;

    return FileIO::Instance().Save(nullptr, fileName, saveText);
}


/**
* �� �Լ��� ���� ��ǰ����� ����մϴ�.
*
* ����� ��ǰ����� ��� ����մϴ�.
*/
void GoodsManager::Print() {
    system("cls");
    cout << "��ǰ ���" << endl << endl;

    products->ForEach([&](Goods* p) { p->Print(); });
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
List<Product*>* GoodsManager::Search(String searchText) {
    List<Product*>* searchList = new List<Product*>();

    products->ForEach([&](Goods* p) {
        if (p->GetName().Contain(&searchText)) {
            searchList->Add((Product*)p);
        }
    });

    return searchList;
}