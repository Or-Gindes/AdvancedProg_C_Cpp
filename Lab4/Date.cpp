#include "Date.h"

Date::Date()
{
    this->_year = 2023;
    this->_month = JAN;
    this->_day = 1;
    cout << "New Date" << endl;
}

void Date::setDate(int year, eMonth month, int day)
{
    this->_year = year;
    this->_month = month;
    this->_day = day;
}

void Date::print()
{
    cout << this->_day << " of " << this->_month << ", " << this->_year;
}