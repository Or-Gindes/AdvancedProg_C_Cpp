typedef enum e_bool { false, true } bool ;
typedef enum e_status { success, failure, BadMemoryAllocation, BadArgs } status ;
#define BUFFER_SIZE 300
/* DELIM is the deliminator separating inputs in the configuration files */
#define DELIM ","
/* Morty speaks in ALL CAPS(!!!) need a function to turn strings to STRINGS */
#define STR_TO_UPPER(str) {for(int k=0; k < strlen(str); k++) {str[k] = toupper(str[k]);}}
/* free generally handles NULL values but this helps avoid errors caused by trying to free a pointer that's already freed */
#define SAFE_FREE(var) {if (var != NULL) {free(var);}}
/* A general allocation function used in constructor functions which generally return pointers to structs */
#define ALLOCATE(var,type,num) {if((var = (type*)malloc((num)*sizeof(type))) == NULL) {return NULL; }}
#define CLOSE_FILE(file_ptr, line_ptr) {fclose(file_ptr); SAFE_FREE(line); }