#include "Transaction.h"
#define _CRT_SECURE_NO_WARNING

Transaction::Transaction(Account* s, Account* d, double amount, const char* date)
{
	SetAmount(amount);
	SetDate(date);
	SetSource(s);
	SetDes(d);

}
Transaction::Transaction(const Transaction& other)
{
	SetAmount(other.GetAmount());
	SetDate(other.GetDate());
	SetDes(other.GetDes());
	SetSource(other.GetSource());
}
void Transaction::SetSource(Account* src)
{
	m_source = src;	
}
void Transaction::SetDes(Account* dst)
{
	m_destination = dst;
}

void Transaction::SetAmount(double amount)
{
	m_amount = amount;
}
void Transaction::SetDate(const char* date)
{
	m_date = new char[(strlen(date))+1];
	if (m_date!=nullptr)
	{
		strcpy(m_date, date);
	}
}
Account* Transaction::GetSource() const
{
	return m_source;
}
Account* Transaction::GetDes() const
{
	return m_destination;
}
double Transaction::GetAmount() const
{
	return m_amount;
}
char* Transaction::GetDate() const
{
	if (m_date!= nullptr)
	{
		return m_date;
	}
	else
	{
		return nullptr;
	}
}
