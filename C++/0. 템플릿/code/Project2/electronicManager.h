#pragma once
#include "list.h"
#include "electronic.h"
#include "SubManager.h"
#include "console.h"

class ElectronicManager : public IManager {
private:
    ElectronicManager(const ElectronicManager& ref) {}
    ElectronicManager& operator=(const ElectronicManager& ref) {}
    ElectronicManager() {}
    ~ElectronicManager() {}

    List<Electronic*>* products;
    String             fileName = "product-electronic.xxx";

public:
    static ElectronicManager& Instance() {
        static ElectronicManager s;
        return s;
    }

    void Init();
    void Dispose();

    /** �� �Լ��� ��ǰ�� �߰��ϰ� ��Ͽ� �����մϴ�. */
    void Input() override;

    /** �� �Լ��� ����� ��ǰ����� ��� ����մϴ�. */
    void Print() override;

    /** �� �Լ��� ����� ��ǰ����� ���Ͽ� ����մϴ�. */
    bool Save() override;

    /** �� �Լ��� ����� ��Ͽ��� �Է¹��� ���ڿ��� �˻��� �� ����� ��ȯ�մϴ�. */
    List<Product*>* Search(String searchText) override;
};