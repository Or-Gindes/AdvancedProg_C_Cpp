#include "Student.h"


int main()
{
	int i;
	Student students[5];
	Student *s;
	printf("asd\n");
	//students details
	char* name[5] = {"Donatello", "Leonardo", "Michelangelo", "Raphael", "Splinter"};
	int id[5] = {588, 504, 624, 366, 678};
	Degree degree[5] = {BACHLOR, BACHLOR, BACHLOR, BACHLOR, MASTER};
	Domain domain[5] = {SCIENCE, ARTS, BUSINESS, MEDICINE, ENGINEERING};

	GenDict dictionary = createDictionary(copyStudent, freeStudent);


	for(i=0; i<5; i++)
	{
		students[i].name=name[i];
		students[i].id=id[i];
		students[i].degree=degree[i];
		students[i].domain=domain[i];
		addElement(dictionary, i, (Element)&(students[i]));
	}

	printf("Key  \tName           \tID\n");
	for(i=0; i<5; i++)
	{
		s = (Student *) getElement(dictionary, i);
		printf("%*d\t%*s\t%i\n", 5, i, 15, s->name, s->id);
		removeElement(dictionary, i);
	}
	printf("nextFreeIndex in dictionary is: %i (should be 0)\n", getNextFreeIndex(dictionary));

	return 1;
}
