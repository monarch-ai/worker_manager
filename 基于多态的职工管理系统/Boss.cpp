#include <iostream>
using namespace std;
#include "Boss.h"

//���캯��
Boss::Boss(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << " Ա����ţ� " << this->m_id
		<< " \tԱ����������" << this->m_name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ�𣺹���˾��������" << endl;
}

//��ȡְ����λ����
string Boss::getDeptName()
{
	return string("�ϰ�");  //char*����ת����������stringҲ�����ǿ������ת��
}