#ifndef PERSON_H_
#define PERSON_H_

#include "Date.h"
#include <string>

class Person
{
private:
    Date m_birthDate;
    void SetAge(int age);

protected: // Relevant only in inheritances
    int m_age;
    double m_height;
    std::string m_id;

public:
    Person(int day, int month, int year); // There is no default constructor, why?
    Person(const Person& p);
    Person& operator=(const Person &other);
    ~Person();

    void SetHeight(double height);
    void SetBirthDate(int day, int month, int year);
    void SetBirthDate(Date date);

    int GetAge() const;
    double GetHeight() const;
    std::string GetID() const;
    Date GetBirthDay() const;

    bool operator<(const Person &other) const;

};

#endif /* PERSON_H_ */
