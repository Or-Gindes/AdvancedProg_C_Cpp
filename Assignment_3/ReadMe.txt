Advanced Programming - Assignment 3 - C Second
Author: Or Gindes
ID: 201640042

DataStructures used in Assignment:
LinkedList is a Generic ADT which stores provided elements in it's Nodes and each node holds a pointer to the next node in the LinkedList

KeyValuePair is a Generic ADT which stores a Key and a Value. each can be a different type of element.

HashTable is an array of fixed size provided by user which uses a hashfunction on provided Key to store LinkedLists of KeyValuePairs
in each of its array 'buckets'. Collisions in index are handled by linking the new KeyValuePair to the end of the existing LinkedList in the index.

MultiValueHashTable uses HashTable functionlity with LinkedLists and MultiValue functions passed as ValueFunctions to HashTable to create a generic ADT
where keys of hashtable are unchanged but the values can be LinkedList themselves, i.e. each 'bucket' stores key: LinkedList KeyValuePair and 
index Collisions are chained as in the regular HashTable.

These data DataStructures are used by JerryBoreeMain such that Jerries data is stored once in a HashTable (JerryBoree), so the HashTable receives 
a DeepCopy functions to store the Jerries. Jerry Id is also stored in a LinkedList in order of admission. this is only the ID which is used to retrive data from the HashTable
Finally, a pointer to Jerry data is stored under matching PhysicalCharacteristics keys in the MultiValueHashTable (JerryCharacteristics)
which allows for quick retrival of data based on PhysicalCharacteristics as well as ID from the regular HashTable.

Hashfunction used for strings is the sum of ASCII values in keys.
HashNumber for the tables is chosen as the smallest Prime Number larger than (number of rows in file - number of planets - 2)
Row number (excluding planets and titles) is indication of worstcase number of jerries + properties.
Creating a hashtable of this size makes sure space is available for file parsing and a number of additions over the course of the program.
a prime number is chosen to reduce clustering around specific indices in case of Collisions.
