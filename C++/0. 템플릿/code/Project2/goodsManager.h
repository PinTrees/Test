#pragma once
#include "list.h"
#include "goods.h"
#include "SubManager.h"
#include "console.h"

// 주석 cpp 포함

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

    /** 이 함수는 상품을 추가하고 목록에 저장합니다. */
    void Input() override;

    /** 이 함수는 저장된 상품목록을 모두 출력합니다. */
    void Print() override;

    /** 이 함수는 저장된 상품목록을 파일에 기록합니다. */
    bool Save() override;

    /** 이 함수는 저장된 목록에서 입력받은 문자열과 검사한 후 결과를 반환합니다. */
    List<Product*>* Search(String searchText) override;
};