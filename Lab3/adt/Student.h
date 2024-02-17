#ifndef _STUDENT_
#define _STUDENT_

#include "GenDict.h"

typedef enum e_Degree 
{
	BACHLOR,
	MASTER,
	DOCTOR
} Degree; 

typedef enum e_Domain
{
	ARCHITECTURE,
	ARTS,
	BUSINESS,
	ENGINEERING,
	MEDICINE,
	SCIENCE
} Domain;

typedef struct t_Student
{
	char *name;
	int id;
	Degree degree;
	Domain domain;
} Student;


Element copyStudent(Element elem);
void freeStudent(Element elem);


#endif //_STUDENT_
