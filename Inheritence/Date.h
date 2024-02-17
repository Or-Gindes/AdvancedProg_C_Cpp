#ifndef DATE_H_
#define DATE_H_

#define CURRENT_YEAR 2021

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;

public:
    //Notice there is no default constructor
    Date(int day, int month, int year=CURRENT_YEAR);
    Date(const Date& other);
    Date& operator=(const Date& otherDate);
    ~Date();

    void SetDate(int day, int month, int year);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    //const on "this", why?
    int GetDay()const;
    int GetMonth()const;
    int GetYear()const;
    void Show() const;

    bool operator< (const Date& otherDate) const;
    bool operator== (const Date& otherDate) const;

    static Date GetNowDaysDate();
    //there is no this to the function - static!

};

#endif /* DATE_H_ */
