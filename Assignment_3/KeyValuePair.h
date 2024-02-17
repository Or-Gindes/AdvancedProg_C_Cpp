#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"


/* definition of a data structure which holds pairs for elements in Key: Value format */
typedef struct keyValuePair_s *keyValuePair;

/* To create a keyValuePair functions are required to copy, print, free for both key and value and test equality function for key */
keyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, PrintFunction printKey, FreeFunction freeKey, EqualFunction keyEqual, \
    CopyFunction copyVal, PrintFunction printVal, FreeFunction freeVal);

/* Functions which the KeyValuePair ADT supports */
status destroyKeyValuePair(keyValuePair);           // Delete KeyValuePair
status displayValue(keyValuePair);                  // Display Value of KeyValuePair
status displayKey(keyValuePair);                    // Display Key of KeyValuePair
Element getValue(keyValuePair);                     // Return Value Element of KeyValuePair
Element getKey(keyValuePair);                       // Return Key Element of KeyValuePair
bool isEqualKey(keyValuePair, Element);             // Return true if Key in keyValuePair is equal to provided key

#endif /* KEYVALUEPAIR_H_ */