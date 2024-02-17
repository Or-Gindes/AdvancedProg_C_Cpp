#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"

/* The MultiValueHashTable stucture supports Hashtable functionallty with the exception */
/* that values for each bucket in the table can be linked lists instead of a single value */

struct multiValueHashTable_s
{
    hashTable svTable;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
};

/* Private functions - Support functions for use of LinkedList ADT with KeyValuePair Nodes */

/* CopyFunction for HashTable which stores LinkedList Values - shallow copy */
Element copyMultiValue(Element elem)
{
    if (elem == NULL)
        return NULL;
    
    linkedList newList = (linkedList)elem;
    
    return newList;
}

/* PrintFunction for HashTable which stores LinkedList Values */
status printMultiValue(Element elem)
{
    if (elem == NULL)
        return failure;

    linkedList value_list = (linkedList) elem;
    return displayList(value_list);
}

/* FreeFunction for HashTable which stores LinkedList Values */
status freeMultiValue(Element elem)
{
    if (elem == NULL)
        return failure;

    return destroyList((linkedList) elem);
}


/* Validate inputs, allocate memory */
multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || equalKey == NULL)     // Validate Key inputs
        return NULL;
    
    if (copyValue  == NULL || freeValue == NULL || printValue == NULL)                  // Validate Value inputs
        return NULL;
    
    if (transformIntoNumber == NULL || hashNumber <= 0)                                 // Validate HashTable inputs
        return NULL;

    multiValueHashTable mvTable = (multiValueHashTable) malloc(sizeof(struct multiValueHashTable_s));
    if (mvTable == NULL)
        return NULL;

    mvTable->svTable = createHashTable(copyKey, freeKey, printKey, copyMultiValue, freeMultiValue, printMultiValue, equalKey, transformIntoNumber, hashNumber);
    if (mvTable->svTable == NULL){
        free(mvTable);
        return NULL;
    }
    mvTable->printKey = printKey;
    mvTable->copyValue = copyValue;
    mvTable->freeValue = freeValue;
    mvTable->printValue = printValue;
    mvTable->equalKey = equalKey;
    return mvTable;
}

/* Destory MultiValueHashtable using appropriate destroy functions */
status destroyMultiValueHashTable(multiValueHashTable mvTable)
{
    if (mvTable == NULL)
        return BadArgs;
    
    status destory_stat = destroyHashTable(mvTable->svTable);
    free(mvTable);

    return destory_stat;
}

/* Add a list of elements to the MultiValueHashTable; Keys in the table are unique, new value for existing key is appended to value list */
status addToMultiValueHashTable(multiValueHashTable mvTable, Element key, Element value)
{
    if (mvTable == NULL || key == NULL || value == NULL)
        return BadArgs;
    
    status stat = success;
    Element linked_list = lookupInHashTable(mvTable->svTable, key);
    if (linked_list == NULL){                                                 // key not found in HashTable
        linkedList value_list = createLinkedList(mvTable->copyValue, mvTable->printValue, mvTable->freeValue, mvTable->equalKey);
        if (value_list == NULL)
            return BadMemoryAllocation;
        stat = appendNode((linkedList) value_list, value);
        if (stat != success){
            destroyList(value_list);
            return failure;
        }
        stat = addToHashTable(mvTable->svTable, key, value_list);
        return stat;
    }
    else{                                                                    // key found, append value to list of values
        status stat = appendNode((linkedList) linked_list, value);
        return stat;
    }
}

/* Search a Key in the MultiValueHashTable - if found, return the list of values associated with this key */
Element lookupInMultiValueHashTable(multiValueHashTable mvTable, Element key)
{
    if (mvTable == NULL || key == NULL)
        return NULL;
    
    return lookupInHashTable(mvTable->svTable, key);
    
}

/* Remove entire value of part of value from key in the MultiValueHashTable - according to user provided free functions */
status removeFromMultiValueHashTable(multiValueHashTable mvTable, Element key, Element value)
{
    if (mvTable == NULL || key == NULL || value == NULL)
        return BadArgs;
    
    Element value_list = lookupInHashTable(mvTable->svTable, key);
    if (value_list == NULL)
        return failure;    
    
    status delete_stat = deleteNode((linkedList) value_list, value);
    if (delete_stat == success && getLengthList((linkedList) value_list) == 0)          // if list is empty after value deletion remove key from table
        delete_stat = removeFromHashTable(mvTable->svTable, key);
    
    return delete_stat;
}

/* Print multiValueHashTable Elements by index in order of key - value using user provided print functions */
status displayMultiValueHashTable(multiValueHashTable mvTable, Element key)
{
    if (mvTable == NULL || key == NULL)
        return BadArgs;

    Element value_list = lookupInHashTable(mvTable->svTable, key);
    if (value_list == NULL)
        return failure;

    mvTable->printKey(key);
    status stat = printMultiValue(value_list);
    return stat;    
}