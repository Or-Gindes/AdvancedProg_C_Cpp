#include "Student.h"
#include <iostream>

using namespace std;

//Initialization of a static data-member.
int Student::m_numOfCreatedStudents=0;

Student::Student(): Person(1, 1, 1992), m_collegeName("BGU")
{
    cout << "In Student::Student()" << endl;
    m_numOfCreatedStudents++;
}

Student::Student(int day, int month, int year): Person(day, month, year), m_collegeName("BGU")
{
    cout << "In Student::Student(int day, int month, int year)" << endl;
    m_numOfCreatedStudents++;
}

//copy-constructor call to the copy constructor! why does it work?
Student::Student (const Student& other): Person(other), m_collegeName(other.m_collegeName)
{
    cout << "In Student::Student(const Student& other)" << endl;
    m_numOfCreatedStudents++;
}

Student::~Student()
{
    cout << "In Student::~Student()" << endl;
};

void Student::SetCollegeName(std::string collegeName)
{
    m_collegeName = collegeName;
};

std::string Student::getCollegeName() const
{
    return m_collegeName;
};

bool Student::operator<(const Student& other) const
{
    return this->Person::operator<(other);
};

Student& Student::operator=(const Student &other)
{
    this->Person::operator=(other);
    SetCollegeName(other.m_collegeName);
    return *this;
};

//this is static function.
int Student::GetNumOfCreatedStudents()
{
    return m_numOfCreatedStudents;
}

