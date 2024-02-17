#ifndef _GENDICT_
#define _GENDICT_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct t_GenDict *GenDict;

typedef void* Element;

typedef Element (*copyFunction)(Element);
typedef void (*freeFunction)(Element);


GenDict createDictionary(copyFunction copyf, freeFunction freef);
void addElement(GenDict sd, int key, Element val);
void removeElement(GenDict sd, int key);
Element getElement(GenDict sd, int key);
int getNextFreeIndex(GenDict sd);


#endif //_GENDICT_
