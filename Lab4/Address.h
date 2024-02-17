
#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <iostream>
#include <string.h>

using namespace std;

class Address
{
private:
	char* _city;
	char* _street;
	int _num;
    
public:
	Address();
	void setAddress(char*, char*, int);
	void print();
	~Address(){ delete[]_city; delete[]_street; cout << "Address deleted" << endl; };
};


#endif /* ADDRESS_H_ */