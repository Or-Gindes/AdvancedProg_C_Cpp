#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"
#include <string>

class Student : public Person
{
private:
    std::string m_collegeName;
    static int m_numOfCreatedStudents;  // like in the cat counter!

public:
    Student(); //default constructor - what does it means?
    Student(int day, int month, int year);
    Student (const Student& other);
    ~Student();

    void SetCollegeName(std::string collegeName);

    std::string getCollegeName() const;

    bool operator<(const Student& other) const;
    Student& operator=(const Student &other);

    //what will happen if we will add const to the end of the declaration?
    static int GetNumOfCreatedStudents();
};


#endif /* STUDENT_H_ */
