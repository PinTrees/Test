#pragma once
#include "product.h"


class Clothes : public Product {
private:
	int size;

public:
	Clothes() {
	}
	Clothes(String _name, int _price, int _size) : Product(_name, _price) {
		size = _size;
	}
	virtual ~Clothes() {

	}

	void	SetSize(int u) { size = u; }
	int		GetSize() { return size; }


	/**
	* Deserialization
	* 
	* 이 함수는 ToSaveFormat()에 의해 직렬화된 문자열을 해당 클래스로 역직렬화 합니다.
	*/
	Product* FromDatabase(String data) override {
		if (data.length < 3) return nullptr;

		List<String*> splits = (*data.Trim()->Split(','));

		SetName(*splits[0]);
		SetPrice(ToInt(splits[1]));
		size = ToInt(splits[2]);

		return this;
	}


	/**
	* Serialization
	* 
	* 이 함수는 해당 클래스를 직렬화한 문자열을 반환합니다.
	* 
	* 직렬화 형식
	*	"data1,data2,data3,data4,"
	*/
	String* ToSaveFormat() override {
		String saveText = "";
		saveText += GetName();
		saveText += ",";
		saveText += ToString(GetPrice());
		saveText += ",";
		saveText += ToString(size);
		saveText += ",";

		return new String(saveText);
	}


	/**
	* 이 함수는 객체의 상품의 정보를 출력합니다.
	*/
	void Print() override {
		cout << "이름: " << GetName() << endl;
		cout << "가격: " << GetPrice() << "원" << endl;
		cout << "사이즈: " << GetSize() << endl;
		cout << endl;
	}
};

