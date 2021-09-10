#pragma once
#include <iostream>
using namespace std;
#include <string>

class Worker
{
public:
	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;

	int m_id;  //职工编号
	string m_name;  //职工姓名
	int m_deptid;  // 职工部门编号
};