#include "MasterStudent.h"
#include <iostream>
using namespace std;

MasterStudent::MasterStudent(const MasterStudent& other): Student(other), m_firstDegree(other.m_firstDegree)
{
    cout << "In MasterStudent::MasterStudent(const MasterStudent& other)" << endl;
}

//what is missing in this constructor??
MasterStudent::MasterStudent(): m_firstDegree("SISE")
{
    cout << "In MasterStudent::MasterStudent()" << endl;
}

// Don't forget to write cout << "In MasterStudent::" << endl;

MasterStudent::~MasterStudent()
{
    cout << "In MasterStudent::~MasterStudent()" << endl;
};

string MasterStudent::getFirstDegreeName() const
{
    return m_firstDegree;
}

void MasterStudent::setFirstDegreeName(std::string name) {
    m_firstDegree = name;
};
