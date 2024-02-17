#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 300
#define DELIM ","
#define SAFE_FREE(var) {if (var != NULL) {free(var);}}
#define ALLOCATE(var,type,num) {if((var = (type*)malloc((num)*sizeof(type))) == NULL) {return NULL; }}
#define CLOSE_FILE(file_ptr, line_ptr) {fclose(file_ptr); SAFE_FREE(line); }
#define FREE_PTR_SET_NULL(ptr) { free(ptr); ptr = NULL; }

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure, BadArgs, BadMemoryAllocation, EmptyStructure } status;

typedef void * Element;

typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);

#endif /* DEFS_H_ */