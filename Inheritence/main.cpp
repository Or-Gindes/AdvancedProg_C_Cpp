//#include "Student.h"
#include "MasterStudent.h"
#include <iostream>

using namespace std;

int main()
{
    //static function exanple:
    (Date::GetNowDaysDate()).Show();
    Date d(22,12,2021);
    d.GetNowDaysDate().Show();

    Student *students[3];

    students[0] = new Student();
    students[1] = new MasterStudent();
    students[2] = new Student();

    //MasterStudent* m = (MasterStudent*)(students[1]);

    for (int i=0; i<3; i++)
    {
        students[i]->SetBirthDate(i+1, 9, 1990);
        students[i]->SetCollegeName("Ben Gurion University");
    };

    cout << "Number of created students is:" << Student::GetNumOfCreatedStudents() << endl;

    //cant use MasterStudent functions on  students[1] as is.

    for (int i=0; i<3; i++)
        delete students[i];

    MasterStudent* ms = new MasterStudent();;
    ms->setFirstDegreeName("Software and Information Systems Engineering");
    cout<<ms->getFirstDegreeName() <<endl;
    delete ms;
    return 0;
}
