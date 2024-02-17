/* linked list example */
#include "LinkedListPartial.h"


/* head points to first node in list, end points to last node in list */
/* initialise both to NULL, meaning no nodes in list yet */
Node *head = (Node*) NULL;
Node *end = (Node*) NULL;

/* this initialises a node, allocates memory for the node, and returns   */
/* a pointer to the new node. Must pass it the node details, name and id */
Node* initnode(char *name, int id )
{
	//complete
   Node *pNode;
   if(strlen(name)<19)
   {
      pNode = malloc(sizeof(Node));
      memcpy(pNode->name, name, strlen(name));
      pNode->id = id;
      pNode->next = NULL;
      return pNode;
   }
	return NULL;
}

/* this prints the details of a node, eg, the name and id                 */
/* must pass it the address of the node you want to print out             */
void printnode(Node *ptr )
{
	//complete
   if (NULL != ptr){
      printf("Node: %s\t-\t%d\n", ptr->name, ptr->id);
   }
}

/* this prints all nodes from the current address passed to it. If you    */
/* pass it 'head', then it prints out the entire list, by cycling through */
/* each node and calling 'printnode' to print each node found             */
void printlist(Node *ptr )
{
	//complete
   while (ptr != NULL){
      printnode(ptr);
      ptr = ptr->next;
   }
}
/* this adds a node to the end of the list. You must allocate a node and  */
/* then pass its address to this function                                 */
void add(Node* newNode )  /* adding to end of list */
{
	//complete
   //if head is NULL, i.e. empty list, make head point to newNode
   if(head == NULL)
   {
      head = newNode;
      printf("added new node at the beginning\n");
   }
   //else make end->next point to newNode and make end point to newNode
   else
   {
      Node *tmp = head;
      while(1){
         if(tmp->next == NULL)
         {
            tmp->next = newNode;
            printf("Added new node at the end\n");
            break;
         }
         tmp = tmp->next;
      }
   }
}

/* search the list for a name, and return a pointer to the found node     */
/* accepts a name to search for, and a pointer from which to start. If    */
/* you pass the pointer as 'head', it searches from the start of the list */
Node* searchname(Node *ptr, char *name )
{
	//complete
   if(head == NULL){
      printf("Unable to search empty list, please add a Node first\n");
      return head;
   }
   else{
      Node *tmp = ptr;
      while (strcmp(tmp->name,name)){
         tmp = tmp->next;
         if(tmp == NULL)
            return end;
      }
      return tmp;
   }
}

/* deletes the specified node pointed to by 'ptr' from the list           */
void deletenode(Node *ptr )
{
	//complete
   if(head == NULL)
      printf("Unable to search empty list, please add a Node first\n");

   else if (ptr == head)
      head = head->next; 

   else{
      Node *tmp = head;
      Node *prev = head;
      while(tmp != ptr){
         prev = tmp;
         tmp = tmp->next;
      }
      prev->next = tmp->next;
      free(tmp);
   }
}

/* inserts a new node, uses place to align node in the proper place in list */
/* pass it the address of the new node to be inserted, with details all   */
/* filled in                                                              */
void insertnode(Node* newNode, int place)
{
	//complete
   //if place is 0 make head point at newNode and newNode takes original head's next
   if(place == 0){
      newNode->next = head;
      head = newNode;
   }
   else{
      Node *tmp = head;
      Node *prev = head;
      for(int i=0;i<place;i++){
         if(tmp->next == NULL){
            tmp->next = newNode;
            printf("Added new node at the end\n");
            return;
         }
         prev = tmp;
         tmp = tmp->next;
      }
      prev->next = newNode;
      newNode->next = tmp;
   }
}

/* this deletes all nodes from the place specified by ptr                 */
/* if you pass it head, it will free up entire list                       */
void deletelist(Node *ptr )
{
	//complete
   Node *tmp = ptr;
   while(tmp != NULL){
      printf("deleting %s\n", tmp->name);
      deletenode(tmp);
      tmp = tmp->next;
   }
}

/* this is the main routine where all the glue logic fits                 */
int main()
{
   char name[20];
   int id, place, ch = 1;
   Node *ptr;

   while( ch != 0 ) {
      printf("1 add a name \n");
      printf("2 delete list \n");
      printf("3 list all names \n");
      printf("4 search for name \n");
      printf("5 insert a name \n");
      printf("0 quit\n");
      scanf("%d", &ch );
      switch( ch )
      {
          case 1:  /* add a name to end of list */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   printf("Enter in id -- ");
                   scanf("%d", &id );
                   ptr = initnode( name, id );
                   add( ptr );
                   break;

          case 2:  /* delete list */
                   deletelist(head);
		   head = NULL;
		   end = NULL;
		   printf("list deleted\n");
                   break;

          case 3:  /* list all nodes */
                   printlist( head );
                   break;

          case 4:  /* search and print name */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   ptr = searchname( head, name );
                   if( NULL == ptr ) {
                       printf("Name %s not found\n", name );
                   }
                   else
                      printnode( ptr );
                   break;

          case 5:  /* insert a name in list */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   printf("Enter in id -- ");
                   scanf("%d", &id );
                   printf("Enter in place in list -- ");
                   scanf("%d", &place );
                   ptr = initnode( name, id );
                   insertnode( ptr, place );
                   break;
      }
   }
   deletelist( head );

   return 0;
}
