
#ifndef MULTI_VALUE_HASH_TABLE_H
#define MULTI_VALUE_HASH_TABLE_H
#include "Defs.h"

typedef struct multiValueHashTable_s *multiValueHashTable;

multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(multiValueHashTable);
status addToMultiValueHashTable(multiValueHashTable, Element key,Element value);
Element lookupInMultiValueHashTable(multiValueHashTable, Element key);
status removeFromMultiValueHashTable(multiValueHashTable, Element key, Element value);
status displayMultiValueHashTable(multiValueHashTable, Element key);

#endif /* MULTI_VALUE_HASH_TABLE_H */
