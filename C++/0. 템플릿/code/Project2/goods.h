#pragma once
#include "product.h"

class Goods : public Product {
private:
	int weight;

public:
	Goods() {}
	Goods(String _name, int _price, int _weight) : Product(_name, _price) {
		weight = _weight;
	}
	virtual ~Goods() {
	}

	void	SetWeight(int u) { weight = u; }
	int		GetWeight() { return weight; }


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
		weight = ToInt(splits[2]);

		return this;
	}


	/**
	* Serialization
	*
	* �� �Լ��� �ش� Ŭ������ ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	*/
	String* ToSaveFormat() override {
		String saveText = "";
		saveText += GetName();
		saveText += ",";
		saveText += ToString(GetPrice());
		saveText += ",";
		saveText += ToString(weight);
		saveText += ",";

		return new String(saveText);
	}


	/**
	* �� �Լ��� ��ü�� ��ǰ�� ������ ����մϴ�.
	*/
	void Print() override {
		cout << "�̸�: " << GetName() << endl;
		cout << "����: " << GetPrice() << "��" << endl;
		cout << "����: " << GetWeight() << endl;
		cout << endl;
	}
};
