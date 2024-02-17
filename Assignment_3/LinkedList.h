#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"


/* definition of a LinkedList that can hold Element information */
typedef struct linkedList_s *linkedList;

/* To create a linked list we require knowledge of how to copy an element of the list, how to print it, how to free it and how to measure equality */
linkedList createLinkedList(CopyFunction copyEle, PrintFunction printEle, FreeFunction freeEle, EqualFunction equalEle);

/* Functions which the LinkedList ADT supports */
status destroyList(linkedList);                     // Delete list instance
status appendNode(linkedList, Element ele);         // Appened Node(Element) to a specific list instance
status deleteNode(linkedList, Element ele);         // Delete Node(Element) from a list after verifying it is indeed in list
status displayList(linkedList);                     // Display entire list, from first to last element
Element getDataByIndex(linkedList, int index);      // Return element found in index or NULL if index doesn't exist in list. Index ranges between 1 and NumOfElemenets
int getLengthList(linkedList);                      // Return lenght of linkedlist instance
Element searchByKeyinList(linkedList, Element ele); // Return first element in list that is equal to provided element or NULL

#endif /* LINKEDLIST_H_ */