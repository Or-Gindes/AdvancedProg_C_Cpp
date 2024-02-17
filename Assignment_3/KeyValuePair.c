#include "KeyValuePair.h"

/* Define internal Key and Value support structures including their create and destory functions */
typedef struct Key_t
{
    Element key;
    CopyFunction copyKey;
    PrintFunction printKey;
    FreeFunction freeKey;
    EqualFunction keyEqual;
}Key;

typedef struct Value_t
{
    Element value;
    CopyFunction copyVal;
    PrintFunction printVal;
    FreeFunction freeVal;
}Value;

/* keyValuePair_s stuct includes the provided copy, free, delete & equal element functions for key and value element as well as the elements themselves */
struct keyValuePair_s
{
    Key *key;
    Value *value;    
};

Key* createKey(Element key, CopyFunction copyKey, PrintFunction printKey, FreeFunction freeKey, EqualFunction keyEqual)
{
    if (key == NULL || copyKey == NULL || printKey == NULL || freeKey == NULL || keyEqual == NULL)  // Check Key inputs are valid
        return NULL;
    
    Key *pKey = (Key*) malloc(sizeof(struct Key_t));
    if (pKey == NULL)
        return NULL;
    
    Element newKey = copyKey(key);          // Use copy function to copy the key Element
    if (newKey == NULL){
        free(pKey);
        return NULL;
    }

    pKey->key = newKey;
    pKey->copyKey = copyKey;
    pKey->printKey = printKey;
    pKey->freeKey = freeKey;
    pKey->keyEqual = keyEqual;    
    return pKey;
}

Value* createValue(Element value, CopyFunction copyVal, PrintFunction printVal, FreeFunction freeVal)
{
    if (value == NULL || copyVal == NULL || printVal == NULL || freeVal == NULL)                   // Check value inputs are valid
        return NULL;

    Value *pVal = (Value*) malloc(sizeof(struct Value_t));
    if (pVal == NULL)
        return NULL;

    Element newVal = copyVal(value);        // Use copy function to copy the value Element
    if (newVal == NULL){
        free(pVal);
        return NULL;
    }
    
    pVal->value = newVal;
    pVal->copyVal = copyVal;
    pVal->printVal = printVal;
    pVal->freeVal = freeVal;
    return pVal;    
}

status deleteKey(Key *pKey)
{
    status stat = pKey->freeKey(pKey->key);
    free(pKey);
    return stat;
}

status deleteValue(Value *pVal)
{
    status stat = pVal->freeVal(pVal->value);
    free(pVal);
    return stat;
}

/* To create a keyValuePair functions are required to copy, print, free for both key and value and test equality function for key */
keyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, PrintFunction printKey, FreeFunction freeKey, EqualFunction keyEqual, CopyFunction copyVal, PrintFunction printVal, FreeFunction freeVal)
{
    Key *pKey = createKey(key, copyKey, printKey, freeKey, keyEqual);
    if (pKey == NULL)
        return NULL;

    Value *pVal = createValue(value, copyVal, printVal, freeVal);   // if memory allocation for value failed key must be released before returning
    if (pVal == NULL){
        deleteKey(pKey);
        return NULL;
    }

    keyValuePair dict = (keyValuePair) malloc(sizeof(struct keyValuePair_s));
    if (dict == NULL){
        deleteKey(pKey);
        deleteValue(pVal);
        return NULL;
    }
    
    dict->key = pKey;
    dict->value = pVal;
    return dict;
}

/* Functions which the KeyValuePair ADT supports - */

/* Delete KeyValuePair using Key and Value Free functions provided by user */
status destroyKeyValuePair(keyValuePair dict)
{
    if (dict == NULL)
        return BadArgs;

    status statKey = deleteKey(dict->key);
    status statVal = deleteValue(dict->value);
    free(dict);

    if (statKey != success || statVal != success)
        return failure;
    return success;
}

/* Display Value of KeyValuePair using printValue function provided by user */
status displayValue(keyValuePair dict)
{
    if (dict == NULL)
        return BadArgs;

    return dict->value->printVal(dict->value->value);
}          

/* Display Key of KeyValuePair using PrintKey function provided by user */
status displayKey(keyValuePair dict)
{
    if (dict == NULL)
        return BadArgs;

    return dict->key->printKey(dict->key->key);
}

/* Return pointer to Value Element of KeyValuePair found in struct Value */
Element getValue(keyValuePair dict)
{
    if (dict == NULL)
        return NULL;

    return dict->value->value;
}

/* Return pointer to Key Element of KeyValuePair found in struct Key */
Element getKey(keyValuePair dict)
{
    if (dict == NULL)
        return NULL;
        
    return dict->key->key;
}

/* Return true if Key in keyValuePair is equal to provided key */
bool isEqualKey(keyValuePair dict_1, Element key )
{
    if (dict_1 == NULL || key == NULL)
        return false;
        
    return dict_1->key->keyEqual(dict_1->key->key, key);
}
