#include "Student.h"

Element copyStudent(Element elem)
{
	Student *s1 = (Student *)elem;
	Student *res = (Student *)malloc(sizeof(Student));
	res->name = (char *)malloc((strlen(s1->name)+1)*sizeof(char));
	strcpy(res->name, s1->name);
	res->id = s1->id;
	res->degree = s1->degree;
	res->domain = s1->domain;
	return (Element)res;
}

void freeStudent(Element elem)
{
	Student *s = (Student *)elem;
	free(s->name);
	free(s);
}
