#include <iostream>
using namespace std;
#include "Manager.h"

//构造函数
Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}

//显示个人信息
void Manager::showInfo()
{
	cout << " 员工编号： " << this->m_id
		<< " \t员工姓名：　" << this->m_name
		<< " \t岗位：" << this->getDeptName()
		<< " \t岗位职责：完成老板交给的任务,并下发任务给员工" << endl;
}

//获取职工岗位名称
string Manager::getDeptName()
{
	return string("经理");  //char*类型转换，若不加string也会进行强制类型转换
}