#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;

int mem_cnt = 0;

typedef struct
{
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char cusName[NAME_LEN];

}Account;

Account *acc = new Account[100];

void make_account()
{

	if (mem_cnt >= 100)
	{
		cout << "���ο� ���� ���� �Ұ�" << endl;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> acc[mem_cnt].accID;

	for (int i = 0; i < mem_cnt; i++)
	{
		if (acc[i].accID == acc[mem_cnt].accID)
		{
			cout << "���°� �ߺ���" << endl;
			cout << endl;
			return;
		}
	}

	cout << "��  ��: ";
	cin >> acc[mem_cnt].cusName;

	for (int i = 0; i < mem_cnt; i++)
	{
		const char* str1 = acc[i].cusName;
		const char* str2 = acc[mem_cnt].cusName;
		if (strcmp(str1, str2) == 0)
		{
			cout << "���� �Ѱ��� ���¸� ��������" << endl;
			cout << endl;
			return;
		}
	}

	cout << "�Աݾ�: ";
	cin >> acc[mem_cnt].balance;

	if (acc[mem_cnt].balance < 10)
	{
		cout << "10�� �̻��� �־��ֽʽÿ�" << endl;
		cout << endl;
		return;
	}

	mem_cnt++;
	cout << endl;
}

void deposit()
{
	int ID;
	int money=0;

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
		if (acc[i].accID == ID)
		{
			cout << "�Աݾ�: ";
			cin >> money;
			if (money < 1)
			{
				cout << "�Աݾ��� 0���� Ŀ�� �մϴ�" << endl;
				cout << endl;
				return;
			}

			acc[i].balance += money;
			cout << money << "���� �ԱݵǾ����ϴ�" << endl;
			cout << "�ܾ�: " << acc[i].balance << endl;
			cout << endl;
		}
		else cout << "��ȿ���� ���� ID �Դϴ�." << endl;
		cout << endl;
	
	}
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
		if (acc[i].accID == ID)
		{
			cout << "��ݾ�: ";
			cin >> money;
			if (money < 1)
			{
				cout << "��ݾ��� 0���� Ŀ�� �մϴ�" << endl;
				cout << endl;
				return;
			}
			else if (acc[i].balance < money)
			{
				cout << "�ܾ��� �����մϴ�." << endl;
				cout << "�ܾ�: " << acc[i].balance << endl;
			}
			else
			{
				acc[i].balance -= money;
				cout << money << "���� ��ݵǾ����ϴ�" << endl;
				cout << "�ܾ�: " << acc[i].balance << endl;
				cout << endl;
			}
		}
		else cout << "��ȿ���� ���� ID �Դϴ�." << endl;
		cout << endl;

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
		cout << "���¹�ȣ: " << acc[i].accID << endl;
		cout << "�̸�: " << acc[i].cusName << endl;
		cout << "�ܾ�: " << acc[i].balance << endl;
		cout << endl;
	}
}

void main()
{
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
			make_account();
			break;
		case 2:
			deposit();
			break;
		case 3:
			withdraw();
			break;
		case 4:
			print_all();
			break;
		case 5:
			if (acc != NULL)
				delete[] acc;
			return;
		default:
			cout << "1~5 ���� �������ּ���." << endl;
			cout << endl;
		}

	}

}

