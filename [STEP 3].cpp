#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;


class Account
{
private:
	const int accID; //계좌번호
	int balance; //잔액
    char *cusName;
	const int SSN;

public:


	Account(int accID, int balance, char* cusName, int SSN)
		:accID(accID),SSN(SSN)
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
		cout << "복사 생성자" << endl;
	}


	~Account()
	{
		delete[] cusName;
	}

	bool checkAccid(int accId)
	{
		return this->accID == accId;
	}

	void deposit(int balance)
	{
		this->balance += balance;
		cout << balance << "원이 입금되었습니다" << endl;
		cout << "잔액: " << this->balance << endl;
		cout << endl;
	}

	void withdraw(int balance)
	{
		if (balance < 1)
		{
			cout << "출금액은 0보다 커야 합니다" << endl;
			cout << endl;
			return;
		}

		else if (this->balance < balance)
		{
			cout << "잔액이 부족합니다." << endl;
			cout << "잔액: " << this->balance << endl;
		}

		else
		{
			this->balance -= balance;
			cout << balance << "원이 출금되었습니다" << endl;
			cout << "잔액: " << this->balance << endl;
			cout << endl;
		}
	}

	bool checkSSN(int SSN)
	{
		return this->SSN == SSN;
	}

	void printall()
	{
		cout << "계좌번호: " << accID << endl;
		cout << "이름: " << cusName << endl;
		cout << "주민등록번호: " << SSN << endl;
		cout << "잔액: " << balance << endl;
		cout << endl;
	}


};

class AccountManager
{
private:
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

	void make_account()
	{
		int accID;
		int balance;
		char cusName[NAME_LEN];
		int SSN;

		if (mem_cnt >= 100)
		{
			cout << "새로운 계좌 생성 불가" << endl;
		}

		cout << "[계좌개설]" << endl;
		cout << "계좌ID: ";
		cin >> accID;

		cout << "이  름: ";
		cin >> cusName;

		cout << "주민등록번호:";
		cin >> SSN;

		cout << "입금액: ";
		cin >> balance;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkSSN(SSN) | acc[i]->checkAccid(accID)) {
				cout << "회원정보 중복됨" << endl;
				cout << endl;
				return;
			}


		}

		if (balance < 10)
		{
			cout << "10원 이상을 넣어주십시요" << endl;
			cout << endl;
			return;
		}

		acc[mem_cnt] = new Account(accID, balance, cusName, SSN);

		mem_cnt++;
		cout << endl;
	}

	void withdraw()
	{
		int ID;
		int money = 0;

		if (mem_cnt == 0)
		{
			cout << "정보가 없음" << endl;
			return;
		}

		cout << "[출    금]" << endl;
		cout << "계좌ID: ";
		cin >> ID;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkAccid(ID))
			{
				cout << "출금액: ";
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
			cout << "정보가 없음" << endl;
			return;
		}

		cout << "[입    금]" << endl;
		cout << "계좌ID: ";
		cin >> ID;

		for (int i = 0; i < mem_cnt; i++)
		{
			if (acc[i]->checkAccid(ID))
			{
				cout << "입금액: ";
				cin >> money;
				if (money < 1)
				{
					cout << "입금액은 0보다 커야 합니다" << endl;
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
			cout << "등록된 계좌 없음" << endl;
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
		cout << "1. 계좌설개" << endl;
		cout << "2. 입    금" << endl;
		cout << "3. 출    금" << endl;
		cout << "4. 계좌정보 전체 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택: ";

		cin >> a;

		cout << endl;

		switch (a)
		{
		case 1:
			accmanager->make_account();
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
			cout << "1~5 까지 선택해주세요." << endl;
			cout << endl;
		}

	}

}