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
	* �� �Լ��� ToSaveFormat()�� ���� ����ȭ�� ���ڿ��� �ش� Ŭ������ ������ȭ �մϴ�.
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
	* �� �Լ��� �ش� Ŭ������ ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	* 
	* ����ȭ ����
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
	* �� �Լ��� ��ü�� ��ǰ�� ������ ����մϴ�.
	*/
	void Print() override {
		cout << "�̸�: " << GetName() << endl;
		cout << "����: " << GetPrice() << "��" << endl;
		cout << "������: " << GetSize() << endl;
		cout << endl;
	}
};

