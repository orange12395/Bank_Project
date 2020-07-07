#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;


class Account
{
protected:
	const int accID; //���¹�ȣ
	int balance; //�ܾ�
	char *cusName;
	const long long SSN;

public:

	Account(int accID, int balance, char* cusName, long long SSN)
		:accID(accID), SSN(SSN)
	{
		this->balance = balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	Account(const Account& qwe)
		:accID(qwe.accID), SSN(qwe.SSN)
	{
		balance = qwe.balance;
		cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, qwe.cusName);
		cout << "���� ������" << endl;
	}


	virtual ~Account()
	{
		delete[] cusName;
	}

	bool checkAccid(int accId)
	{
		return this->accID == accId;
	}

	virtual int cal_interest(int amount)
	{
		return (int)((double)balance * 0.01);
	}

	void deposit(int balance)
	{
		this->balance += balance;
		int interest = cal_interest(this->balance);
		cout << "" << endl;
		cout << balance << "���� �ԱݵǾ����ϴ�" << endl;
		this->balance = this->balance + cal_interest(this->balance);
		cout << "����: " << interest <<"��"<< endl;
		cout << "�ܾ�: " << this->balance <<"��"<< endl;
		cout << endl;
	}

	void withdraw(int balance)
	{
		if (balance < 1)
		{
			cout << "��ݾ��� 0���� Ŀ�� �մϴ�" << endl;
			cout << endl;
			return;
		}

		else if (this->balance < balance)
		{
			cout << "�ܾ��� �����մϴ�." << endl;
			cout << "�ܾ�: " << this->balance << "��" << endl;
		}

		else
		{
			this->balance -= balance;
			cout << "" << endl;
			cout << balance << "���� ��ݵǾ����ϴ�" << endl;
			cout << "�ܾ�: " << this->balance << "��" << endl;
			cout << endl;
		}
	}

	bool checkSSN(long long SSN)
	{
		return this->SSN == SSN;
	}

	void printall()
	{
		cout << "���¹�ȣ: " << accID << endl;
		cout << "�̸�: " << cusName << endl;
		cout << "�ֹε�Ϲ�ȣ: " << SSN << endl;
		cout << "�ܾ�: " << balance << endl;
		cout << endl;
	}
};

class deposit_account : public Account 
{
public:
	deposit_account(int in_accID, int in_balance, char* in_cusName, long long in_SSN) : Account(in_accID, in_balance, in_cusName, in_SSN)
	{

	}

	virtual int cal_interest(int amount)
	{
		return (int)((double)balance * 0.02);
	}
};

class AccountManager
{
protected:
	int mem_cnt = 0;
	Account *acc[100];

public:

	AccountManager()
	{
		for (int i = 0; i < mem_cnt; i++)
		{
			delete acc[i];
		}
	}

	void make_account(int select)
	{
		int accID;
		int balance;
		char cusName[NAME_LEN];
		long long SSN = 0;
		bool checkSSN = false;

		if (mem_cnt >= 100)
		{
			cout << "���ο� ���� ���� �Ұ�" << endl;
		}
		
		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> accID;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkAccid(accID)) {
				cout << "���¹�ȣ �ߺ���" << endl;
				cout << endl;
				return;
			}
		}

		cout << "��  ��: ";
		cin >> cusName;

		cout << "�ֹε�Ϲ�ȣ:";
		cin >> SSN;

		if (select == 1)
		{
			for (int i = 0; i < mem_cnt; i++)
			{
				if (acc[i]->checkSSN(SSN)) {
					cout << "�ֹε�Ϲ�ȣ �ߺ���" << endl;
					cout << endl;
					return;
				}
			}
		}

		else
		{
			for (int i = 0; i < mem_cnt; i++)
			{
				if (acc[i]->checkSSN(SSN)) 
				{
					checkSSN = true;
				}
			}

			if (checkSSN == false)
			{
				cout << "������°� �����ϴ�" << endl << endl;
				return;
			}
		}

		cout << "�Աݾ�: ";
		cin >> balance;


		if (balance < 10)
		{
			cout << "10�� �̻��� �־��ֽʽÿ�" << endl;
			cout << endl;
			return;
		}

		if (select == 1)
		{
			acc[mem_cnt] = new Account(accID, balance, cusName, SSN);
		}
		else
		{
			acc[mem_cnt] = new deposit_account(accID, balance, cusName, SSN);
		}

		mem_cnt++;
		cout << endl;
	}

	

	void withdraw()
	{
		int ID;
		int money = 0;

		if (mem_cnt == 0)
		{
			cout << "������ ����" << endl;
			return;
		}

		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> ID;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkAccid(ID))
			{
				cout << "��ݾ�: ";
				cin >> money;

				acc[i]->withdraw(money);
			}
		}
	}

	void deposit()
	{
		int ID;
		int money = 0;

		if (mem_cnt == 0)
		{
			cout << "������ ����" << endl;
			return;
		}

		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> ID;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkAccid(ID))
			{
				cout << "�Աݾ�: ";
				cin >> money;
				if (money < 1)
				{
					cout << "�Աݾ��� 0���� Ŀ�� �մϴ�" << endl;
					cout << endl;
					return;
				}

				acc[i]->deposit(money);
			}

		}
	}

	void print_all()
	{
		if (mem_cnt == 0)
		{
			cout << "��ϵ� ���� ����" << endl;
		}
		for (int i = 0; i < mem_cnt; i++)
		{
			acc[i]->printall();
		}
	}
};



void main()
{
	AccountManager* accmanager = new AccountManager;

	while (1)
	{
		int a;
		cout << "-----menu-----" << endl;
		cout << "1. ���¼���" << endl;
		cout << "2. ��    ��" << endl;
		cout << "3. ��    ��" << endl;
		cout << "4. �������� ��ü ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "����: ";

		cin >> a;

		cout << endl;

		switch (a)
		{
		case 1:
			int select;
			cout << "[��������]" << endl << "1. �������" << endl << "2. ���ݰ���" << endl << "���� :";
			cin >> select;
			cout << "" << endl;
			accmanager->make_account(select);
			break;

		case 2:
			accmanager->deposit();
			break;

		case 3:
			accmanager->withdraw();
			break;

		case 4:
			accmanager->print_all();
			break;

		case 5:
			delete(accmanager);
			break;

		default:
			cout << "1~5 ���� �������ּ���." << endl;
			cout << endl;
		}

	}

}