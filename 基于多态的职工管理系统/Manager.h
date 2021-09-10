#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Worker.h"

class Manager :public Worker
{
public:
	//构造函数
	Manager(int id, string name, int did);

	//显示个人信息
	virtual void showInfo();

	//获取职工岗位名称
	virtual string getDeptName();

};