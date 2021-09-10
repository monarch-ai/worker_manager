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
	//���캯��
	workerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp( );

	//�ж�ְ���Ƿ����,�����򷵻�λ�ã��������򷵻�-1
	int IsExist(int id);

	//�޸�ְ��
	void  Mod_Emp();

	//����ְ����һ�ְ��ձ�ţ�һ�ְ�������
	void Find_Emp();

	//����Ա�����ѡ������
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~workerManager();
};