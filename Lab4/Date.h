#ifndef DATE_H_
#define DATE_H_
#include <iostream>

using namespace std;

enum eMonth{ JAN, OCT, NOV };

class Date
{
private:
    int _year;
    eMonth _month;
    int _day;
public:
    Date ();
    void setDate (int year, eMonth, int day);
    void print();
    ~Date(){ cout << "Date deleted" << endl; };
};

#endif /* DATE_H_ */