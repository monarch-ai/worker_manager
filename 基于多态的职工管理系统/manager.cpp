#include <iostream>
using namespace std;
#include "Manager.h"

//���캯��
Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << " Ա����ţ� " << this->m_id
		<< " \tԱ����������" << this->m_name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ������ϰ彻��������,���·������Ա��" << endl;
}

//��ȡְ����λ����
string Manager::getDeptName()
{
	return string("����");  //char*����ת����������stringҲ�����ǿ������ת��
}