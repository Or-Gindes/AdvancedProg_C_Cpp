#include "Person.h"

Person::Person()
{
    this->_age = 0;
    this->_height = 0;
    this->_id = new char[300];
    this->_birthDate;
    this->_addr;
    cout << "New Person" << endl;
}

void Person::setAge(int age)
{
    this->_age = age;
}

void Person::setHeight(double height)
{
    this->_height = height;
}

void Person::setId(char* src)
{
	strcpy(this->_id, src);
}

void Person::setAddress(char *city, char *street, int num)
{
	(this->_addr).setAddress(city, street, num);
}

void Person::setDate(int year, eMonth month, int day)
{
	(this->_birthDate).setDate(year, month, day);
}

void Person::print()
{
	cout << "PERSON, id=" << this->_id << ", age=" << this->_age << ", height=" << this->_height << "." << endl;
	cout <<	"Born on ";
	(this->_birthDate).print();
	cout << endl;
	cout <<	"Lives in ";
	(this->_addr).print();
}