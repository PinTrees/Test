#pragma once
#include "list.h"
#include "goods.h"
#include "SubManager.h"
#include "console.h"

// �ּ� cpp ����

class GoodsManager : public IManager {
private:
    GoodsManager(const GoodsManager& ref) {}
    GoodsManager& operator=(const GoodsManager& ref) {}
    GoodsManager() {}
    ~GoodsManager() {}

    List<Goods*>* products;
    String fileName = "product-goods.xxx";

public:
    static GoodsManager& Instance() {
        static GoodsManager s;
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