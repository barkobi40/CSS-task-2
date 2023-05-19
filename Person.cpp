#include "Person.h"
#define _CRT_SECURE_NO_WARNING

Person::Person()
{
	m_name = nullptr;
	m_id = 0;
}
Person::Person(const char* name, int id)
{
	SetName(name);
	SetId(id);
}
Person::Person(const Person& other)
{
	this->SetName(other.m_name);
	this->SetId(other.m_id);

}
Person::~Person()
{
	if (m_name!=nullptr)
	{
		delete[] m_name;
	}
}

void Person::SetName(const char* newName)
{
	int size = strlen(newName)+1;
	m_name = new char[size];
	if (newName!=nullptr)
	{
		strcpy(m_name, newName);
	}
}
void Person::SetId(int newId)
{
	m_id = newId;
}
char* Person::GetName() const
{
	return m_name;
}
int	Person::GetId() const
{
	return m_id;
}