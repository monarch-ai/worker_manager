#include <iostream>
using namespace std;
#include "Employee.h"

//���캯��
Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

//��ʾ������Ϣ
void Employee::showInfo()
{
	cout<<" Ա����ţ� "<<this->m_id
		<<" \tԱ����������" << this->m_name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ����ɾ�����������" << endl;
}

//��ȡְ����λ����
string Employee::getDeptName()
{
	return string("Ա��");  //char*����ת����������stringҲ�����ǿ������ת��
}