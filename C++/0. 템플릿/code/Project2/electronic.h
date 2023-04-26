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
	* �� �Լ��� ToSaveFormat()�� ���� ����ȭ�� ���ڿ��� �ش� Ŭ������ ������ȭ �մϴ�.
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
	* �� �Լ��� �ش� Ŭ������ ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
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
	* �� �Լ��� ��ü�� ��ǰ�� ������ ����մϴ�.
	*/
	void Print() override {
		cout << "�̸�: " << GetName() << endl;
		cout << "����: " << GetPrice() << "��" << endl;
		cout << "�𵨸�: " << GetModelUID() << endl;
		cout << endl;
	}
};