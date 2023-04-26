#pragma once
#include "list.h"
#include "clothes.h"
#include "SubManager.h"
#include "console.h"

class ClothesManager : public IManager {
private:
    ClothesManager() {}
    ~ClothesManager() {}
    ClothesManager(const ClothesManager& ref) {}
    ClothesManager& operator=(const ClothesManager& ref) {}

    List<Clothes*>*     products;
    String              fileName = "product-clothes.xxx";

public:
    static ClothesManager& Instance() {
        static ClothesManager s;
        return s;
    }

    void Init();
    void Dispose() {
        delete products;
    }


    /** �� �Լ��� ��ǰ�� �߰��ϰ� ��Ͽ� �����մϴ�. */
    void Input() override;

    /** �� �Լ��� ����� ��ǰ����� ��� ����մϴ�. */
    void Print() override;

    /** �� �Լ��� ����� ��ǰ����� ���Ͽ� ����մϴ�. */
    bool Save() override;

    /** �� �Լ��� ����� ��Ͽ��� �Է¹��� ���ڿ��� �˻��� �� ����� ��ȯ�մϴ�. */
    List<Product*>* Search(String searchText) override;
};