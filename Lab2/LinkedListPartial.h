#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* definition of a data node for holding student information */
typedef struct Node_t
{
   char name[20];
   int  id;
   struct Node_t *next;
}Node;

Node* initnode( char *, int );
void printnode( Node* );
void printlist( Node* );
void add( Node* );
Node* searchname( Node*, char * );
void deletenode( Node* );
void insertnode( Node*, int place );
void deletelist( Node* );