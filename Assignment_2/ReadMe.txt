Advanced Programming - Assignment 2 - C
Author: Or Gindes
ID: 201640042

Module structure - 
Jerry module is comprised of four different structures - 
1. Planet                   (name (unique), x, y, z)
2. Origin                   (dimension, Planet)
3. PhysicalCharacteristics  (name, value)
4. Jerry                    (id (unique), happiness, Origin, PhysicalCharacteristics_array)

Entity functions -
Each entity in the module has an init and delete functions in addition to whatever other functions are needed
by the module or by the ManageJerries.
All functions used by the ManageJerries are declared in Jerry.h but some static functions which are only used by the module
were not (e.g. Origin and PhysicalCharacteristic related functions)

Data Structure and ManageJerries vs Jerry responsibilities - 
In this assignment a user provided number of Jerries and Planets were parsed from configuration file.
Additionally, there is no way to add planets or jerries once input has been provided.
Therefore, it was decided to handle these in an array where the memory allocation can be done in advance.
In a future assignment it is possible we will be required to have this option and we might consider a different data structure,
for that reason parsing the files as well as the arrays (including memory allocate and deallocate) and element duplication prevention 
are handled in ManageJerries and not in the module itself (duplication prevention wasn't required but still implemented).

PhysicalCharacteristics which can be added during run are still handled as an array because we were required 
to not take up more memory than needed (eliminating linked lists for example).
this is handled by using realloc to allocate or deallocate memory to the PhysicalCharacteristics_array as needed
when properties are added or removed.

Data parsing assumes valid inputs and configuration file strucutre as guaranteed in the assignment.
if the file didn't match specified design (e.g. planets before jerries).

Error handling - 
Each function that returns a status that isn't success (i.e. failure, BadArgs or BadMemoryAllocation) 
will return the relevant type of status. e.g. a print function receving null pointers will return failure
where as duplicated planets or missing configuration will return BadArgs.
Additionally, functions that return pointers (inits & searches) will return NULL if failed.
Any status/NULL pointer that isn't a success is handled by main, sometimes a message is printed (e.g. Jerry not found by search)
or sent to 'clean_exit' label in main for memory clean and exit.
In case the last status which sent main to 'clean_exit' protocol was BadMemoryAllocation a MemoryProblem message will be printed.