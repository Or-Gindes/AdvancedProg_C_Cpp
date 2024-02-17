#ifndef MASTERSTUDENT_H_
#define MASTERSTUDENT_H_

#include "Student.h"

class MasterStudent : public Student
{
private:
    std::string m_firstDegree;

public:
    MasterStudent();
    MasterStudent(const MasterStudent& other);
    ~MasterStudent();

    void setFirstDegreeName(std::string name);
    std::string getFirstDegreeName()const;
};

#endif /* MASTERSTUDENT_H_ */
