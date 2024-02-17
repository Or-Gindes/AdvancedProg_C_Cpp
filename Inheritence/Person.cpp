#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(int day, int month, int year):
        m_birthDate(day, month, year)
{
    cout << "In Person::Person(int day, int month, int year)" << endl;
}

Person::Person(const Person& p):
        m_birthDate(p.m_birthDate)
{
    cout << "In Person::Copy Constructor" << endl;
    m_id = p.m_id;
};

Person::~Person()
{
    cout << "In Person::~Person()" << endl;
};


Person& Person::operator=(const Person &other)
{
    cout << "In Person::operator=" << endl;
    SetAge(other.m_age);
    m_height = other.m_height;
    m_id = other.m_id;
    return *this;
};

bool Person::operator<(const Person &other) const
{
    return m_birthDate < other.m_birthDate;
};

/****************** Setters ****************/

//This is a private function
void Person::SetAge(int age)
{
    m_age = age;
};

//This is a public function
void Person::SetHeight(double height)
{
    m_height = height;
};

void Person::SetBirthDate(int day, int month, int year)
{
    m_birthDate.SetDate(day, month, year);
};

void Person::SetBirthDate(Date date)
{
    m_birthDate.SetDate(date.GetDay(),date.GetMonth(),date.GetYear());
};

/****************** Getters ****************/

int Person::GetAge() const
{
    return m_age;
};
double Person::GetHeight() const
{
    return m_height;
};

std::string Person::GetID() const
{
    return m_id;
};

Date Person::GetBirthDay() const
{
    return m_birthDate;
};
