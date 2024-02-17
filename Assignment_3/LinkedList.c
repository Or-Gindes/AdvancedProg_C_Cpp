#include "LinkedList.h"

/* Linked list implemenation based on Nodes which point to the next node in order */
/* Each node contains an element copied using copyFunction provided in initialization of list and pointer to next node */
typedef struct Node_t
{
    Element element;
    struct Node_t *next;
}Node;

/* Linkedlist stuct includes the provided copy, free, delete & equal element functions as well pointers to head and end of list and length*/
struct linkedList_s
{
    int listLength;
    struct Node_t *head;
    struct Node_t *end;
    CopyFunction _copyElement;
    FreeFunction _freeElement;
    PrintFunction _printElement;
    EqualFunction _equalElement;
};

/* Node initializer for linked list - requires linked list to which the node will be added (for copy function) and element to add */
Node* initNode(linkedList linked_list, Element element)
{
    if (linked_list == NULL || element == NULL )
        return NULL;
    
    Element newElement = linked_list->_copyElement(element);
    if (newElement == NULL)
        return NULL;
    
    Node *pNode = (Node*) malloc(sizeof(Node));
    pNode->element = newElement;
    pNode->next = linked_list->end; // in this implementation each new node will always be appended to the end of the list
    return pNode;
}

/* Create an instance of a LinkedList using provided functions which define element interactions */
/* Besides the functions, a linkedlist has head and end nodes and saves list length for ease of use */
linkedList createLinkedList(CopyFunction copyEle, PrintFunction printEle, FreeFunction freeEle, EqualFunction equalEle)
{
    if (copyEle == NULL || printEle == NULL || freeEle == NULL || equalEle == NULL)     // Check inputs are valid
        return NULL;

    linkedList linked_list = (linkedList) malloc(sizeof(struct linkedList_s));
    if (linked_list == NULL)
        return NULL;
    
    linked_list->_copyElement = copyEle;
    linked_list->_freeElement = freeEle;
    linked_list->_printElement = printEle;
    linked_list->_equalElement = equalEle;

    linked_list->listLength = 0;
    linked_list->head = (Node*) NULL;
    linked_list->end = (Node*) NULL;
    return linked_list;
}

/* Deletes all nodes in linkedList by iterating on list from head until and deleting each node */
status destroyList(linkedList linked_list)
{
    if (linked_list == NULL)
        return BadArgs;

    Node *tmp = linked_list->head;
    status stat = success;
    while(tmp != NULL){
        stat = deleteNode(linked_list, tmp->element);   // Delete head of linkedlist
        if (stat != success)
            return stat;
        tmp = linked_list->head;                        // set tmp to point to the new head of the list and keep clearing until head is NULL
   }
   free(linked_list);
   return stat;
}

/* Initialize Node from element and Append to the end of the provided linkedList */
status appendNode(linkedList linked_list, Element element)
{
    if (linked_list == NULL || element == NULL)
        return BadArgs;
    
    Node *newNode = initNode(linked_list, element);
    if (newNode == NULL)
        return BadMemoryAllocation;

    if(linked_list->head == NULL)       // if head is NULL, i.e. empty list, make head point to the new node
        linked_list->head = newNode;
    
    else{                                // otherwise, make end point to newNode
        Node *tmp = linked_list->head;
        while(1){
            if (tmp->next == linked_list->end){
                tmp->next = newNode;    // Add newNode at the end of the list
                break;
            }
            tmp = tmp->next;
        }
    }
    linked_list->listLength++;
    return success;
}

/* deletes the specified elemenet from linkedlist - find element using equal function and free using free function */
status deleteNode(linkedList linked_list, Element element)
{
    if (linked_list == NULL || element == NULL)
        return BadArgs;

    if (linked_list->head == NULL)      // Check if list is already empty
        return EmptyStructure;

    // Check if element is the first element in the list, free element in node and make head point to next in Node in list
    Node *tmp = linked_list->head;
    status stat = success;
    if (linked_list->_equalElement(linked_list->head->element, element) == true)    
    {
        stat = linked_list->_freeElement(linked_list->head->element);
        if (stat != success)
            return stat;
        linked_list->head = linked_list->head->next;
    }
    else
    {
        Node *prev = linked_list->head;
        while(linked_list->_equalElement(tmp->element, element) != true){
            prev = tmp;
            tmp = tmp->next;
            if (tmp == NULL)
                return failure;     // return failure if a matching element was not found
        }
        prev->next = tmp->next;
        stat = linked_list->_freeElement(tmp->element);
        if (stat != success)
            return stat;
    }
    if (tmp != NULL)    // if a Node was found containing the element free the Node, this is only after the element was freed
        free(tmp);
    linked_list->listLength--;
    return success;
}

/* Iterate over list and print each node according to provided print function */
status displayList(linkedList linked_list)
{
    if (linked_list == NULL)
        return BadArgs;

    if (linked_list->head == NULL)      // Check if list is empty
        return EmptyStructure;
    
    Node *tmp = linked_list->head;
    status stat = success;
    while (tmp != NULL){
        stat = linked_list->_printElement(tmp->element);
        if (stat != success)
            return stat;
        tmp = tmp->next;
    }
    return success;

}

/* Find and return element in linked list according to index of the element in the list. Index ranges between 1 and NumOfElemenets */
Element getDataByIndex(linkedList linked_list, int index)
{
    if (linked_list == NULL)
        return NULL;
    
    if (index <=0 || index > linked_list->listLength)   // check that index is valid
        return NULL;

    Node *tmp = linked_list->head;
    status stat = success;
    for (int i=1; i <= index; i++){
        if (i == index)
            return linked_list->_copyElement(tmp->element);
        tmp = tmp->next;
    }
    return success;    
}

/* Return the length of the list as int. List length is tracked and updated when an element is added or removed */
int getLengthList(linkedList linked_list)
{
    if (linked_list == NULL)
        return 0;
    return linked_list->listLength;
}

/* Find and return element in linked list according to equal function provided by user */
Element searchByKeyinList(linkedList linked_list, Element element)
{
    if (linked_list == NULL || element == NULL)
        return NULL;

    Node *tmp = linked_list->head;
    bool test = false;
    while (tmp != NULL){
        test = linked_list->_equalElement(tmp->element, element);
        if (test == true)
            return linked_list->_copyElement(tmp->element);
        tmp = tmp->next;
    }
    return NULL;    
}

