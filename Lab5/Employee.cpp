#include "Employee.h"

// Initialize static member of class Employee
int Employee::_employeeCount = 0;

Employee::Employee()
{
    _name = nullptr;
    setName("");
    setSalary(0.0);
    _employeeCount++;
}

Employee::Employee(char* name, double salary)
{
    _name = nullptr;
    setName(name);
    setSalary(salary);
    _employeeCount++;
}

Employee::Employee(const Employee &other)
{
    _name = nullptr;
    setName(other._name);
    setSalary(other._salary);
    _employeeCount++;
}

void Employee::setSalary(double salary)
{
	_salary = salary;
}

bool Employee::setName(const char* name)
{
	if (!name)
		return false;
	char* temp = new char[strlen(name) + 1];
	if (!temp)
		return false;
	strcpy(temp, name);
    delete[] _name;
	_name = temp;
	return true;
}

bool Employee::operator==(const Employee& other)const
{
    if (strcmp(_name, other._name) != 0)
        return false;
    
    return true;
}

bool Employee::operator>(const Employee& other)const
{
    if (_salary > other._salary)   
        return true;
    
    return false;
}

const Employee& Employee::operator+(const Employee& other)
{
    _salary += other._salary;
    return *this;
}

Employee& Employee::operator++()
{
    _salary += 100;
    return *this;
}

const Employee& Employee::operator+=(const Employee& other)
{
    char* temp = new char[strlen(_name) + strlen(other._name) + 1];
	if (!temp)
		return *this;
	strcpy(temp, _name);
    strcat(temp, other._name);
    delete[] _name;
    _name = temp;
    return *this;
}

ostream& operator<<(ostream& out, const Employee& employee)
{
	cout << "Name:" << employee._name << "\n" << employee._salary << endl;
	return out;
}

Employee::~Employee()
{
	delete[] _name;
}