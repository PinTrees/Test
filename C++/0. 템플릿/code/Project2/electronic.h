#pragma once
#include "product.h"


class Electronic : public Product {
private:
	String modelUid;

public:
    Electronic() {}

	Electronic(String _name, int _price, String _modelUid) : Product(_name, _price) {
		modelUid = _modelUid;
	}
	virtual ~Electronic() {

	}

	void	SetModelUID(String u)	{ modelUid = u; }
	String	GetModelUID()			{ return modelUid; }


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
		modelUid = splits[2];

		return this;
	}


	/**
	* Serialization
	*
	* 이 함수는 해당 클래스를 직렬화한 문자열을 반환합니다.
	*/
	String* ToSaveFormat() override  {
		String saveText = "";
		saveText += GetName();
		saveText += ",";
		saveText += ToString(GetPrice());
		saveText += ",";
		saveText += modelUid;
		saveText += ",";

		return new String(saveText);
	}


	/**
	* 이 함수는 객체의 상품의 정보를 출력합니다.
	*/
	void Print() override {
		cout << "이름: " << GetName() << endl;
		cout << "가격: " << GetPrice() << "원" << endl;
		cout << "모델명: " << GetModelUID() << endl;
		cout << endl;
	}
};