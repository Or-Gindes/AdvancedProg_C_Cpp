#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Employee
{
    char *_name;
    double _salary;
    static int _employeeCount;

public:
    // default constructor
    Employee();
    // parameterized constructor
    Employee(char*, double);
    // copy constructor
    Employee(const Employee &eSrc);
    // Use to set an Employee's salary
    void setSalary(double salary);
    // Use to set an Employee's name
    bool setName(const char* name);
    // Overload '==' operator - determine if employees have the same name 
    bool operator==(const Employee& other)const;
    // Overload '>' operator - determine if one employee makes a salary than the other
    bool operator>(const Employee& other)const;
    // Overload '+' operator - add other employee salary to first employee salary
    const Employee& operator+(const Employee& other);
    // Overload '++' operator - add 100 to employee salary
    Employee& operator++();
    // Overload '+=' operator - add other employee name to first employee name
    const Employee& operator+=(const Employee& other);
    // Overload '<<' operator - output employee info to stdout
    friend ostream& operator<<(ostream& out, const Employee& employee);
    // Get current number of employees 
    static int getNumberOfEmployee() {return _employeeCount;}
    // Destructor
    ~Employee();
};

#endif /* EMPLOYEE_H_ */