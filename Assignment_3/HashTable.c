#include "Defs.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

/* The hashTable stucture supports saving of KeyValuePairs in an array of given size */
/* Each 'bucket' in the table is initialized as a LinkedList of KeyValue pairs */
/* The index of the table is evaluated with user defined HashFunction */
/* conflicting indices are chained the the linkedList in the index */

struct hashTable_s
{
    int size;
    linkedList* array;
    CopyFunction copyKey;
    CopyFunction copyValue;
    FreeFunction freeKey;
    FreeFunction freeValue;
    PrintFunction printKey;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction hashFunction;
};

/* Private - calculate modulo of key transformed into int */
int getIndex(hashTable table, Element key)
{
    if (key == NULL || table == NULL)
        return -1; 

    return table->hashFunction(key) % table->size;
}

/* Private functions - Support functions for use of LinkedList ADT with KeyValuePair Nodes */

/* CopyFunction for LinkedList with KeyValuePair Nodes - performs shallow copy of Pairs created in HashTable */
Element copyKeyValuePair(Element elem)
{
    if (elem == NULL)
        return NULL;

    keyValuePair newPair = (keyValuePair)elem;
    return newPair;
}

/* PrintFunction for LinkedList with KeyValuePair Nodes */
status printKeyValuePair(Element elem)
{
    if (elem == NULL)
        return failure;

    keyValuePair pair = (keyValuePair) elem;
    status statkey = displayKey(pair);
    status statval = displayValue(pair);

    if (statkey != success || statval != success)
        return failure;
    
    return success;
}

/* FreeFunction for LinkedList with KeyValuePair Nodes */
status freeKeyValuePair(Element elem)
{
    if (elem == NULL)
        return failure;

    keyValuePair pair = (keyValuePair) elem;
    status stat = destroyKeyValuePair(pair);
    return stat;
}

/* EqualFunction for LinkedList with KeyValuePair Nodes */
bool isPairEqualByKey(Element elem_1, Element elem_2)
{
    if (elem_1 == NULL || elem_2 == NULL)
        return false;

    keyValuePair pair_1 = (keyValuePair) elem_1;
    keyValuePair pair_2 = (keyValuePair) elem_2;
    bool test = isEqualKey(pair_1, getKey(elem_2));
    return test;
}



/* Validate inputs, allocate memory and initialize an array of size hashNumber of LinkedLists where each Node in the list is a KeyValuePair. hashNumber is recommanded to be a Prime number to prevent clustering */
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || equalKey == NULL)     // Validate Key inputs
        return NULL;
    
    if (copyValue  == NULL || freeValue == NULL || printValue == NULL)                  // Validate Value inputs
        return NULL;
    
    if (transformIntoNumber == NULL || hashNumber <= 0)                                 // Validate HashTable inputs
        return NULL;

    hashTable table = (hashTable) malloc(sizeof(struct hashTable_s));
    if (table == NULL)
        return NULL;

    table->array = (linkedList*) malloc(hashNumber * sizeof(linkedList));               // Allocate memory for an array of pointers to linkedLists the size of hashNumber
    if (table->array == NULL){
        free(table);
        return NULL;
    }
    
    table->hashFunction = transformIntoNumber;
    table->size = hashNumber;
    table->copyKey = copyKey;
    table->copyValue = copyValue;
    table->freeKey = freeKey;
    table->freeValue = freeValue;
    table->printKey = printKey;
    table->printValue = printValue;
    table->equalKey = equalKey;

    for (int i=0; i < hashNumber; i++)                                                 // Initialize an empty array
        table->array[i] = NULL;
    
    return table;
}

/* Destory Hashtable using appropriate destroy functions */
status destroyHashTable(hashTable table)
{
    if (table == NULL)
        return BadArgs;

    status destory_stat = success;
    for (int i=0; i < table->size; i++){                                                // Iterate and free list in each array
        if (table->array[i] != NULL){
            destory_stat = destroyList(table->array[i]);                                // DestroyList also frees up KeyValuePairs because of the freeKeyValuePair function passed into it
            if (destory_stat != success)
                return failure;
        }
    }
    
    free(table->array);
    free(table);
    return destory_stat;
}

/* Add element to HashTable; Keys in Hashtable are unique, duplicated keys will return failure */
status addToHashTable(hashTable table, Element key, Element value)
{
    if (table == NULL || key == NULL || value == NULL)
        return BadArgs;
    
    int index = getIndex(table, key);       // get Index into which to insert the input using the HashFunction 
    if (index >= table->size)
        return failure;

    Element newPair = (Element) createKeyValuePair(key, value, table->copyKey, table->printKey, table->freeKey, table->equalKey, table->copyValue, table->printValue, table->freeValue);
    if (newPair == NULL)
        return BadMemoryAllocation;
    
    if (table->array[index] == NULL){
        table->array[index] = createLinkedList(copyKeyValuePair, printKeyValuePair, freeKeyValuePair, isPairEqualByKey);
        
        if (table->array[index] == NULL){
            destroyKeyValuePair(newPair);
            return BadMemoryAllocation;
        }
    }
    else                                        // Need to check for conflicts in key before we append new pair to existing list
    {
        if (searchByKeyinList(table->array[index], newPair) != NULL){
            destroyKeyValuePair(newPair);
            return BadArgs;
        }
    }           

    // no conflicts were found - append newPair to list in index
    status append_stat = appendNode(table->array[index], newPair);
    if (append_stat != success)
        destroyKeyValuePair(newPair);
        
    return append_stat;
}

/* Search a Key in the HashTable */
Element lookupInHashTable(hashTable table, Element key)
{
    if (table == NULL || key == NULL)
        return NULL;
    
    int index = getIndex(table, key);       // get Index into which to insert the input using the HashFunction 
    if (index >= table->size)
        return NULL;
    
    if (table->array[index] == NULL)        // index is empty, no need to search for key
        return NULL;

    keyValuePair pair;
    for (int i=1; i <= getLengthList(table->array[index]); i++){
        pair = (keyValuePair) getDataByIndex(table->array[index], i);
        if (pair != NULL){
            if (isEqualKey(pair, key) == true)
                return getValue(pair);
        }
    }
    return NULL;
}

/* Remove element by Key in the HashTable */
status removeFromHashTable(hashTable table, Element key)
{
    if (table == NULL || key == NULL)
        return BadArgs;
    
    int index = getIndex(table, key);       // get Index into from which to remove a KeyValuePair using the HashFunction 
    if (index >= table->size)
        return BadArgs;
    
    if (table->array[index] == NULL)
        return BadArgs;
    
    keyValuePair pair;
    for (int i=1; i <= getLengthList(table->array[index]); i++){
        pair = (keyValuePair) getDataByIndex(table->array[index], i);
        if (pair != NULL){
            if (isEqualKey(pair, key) == true)
                return deleteNode(table->array[index], pair);
        }
    }
    return failure;
}

/* Print HashTable Elements by index in order of key - value using user provided print functions */
status displayHashElements(hashTable table)
{
    if (table == NULL)
        return BadArgs;

    status print_stat = success;
    for (int i=0; i < table->size; i++){
        print_stat = displayList(table->array[i]);
        if (print_stat == failure)
            return print_stat;
    }
    return print_stat;
}
