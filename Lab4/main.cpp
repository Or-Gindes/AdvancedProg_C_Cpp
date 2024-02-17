#include "Address.h"
#include "Date.h"
#include "Person.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	//Test 1 - Address
	cout << "Test 1\n";
	Address a;
	a.setAddress((char*)"Camebridge", (char*)"Trinity Lane", 1);
	a.print();
	cout << "\n";

	//Test 2 - Date
	cout << "Test 2\n";
	Date d;
	d.setDate(2012, OCT, 15);
	d.print();
	cout << "\n";

	//Test 3 - Person
	cout << "Test 3\n";
	Person p;
	p.setAddress((char*)"Camebridge", (char*)"Massachusetts Ave", 1350);
	p.setId((char*)"123456");
	p.setDate(2012, NOV, 8);
	p.print();
	cout << "\n";

	return 1;
}
