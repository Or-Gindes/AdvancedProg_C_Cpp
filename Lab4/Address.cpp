#include "Address.h"

Address::Address()
{
    this->_city = new char[300];
    strcpy(this->_city, "BeerSheva");
    this->_street = new char[300];
    strcpy(this->_street, "David Ben Gurion Blvd");
    this->_num = 1;
    cout << "New Address" << endl;
}

void Address::setAddress(char* city, char* street, int num)
{
    strcpy(this->_city, city);
	strcpy(this->_street, street);
	this->_num = num;
}

void Address::print()
{
    cout << "[" << this->_city << ", " << this->_street << ", " << this->_num << "]";
}