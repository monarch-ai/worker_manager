#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

#include <fstream>
#define FILENAME "empFilde.txt"

class workerManager
{
public:
	//构造函数
	workerManager();

	//展示菜单
	void Show_Menu();

	//退出系统
	void exitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker ** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//标志文件是否为空
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp( );

	//判断职工是否存在,存在则返回位置，不存在则返回-1
	int IsExist(int id);

	//修改职工
	void  Mod_Emp();

	//查找职工，一种按照编号，一种按照姓名
	void Find_Emp();

	//按照员工编号选择排序
	void Sort_Emp();

	//清空文件
	void Clean_File();

	//析构函数
	~workerManager();
};