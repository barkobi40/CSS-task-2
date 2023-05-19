#include "Account.h"
#define _CRT_SECURE_NO_WARNING

Account::Account()
{
	m_numberOfTransaction = 0;
	m_accountNumber = 0;
	m_balance = 0;
	m_persons = nullptr;
	m_totalPersons = 0;
	m_transactionList = nullptr;
}
Account::Account(Person** persons, int count, double balance)
{
	SetBalance(balance);
	int num = 0;
	m_totalPersons = 0;
	m_persons = new Person * [count];
	for (int i = 0; i < count; i++)
	{
		m_persons[i] = new Person(*persons[i]);
		m_totalPersons++;
		num += persons[i]->GetId() / 10;
	}
	SetAccountNumber(num);
	m_numberOfTransaction = 0;
	m_transactionList = nullptr;
}
Account::Account(const Person& person, double balance)
{
	m_totalPersons = 1;
	SetBalance(balance);
	m_persons = new Person * [1];
	m_persons[0] = new Person(person);
	m_numberOfTransaction = 0;
	SetAccountNumber(person.GetId() / 10);
	m_transactionList = nullptr;
}
Account::Account(const Account& other)
{
	SetAccountNumber(other.GetAccountNumber());
	SetBalance(other.m_balance);
	SetPersons(other.m_persons,other.m_totalPersons);
	SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
}
Account::~Account()
{
	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		delete m_transactionList[i]->GetDate();
		delete m_transactionList[i]->GetDes();
		delete m_transactionList[i]->GetSource();
		delete m_transactionList[i];
	}
	for (int i = 0; i < m_totalPersons; i++)
	{
		m_persons[i]->~Person();
	}
	delete[]m_persons;
	delete[]m_transactionList;
}

void Account::SetPersons(Person** persons, int count)
{
	m_totalPersons = count;
	m_persons = new Person*[count];	
	for (int i = 0; i < count; i++)
	{
		m_persons[i] = new Person(*persons[i]);	
	}
}
void Account::SetAccountNumber(int number)
{
	m_accountNumber = number;
}
void Account::SetBalance(double balance)
{
	m_balance = balance;
}
void Account::SetTransactions(Transaction** newTransaction, int count)
{
	m_transactionList = new Transaction * [count];
	m_numberOfTransaction = count;
	for (int i = 0; i < count; i++)
	{
		m_transactionList[i] = new Transaction(*newTransaction[i]);
	}
}
Transaction** Account::GetTransactions()
{
	return m_transactionList;
}
int	Account::GetNumOfTransactions()
{
	return m_numberOfTransaction;
}
Person** Account::GetPersons() const
{
	return m_persons;
}
int	Account::GetTotalPersons()const
{
	return m_totalPersons;
}
int	Account::GetAccountNumber() const
{
	return m_accountNumber;
}
double	Account::GetBalance() const
{
	return m_balance;
}

void Account::Withdraw(double amount, const char* date)
{
	this->m_balance -= amount;
	Transaction** tmp = new Transaction * [m_numberOfTransaction + 1];
	for (int i = 0; i < m_numberOfTransaction; i++)// create tmp array
	{
		tmp[i] = new Transaction(*m_transactionList[i]);
	}
	tmp[m_numberOfTransaction] = new Transaction(this, this, amount, date);// c'tor of the tmp array
	m_numberOfTransaction++;
	SetTransactions(tmp, m_numberOfTransaction);
	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		delete[]tmp[i];
	}
	delete[]tmp;
}

void Account::Deposit(double amount, const char* date)
{
	this->m_balance += amount;
	Transaction** tmp = new Transaction * [m_numberOfTransaction + 1];
	for (int i = 0; i < m_numberOfTransaction; i++)// create tmp array
	{
		tmp[i] = new Transaction(*m_transactionList[i]);
	}
	tmp[m_numberOfTransaction] = new Transaction(this, this, amount, date);// c'tor of the tmp array
	m_numberOfTransaction++;
	SetTransactions(tmp, m_numberOfTransaction);
	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		delete[]tmp[i];
	}
	delete[]tmp;

}
void Account::AddPerson(const Person& newPerson, double	amount)
{
	for (int i = 0; i < m_totalPersons; i++)
	{
		if (m_persons[i]->GetId()==newPerson.GetId())//person exsist on person array
		{
			return;
		}
	}
	Person** tmp = new Person * [m_totalPersons + 1];
	for (int i = 0; i < m_totalPersons; i++)
	{
		tmp[i] = new Person(*m_persons[i]);
	}
	tmp[m_totalPersons] = new Person(newPerson);
	m_totalPersons++;
	SetPersons(tmp, m_totalPersons);
	SetBalance(amount+m_balance);
	for (int i = 0; i < m_totalPersons; i++)
	{
		delete tmp[i];
	}
	delete[]tmp;
}
void Account::DeletePerson(const Person& oldPerson)
{
	for (int i = 0; i < m_totalPersons; i++)
	{
		if (m_persons[i]->GetId()== oldPerson.GetId())
		{
			m_persons[i]->~Person();
			i--;
			m_totalPersons--;
		}
	}
	oldPerson.~Person();
	
}
void Account::AddTransaction(const Transaction& newTransaction)
{
	if (this->GetAccountNumber() == newTransaction.GetDes()->GetAccountNumber()&& 
		this->GetAccountNumber() == newTransaction.GetSource()->GetAccountNumber())
	{
		Transaction** tmp = new Transaction * [m_numberOfTransaction+1];
		for (int i = 0; i < m_numberOfTransaction; i++)
		{
			tmp[i] = new Transaction(*m_transactionList[i]);
		}
		tmp[m_numberOfTransaction] = new Transaction(newTransaction);
		m_numberOfTransaction++;
		
	}
	else if (this->GetAccountNumber() == newTransaction.GetDes()->GetAccountNumber())
	{
		newTransaction.GetDes()->Withdraw(newTransaction.GetAmount(), newTransaction.GetDate());
		newTransaction.GetSource()->Deposit(newTransaction.GetAmount(), newTransaction.GetDate());
		
	}
	else if (this->GetAccountNumber() == newTransaction.GetSource()->GetAccountNumber())
	{
		newTransaction.GetSource()->Withdraw(newTransaction.GetAmount(), newTransaction.GetDate());
		newTransaction.GetDes()->Deposit(newTransaction.GetAmount(), newTransaction.GetDate());
		
	}
	else if (this->GetAccountNumber() != newTransaction.GetDes()->GetAccountNumber() &&
		this->GetAccountNumber() != newTransaction.GetSource()->GetAccountNumber())
	{
		newTransaction.GetSource()->Withdraw(newTransaction.GetAmount(), newTransaction.GetDate());
		newTransaction.GetDes()->Deposit(newTransaction.GetAmount(), newTransaction.GetDate());
	}
}

void Account::clearTransactions()
{

	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		delete m_transactionList[i]->GetSource();
		delete m_transactionList[i]->GetDes();
		delete m_transactionList[i]->GetDate();
		delete m_transactionList[i];
	}
	delete[]m_transactionList;
}
//delete person fron the person array
void Account::clearPersons()
{
	for (int i = 0; i < m_totalPersons; i++)
	{
		m_persons[i]->~Person();
	}
	delete[]m_persons;
}