#include "Date.h"
#include <ctime>
#include <iostream>

Date::Date(int day, int month, int year):
        m_day(day), m_month(month), m_year(year){}

Date::Date(const Date& other):
        m_day(other.m_day), m_month(other.m_month), m_year(other.m_year){}

Date& Date::operator=(const Date& otherDate)
{
    if (this==&otherDate)
        return *this;
    m_day = otherDate.m_day;
    m_month = otherDate.m_month;
    m_year = otherDate.m_year;
    return *this;
}

Date::~Date() {}

Date Date::GetNowDaysDate()
{
    //this is static! cant write this->m_day for example
    //this->
    time_t rawtime = std::time(0);
    std::tm* timeinfo = std::localtime(&rawtime);

    //return by value
    return Date(timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900);
};

void Date::SetDate(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
};

void Date::setDay(int day)
{
    m_day = day;
};

void Date::setMonth(int month)
{
    m_month = month;
};

void Date::setYear(int year)
{
    m_year = year;
};

int Date::GetDay()const
{
    return m_day;
};

int Date::GetMonth()const
{
    return m_month;
};

int Date::GetYear()const
{
    return m_year;
};

//In this function the direction is important
//a < b   <==>  a.operator<(b)  ->  this = a,  other = b
bool Date::operator< (const Date& otherDate) const
{
    if (m_year < otherDate.m_year)
        return true;
    if (m_year == otherDate.m_year && m_month < otherDate.m_month)
        return true;
    if (m_month == otherDate.m_month && m_day < otherDate.m_day)
        return true;
    return false;
};

//The comparison here is according to the content of the object
bool Date::operator== (const Date& otherDate) const
{
    if (m_year == otherDate.m_year && m_month == otherDate.m_month && m_day == otherDate.m_day)
        return true;
    return false;
}

void Date::Show() const
{
    std::cout << m_day << "/" << m_month << "/" << m_year <<std::endl;
};

