#include "GenDict.h"

struct t_GenDict
{
	Element values[100];
	int keys[100];
	int nextFreeIndex;
	copyFunction copyFunc;
	freeFunction freeFunc;
};

GenDict createDictionary(copyFunction copyf, freeFunction freef)
{
	GenDict dict = (GenDict) malloc(sizeof(struct t_GenDict));
	if (dict == NULL)
		return NULL;
	
	// DEBUG CHECK IF NEEDED
	for (int i=0; i<100; i++){
		dict->values[i] = NULL;
		dict->keys[i] = 0;
	}
	dict->nextFreeIndex = 0;
	dict->copyFunc = copyf;
	dict->freeFunc = freef;	
	return dict;
}

/* Add Elemenet to dictonary in the next availiable index after checking there is room left in the dictionary */
/* Also tests that key doesn't already exist in the dictionary because keys must be unique */
void addElement(GenDict sd, int key, Element val)
{
	if (sd->nextFreeIndex >= 100)
		return;
	for (int i=0; i < sd->nextFreeIndex; i++){
		if (sd->keys[i] == key)
			return;
	} 
	sd->values[sd->nextFreeIndex] = sd->copyFunc(val);
	// Need to test that memory allocation in copyf was succesfull
	if (sd->values[sd->nextFreeIndex] == NULL)
		return;
	
	sd->keys[sd->nextFreeIndex] = key;
	sd->nextFreeIndex++;
}

/* Remove element according to key */
void removeElement(GenDict sd, int key)
{
	int i=0;
	for (i; i < sd->nextFreeIndex; i++){
		if (sd->keys[i] == key){
			sd->freeFunc(sd->values[i]);
			break;
		}
	}
	if (i == (sd->nextFreeIndex-1))
		sd->keys[i] = 0;
	// shift left remaining elements in dictionary 
	for (i; i < (sd->nextFreeIndex-1); i++){
		sd->keys[i] = sd->keys[i+1];
		sd->keys[i+1] = 0;
		sd->values[i] = sd->copyFunc(sd->values[i+1]);
		sd->freeFunc(sd->values[i+1]);
	}
	
	sd->nextFreeIndex--;
}
/* Find element in dictionary by comparing key to keys in array and returning the relevant value to this key if found */
Element getElement(GenDict sd, int key)
{
	for (int i=0; i < sd->nextFreeIndex; i++){
		if (sd->keys[i] == key)
			return sd->values[i];
	}
	return NULL;
}

/* Return the next free index of the provided dictionary */
int getNextFreeIndex(GenDict sd)
{
	return sd->nextFreeIndex;
}