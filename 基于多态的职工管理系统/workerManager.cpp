#include "workerManager.h"

workerManager::workerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		return;
	}

	//2、文件存在，且无记录
	char ch;
	ifs >> ch; //向后读一个字符
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		return;
	}

	//3、当文件存在，且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据,存到数组中
	this->init_Emp();
}

void workerManager::Show_Menu() 
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void workerManager::exitSystem()
{
	cout << "欢迎您再次使用" << endl;
	system("pause");
	exit(0); //强制退出
}

void workerManager::Add_Emp()
{
	cout << "请输入添加职工数量" << endl;

	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下的内容存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect; //部门选择

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;

	    //更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新文件是否为空
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}

	//清屏
	system("pause");
	system("cls");
		
}

void workerManager::save()
{
	//写文件
	ofstream ofs;
	ofs.open(FILENAME, ios::out);


	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}

	ofs.close();
}

int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) //读完一行数据
	{
		num++;
	}
	return num;
}

void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker * worker= NULL;

		if (did == 1)  // 1普通员工
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2) //2经理
		{
			worker = new Manager(id, name, did);
		}
		else //总裁
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

void workerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i=0; i < this->m_EmpNum; i++) //这个this可加可不加
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//判断职工是否存在
int workerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
//数组删除的本质是后面的前移一个
void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员的个数

			//数据同步更新到文件
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "未找到该职工" << endl;
		}
	}

	//清屏
	system("pause");
	system("cls");
}



void  workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工编号" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新的职工号：" << endl;
			cin >> newid;

			cout << "请输入新姓名： " << endl;
			cin >> newname;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case1:
				worker = new Employee(newid, newname, dSelect);
				break;
			case2:
				worker = new Manager(newid, newname, dSelect);
				break;
			case 3:
				worker = new Boss(newid, newname, dSelect);
				break;
			default:
				break;
			}
			//更改数据 到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}

		//清屏
		system("pause");
		system("cls");
	}
}

//查找职工
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrmax = i;

			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (m_EmpArray[j]->m_id < m_EmpArray[minOrmax]->m_id)
					{
						minOrmax = j;
					}
				}
				else
				{
					if (m_EmpArray[j]->m_id > m_EmpArray[minOrmax]->m_id)
					{
						minOrmax = j;
					}
				}
			}

			if (i != minOrmax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrmax];
				m_EmpArray[minOrmax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}

void workerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//清空内部存储
		if (this->m_EmpArray != NULL)
		{
			//清空每个数据
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;

			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}


workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}