#pragma once
#include <iostream>
#include "manager.h"
#include "list.h"
#include "global.h"
#include "string.h"
#include "list.h"

// �޴�
// ���� �Է�
// ���� ��ȸ
// ���� ���
// ����
// 
// 
// 
// 
// 
// ���� �Է�
// �а�����
// �������α׷���
// ���ӱ�ȹ
// 
// �̸� 
// �й�
// 
// ���� ����Ʈ 3����
// ���� ���
// ����: ���� �Է�
// 
// 
// 
// 
// 
// 
// ������ȸ
// �й� - �̸�   
// 
// �̸����� �˻��� ��� �������� �߻�
// ����Ʈ�� ��� �ʿ�
// 
// 
// 
// 
// 
// ���� ���
// 1. �а�����
// 2. ��ü���
// 
// ��� ���� ���
// �й� �̸� ���� ����Ʈ ����
// 
// 
//

 
int main()   
{
    Manager* manager = new Manager();
    manager->Init();
    manager->Run();

    //std::cout << "Hello World!\n";
}
