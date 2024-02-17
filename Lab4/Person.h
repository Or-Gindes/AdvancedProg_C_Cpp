#ifndef PERSON_H_
#define PERSON_H_
#include "Address.h"
#include "Date.h"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Person
{
private:
	int _age;
	double _height;
	char *_id;
	Date _birthDate;
	Address _addr;

public:
	Person();
    void setAge(int);
    void setHeight(double);
	void setId(char*);
	void setAddress(char*, char*, int);
    void setDate(int, eMonth, int);
	void print();
	~Person(){ delete[]_id; cout << "Person deleted" << endl;};
};

#endif /* PERSON_H_ */