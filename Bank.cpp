#include "Bank.h"
#define _CRT_SECURE_NO_WARNING

Bank::Bank()
{
	m_bankCode = 0;
	m_account = nullptr;
	m_totalBalance = 0;
	m_name = nullptr;
	m_numbeOfAccounts = 0;
}
Bank::Bank(const char* name, int code)
{
	SetCode(code);
	SetBankName(name);
	m_account = nullptr;
	m_totalBalance = 0;
	m_numbeOfAccounts = 0;
}
Bank::~Bank()
{
	delete[] m_name;
	for (int i = 0; i < m_numbeOfAccounts ; i++)
	{
		m_account[i]->~Account();
		delete m_account[i];
	}
	delete m_account;
}
void Bank::SetBankName(const char* name)
{
	m_name = new char[strlen(name)+1];
	strcpy(m_name, name);
}
void Bank::SetAccount(Account** account, int numbeOfAccounts)
{
	m_numbeOfAccounts = numbeOfAccounts;
	m_account = new Account * [numbeOfAccounts];
	for (int i = 0; i < numbeOfAccounts; i++)
	{
		m_account[i]= new  Account(*account[i]);
	}
	
}
void Bank::SetTotal(double total)
{
	m_totalBalance = total;
}
void Bank::SetCode(int code)
{
	m_bankCode = code;
}
const char* Bank::GetBankName() const
{
	return m_name;
}
Account** Bank::GetAccounts() const
{
	return m_account;
}
int Bank::GetNumberOfAccounts() const
{
	return m_numbeOfAccounts;
}
double Bank::GetTotal() const
{
	return m_totalBalance;
}
int Bank::GetCode() const
{
	return m_bankCode;
}
void Bank::AddAccount(const Account& account)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber()== account.GetAccountNumber())
		{
			return;
		}
	}
	Account** tmp = nullptr;
	tmp=new Account * [m_numbeOfAccounts + 1];
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		tmp[i] = new Account(*m_account[i]);	
	}
	tmp[m_numbeOfAccounts] = new Account(account);
	m_numbeOfAccounts++;
	SetAccount(tmp, m_numbeOfAccounts);
	SetTotal(account.GetBalance()+this->m_totalBalance);
	delete[]tmp;
}
void Bank::AddAccount(const Person& per, double amount)
{
	Account** tmp = new Account * [m_numbeOfAccounts + 1];
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		tmp[i] = new Account(*m_account[i]);
	}
	tmp[m_numbeOfAccounts] = new Account(per, amount);
	m_numbeOfAccounts++;
	SetAccount(tmp, m_numbeOfAccounts);
	SetTotal(amount + this->GetTotal());
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		delete tmp[i];
	}
	delete[]tmp;

}
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	int flag = 0;
	int counter = 0;
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber()==account.GetAccountNumber())
		{
			flag = 1;
			counter = i;
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++)
			{
				if (m_account[i]->GetPersons()[j]->GetId()== newPerson.GetId())
				{
					flag = 2;
					return;
				}
			}
		}
	}
	if (flag==1)
	{
		m_account[counter]->AddPerson(newPerson, amount);
	}
	else if (flag==0)
	{
		AddAccount(account);
		m_numbeOfAccounts++;
	}
}
void Bank::DeleteAccount(const Account& account)
{
	int count = 0;
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (account.GetAccountNumber()== m_account[i]->GetAccountNumber())
		{
			m_account[i]->~Account();
		}
	}
}
void Bank::DeletePerson(const Person& p)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		for (int j = 0; j < m_account[i]->GetTotalPersons(); j++)
		{
			if (m_account[i]->GetPersons()[j]->GetId()==p.GetId())
			{
				if (m_account[i]->GetTotalPersons()==1)
				{
					m_totalBalance -= m_account[i]->GetBalance();
					m_account[i]->~Account();
					m_numbeOfAccounts--;
				}
				
			}
		}
	}
}
