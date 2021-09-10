#include "workerManager.h"

workerManager::workerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		return;
	}

	//2���ļ����ڣ����޼�¼
	char ch;
	ifs >> ch; //����һ���ַ�
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		return;
	}

	//3�����ļ����ڣ��Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е�����,�浽������
	this->init_Emp();
}

void workerManager::Show_Menu() 
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void workerManager::exitSystem()
{
	cout << "��ӭ���ٴ�ʹ��" << endl;
	system("pause");
	exit(0); //ǿ���˳�
}

void workerManager::Add_Emp()
{
	cout << "���������ְ������" << endl;

	int addNum = 0;//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�ռ��µ����ݴ�ŵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect; //����ѡ��

			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

	    //�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//�����ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}

	//����
	system("pause");
	system("cls");
		
}

void workerManager::save()
{
	//д�ļ�
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
	while (ifs >> id && ifs >> name && ifs >> did) //����һ������
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

		if (did == 1)  // 1��ͨԱ��
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2) //2����
		{
			worker = new Manager(id, name, did);
		}
		else //�ܲ�
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}

void workerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i=0; i < this->m_EmpNum; i++) //���this�ɼӿɲ���
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//ɾ��ְ��
//����ɾ���ı����Ǻ����ǰ��һ��
void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա�ĸ���

			//����ͬ�����µ��ļ�
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "δ�ҵ���ְ��" << endl;
		}
	}

	//����
	system("pause");
	system("cls");
}



void  workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ�����" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ�����������µ�ְ���ţ�" << endl;
			cin >> newid;

			cout << "�������������� " << endl;
			cin >> newname;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//�������� ��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}

		//����
		system("pause");
		system("cls");
	}
}

//����ְ��
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) //��ְ���Ų���
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) //����������
		{
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_id
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

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
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}
}

void workerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//����ڲ��洢
		if (this->m_EmpArray != NULL)
		{
			//���ÿ������
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
		cout << "��ճɹ���" << endl;
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