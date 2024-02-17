/* Menu for JerryBoreeMain */
/* Author: Or Gindes */
#include "Jerry.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"

/*The following functions are defined here because they are used by only during menu commands - */

/* Define a function to catch failures of any kind while in menu and jump to clean_exit protocol */
#define CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit) {if (stat != success) {goto clean_exit; }}

/* A string allocation function used in menu after reading input to buffer */
/* free var if its not NULL, allocate memory for it based on buffer and copy buffer into it */
#define ALLOCATE_AND_COPY_BUFFER(stat, var, buffer) {SAFE_FREE(var); if((var = (char*)malloc((strlen(buffer) + 1)*sizeof(char))) == NULL) \
 {stat=BadMemoryAllocation; goto clean_exit; } else {strcpy( var, buffer ); }}

/* Because we are given in advance number the of planets they will be handled in an array */
Planet** planet_array = NULL;

/* Initialize memory blocks for planet and jerry array of pointers and initialize each element of the arrays to NULL */
status initialize_arrays(int num_planets)
{
    int i;
    planet_array = malloc(num_planets*sizeof(Planet*));
    if ((planet_array == NULL))
        return BadMemoryAllocation;
    for (i=0; i < num_planets; i++)
        planet_array[i] = NULL;
    return success;
}

/* support functions for HashTable Keys which are strings (Jerry ID / PhysicalCharacteristic Name) */
Element copyString(Element elem)
{
    if (elem == NULL)
        return NULL;

    char *string = (char*)elem;
    char *newString = (char*)malloc(sizeof(char) * (strlen(string)+1));
    if (newString == NULL)
        return NULL;

    strcpy(newString, string);
    if (newString != NULL)
        return newString;
    return NULL;
}

status freeString(Element elem)
{
    if (elem == NULL)
        return BadArgs;

    free ((char*)elem);
    return success;
}

bool equalString(Element elem_1, Element elem_2)
{
    if (elem_1 == NULL || elem_2 == NULL)
        return false;

    if (strcmp((char*)elem_1, (char*)elem_2) == 0)
        return true;
    else
        return false;
}

bool equalJerry(Element elem_1, Element elem_2)
{
    if (elem_1 == NULL || elem_2 == NULL)
        return false;

    Jerry* jerry_1 = (Jerry*)elem_1;
    Jerry* jerry_2 = (Jerry*)elem_2;

    return equalString(jerry_1->id, jerry_2->id);
}

status printString(Element elem)
{
    if (elem == NULL)
        return BadArgs;

    printf("%s : \n", (char*)elem);
    return success;
}

status doNothing(Element elem)
{
    return success;
}

int transformString(Element elem)
{   
    if (elem == NULL)
        return -1;
        
    char *string = (char*)elem;
    int ascii_sum = 0;
    for (int i=0; i < strlen(string); i++)
        ascii_sum += string[i];
    return ascii_sum;
}

/* support functions for HashTable values which are Jerries */

Element DeepCopyJerry(Element elem)
{
    if (elem == NULL)
        return NULL; 

    Jerry* jerry = (Jerry*)elem;
    Jerry* newJerry = init_jerry(jerry->id, jerry->happiness, jerry->origin->planet, jerry->origin->dimension);
    if (newJerry == NULL)
        return NULL;

    status property_status = success;
    for (int i=0; i < jerry->number_of_properties; i++){
        property_status = add_property(newJerry, jerry->property_array[i]->name, jerry->property_array[i]->value);
        if (property_status != success)
            return NULL;
    }
    return newJerry;
}

Element copyJerry(Element elem)
{
    if (elem == NULL)
        return NULL;
    Jerry* newJerry = (Jerry*)elem;
    return newJerry;
}

status freeJerry(Element elem)
{
    if (elem == NULL)
        return BadArgs;

    return delete_jerry((Jerry*)elem);
}

status printJerry(Element elem)
{
    if (elem == NULL)
        return BadArgs;
    
    return print_jerry((Jerry*)elem);
}

/* Search planet in array by planet name */
Planet* search_planet( Planet** planet_array, char *name, int number_of_planets)
{
   for (int i=0; i < number_of_planets; i++)
   {
      if( strcmp(planet_array[i]->name, name ) == 0 )
         return planet_array[i];
   }
   return NULL;
}

/* Support functions for MultiValueHashTable usage which receives values as lists */

/* Function to parse configuration file and initialize planets & jerries */
status parse_config(int num_planets, char *config_path, hashTable JerryBoree, multiValueHashTable JerryCharacteristics, linkedList JerryIdList)
{
    /* initialize file read variables */
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int j = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    status stat = success;

    /* initialize planet variables */
    Planet *planet_ptr;
    char *pname = NULL;
    float x,y,z;
    /* initialize jerry variables */
    Jerry *jerry_ptr = NULL;
    Jerry *tabled_jerry = NULL;
    char *id, *dim;
    int happiness = 0;
    /* initialize Physical Characteristics variables */
    PhysicalCharacteristic* property_ptr;
    char *prop_name;
    float value;

    fp = fopen(config_path, "r");
    /* Return failure if no configuration file was found - shouldn't happen because input is assumed to be valid */
    if ( fp == NULL )
        return BadArgs;
    
    /* Iterate over line in configuration file and count line number in i */
    while ((read = getline(&line, &len, fp)) != -1) {

        /* First line is "Planets" followed by {num_planets} rows of planetName,x,y,z  */
        /* Initialize planet of row i , 0 < i <= num_planets and add planet pointer to array */
        if ( i > 0 && i <= num_planets ){
            if ( sscanf ( line, "%[^,],%f,%f,%f\n", buffer, &x, &y, &z) == 4){
                pname = malloc(strlen(buffer) * sizeof(char) + 1);
                if( pname == NULL ){
                    CLOSE_FILE(fp, line);
                    return BadMemoryAllocation;
                }
                strcpy(pname, buffer);

                planet_ptr = search_planet( planet_array, pname, i-1);
                if (planet_ptr != NULL){ /* Duplicate Planet Name */
                    CLOSE_FILE(fp, line);
                    free(pname);
                    return BadArgs;
                }
                
                planet_ptr = init_planet(pname, x, y, z);
                free(pname);
                if ( NULL == planet_ptr ){
                    CLOSE_FILE(fp, line);
                    return BadMemoryAllocation;
                }
                planet_array[i-1] = planet_ptr;
            }
        }
        /* Jerries start at row num_planets + 1 after Jerries title */
        if ( i > (num_planets + 1) )
        {
            /* If line starts with \t it's a Physical Characteristic line for previous Jerry */
            if ( strncmp(line, "\t", 1) == 0 ){
                
                /* copy line into buffer without the "\t" char to get Property_name:Property_value\n */
                memcpy(buffer, line + 1, strlen(line)-1);
                prop_name = strtok(buffer, ":");
                value = atof(strtok(NULL, "\n"));
                
                /* Add the new Physical Characteristic to the last Jerry which was put into the JerryBoree */
                tabled_jerry = lookupInHashTable(JerryBoree, jerry_ptr->id);
                stat = add_property(tabled_jerry, prop_name, value);
                if (stat != success){
                    CLOSE_FILE(fp, line);
                    return stat;
                }
                /* Add a pointer to the tabled Jerry under the JerryCharacteristics MultiValue table*/
                stat = addToMultiValueHashTable(JerryCharacteristics, prop_name, tabled_jerry);
                if (stat != success){
                    CLOSE_FILE(fp, line);
                    return stat;
                } 
            }
            /* Otherwise its a new Jerry to initiate */
            else
            {
                // if jerry_ptr isn't null we can add it to the JerryBoree HashTable and delete it since copyJerry function makes a deepcopy and we don't want to keep duplicates
                // This is done here so we're sure we finished adding any Physical Characteristic to this jerry because we're moving on to the next one.
                if (jerry_ptr != NULL){
                    stat = delete_jerry(jerry_ptr);
                    if (stat != success){
                        CLOSE_FILE(fp, line);
                        return stat;
                    }
                }
                
                id = strtok(line, DELIM);
                jerry_ptr = lookupInHashTable(JerryBoree, id);
                if (jerry_ptr != NULL){         /* Duplicate Jerry ID */
                    CLOSE_FILE(fp, line);
                    return BadArgs;
                }
                dim = strtok(NULL, DELIM);
                pname = strtok(NULL, DELIM);
                happiness = atoi(strtok(NULL, DELIM));
                planet_ptr = search_planet( planet_array, pname, num_planets);
                jerry_ptr = init_jerry( id, happiness, planet_ptr, dim);
                
                if ( NULL == jerry_ptr ){
                    CLOSE_FILE(fp, line);
                    return BadMemoryAllocation;
                }

                stat = appendNode(JerryIdList, jerry_ptr->id);
                if (stat != success){
                    CLOSE_FILE(fp, line);
                    return stat;
                }
                stat = addToHashTable(JerryBoree, jerry_ptr->id, jerry_ptr);
                if (stat != success){
                    CLOSE_FILE(fp, line);
                    return stat;
                }
            }
        }
        i++;
    }
    // delete pointer to final jerry
    if (jerry_ptr != NULL){
        delete_jerry(jerry_ptr);
    }
    CLOSE_FILE(fp, line);
    return success;
}

/* iterate planet array and print all planets unless runs into an empty pointer */
status print_all_planets(int num_of_planets )
{
    status stat = success;
    int i=0;
    if (NULL != planet_array && num_of_planets > 0)
    {
        while(stat == success && i < num_of_planets)
        {
            stat = print_planet(planet_array[i]);
            i++;
        }
        return stat;
    }
    return BadArgs;
}

status print_all_jerries(linkedList JerryIdList, hashTable JerryBoree)
{
    if (getLengthList(JerryIdList) < 1){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return EmptyStructure;
    }
    char *id = NULL;
    Jerry *jerry = NULL;
    for (int i=1; i <= getLengthList(JerryIdList); i++){
        id = (char*) getDataByIndex(JerryIdList, i);
        jerry = (Jerry*) lookupInHashTable(JerryBoree, id);
        print_jerry(jerry);
        FREE_PTR_SET_NULL(id);
    }
    return success;
}

/* Support function to take Jerries on a custom activity and change their happiness */
status JerriesActivity(linkedList JerryIdList, hashTable JerryBoree, int limit, int bonus, int penalty)
{
    if (JerryIdList == NULL || JerryBoree == NULL)
        return BadArgs;
        
    char *id = NULL;
    Jerry* jerry = NULL;
    int newHappiness = 0;
    for (int i=1; i <= getLengthList(JerryIdList); i++){
        id = (char*) getDataByIndex(JerryIdList, i);
        jerry = (Jerry*) lookupInHashTable(JerryBoree, id);      
        if (getHappiness(jerry) >= limit)
            newHappiness = getHappiness(jerry) + bonus;
        else
            newHappiness = getHappiness(jerry) - penalty;
        setHappiness(jerry, newHappiness);
        FREE_PTR_SET_NULL(id);
    }
    printf("The activity is now over ! \n");
    return print_all_jerries(JerryIdList, JerryBoree);
}

/* Free each element in either array using relevant destractor and finally free array*/
void delete_planet_array(int num_planets)
{
    int i;
    if (NULL != planet_array){
        for (i=0; i < num_planets; i++)
            delete_planet(planet_array[i]);
        free(planet_array);
    }
}

int count_lines(char *config_path)
{
    FILE *fp;
    int count = 0;  // Line counter (result)
    char c;  // To store a character read from file
 
    fp = fopen(config_path, "r");
    if ( fp == NULL )
        return 0;
 
     for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    fclose(fp);
    return count;
}

bool isPrime(int n)
{
    // Corner cases
    if (n <= 1) return false;
    if (n <= 3) return true;
   
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}

int nextPrime(int n)
{
    if (n <= 1)
        return 2;
    
    int prime = n;
    while (isPrime(prime) == false){
        prime++;
    }
    return prime;
}

/* Main function to run the JerryBoree */
int main(int argc, char *argv[])
{   
    /* First - check that all required arguments are provided */
    if (argc<=2)
        return -1;

    /* if bitg provided assume they are legit (testing input not required) and continue to variable initialization */
    /* Parsing variables */
    int num_planets = atoi(argv[1]);
    char *config_path = argv[2];

    /* Menu variables */
    status stat = success;
    bool test = false;
    char buffer[BUFFER_SIZE] = {'\0'};
    char *id = NULL;
    char *name = NULL;
    char *dim = NULL;
    int happiness = 0;
    float diff = INFINITY;                       // set diff to be a very large number
    float property_value = 0.0;
    Planet *p_planet = NULL;
    Jerry *p_jerry = NULL;
    Jerry *candidate_jerry = NULL;
    int lines_counter = count_lines(config_path);

    /* Save Jerry ID's in a linkedlist by order of insert for later search in the HashTable */
    linkedList JerryIdList = createLinkedList(copyString, printString, freeString, equalString);

    // The JerryBoree is only starting out and doesn't require a lot of room (some Jerries can share rooms). A Prime number of rooms can reduce clustering
    int hashNumber = nextPrime(lines_counter - num_planets - 2);
    /* Create a SingleValue HashTable to hold Jerries by Unique ID as key */
    hashTable JerryBoree = createHashTable(copyString, freeString, doNothing, DeepCopyJerry, freeJerry, printJerry, equalString, transformString, hashNumber);
    if (JerryBoree == NULL){
        printf("Memory Problem");
        return -1;
    }
    /* Create a MultiValueHashTable to hold a list of pointers to Jerries under Physical characteristics string keys */
    /* This Hashtable only does shallow copies of Jerry pointers and isn't required to free Jerries */
    multiValueHashTable JerryCharacteristics = createMultiValueHashTable(copyString, freeString, printString, copyJerry, doNothing, printJerry, equalString ,transformString, hashNumber);
    if (JerryCharacteristics == NULL){
        printf("Memory Problem");
        return -1;
    }
    /* assign memory for array of points to planet and jerry structs which we'll parse from the configuration file */
    stat = initialize_arrays(num_planets);
    CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
    
    /* Parse configuration file and free it's pointer */
    stat = parse_config(num_planets, config_path, JerryBoree, JerryCharacteristics, JerryIdList);
    CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
    
  
    while(1) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s[^\n]", buffer );
        if (strlen(buffer) != 1)                         // Only inputs with length == 1 are valid
            strcpy(buffer, "default");
        switch( *buffer )
        {
            case '1':  /* Leave Jerry in daycare */
                // Request Jerry ID / test in O(1) if ID already in system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = lookupInHashTable(JerryBoree, id);
                if (p_jerry != NULL){
                    printf("Rick did you forgot ? you already left him here ! \n");
                    FREE_PTR_SET_NULL(id);
                    break;
                }

                // If Jerry is new, request planet name and check if in system
                printf("What planet is your Jerry from ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                p_planet = search_planet( planet_array, name, num_planets );
                if (p_planet == NULL){
                    printf("%s is not a known planet ! \n", name);
                    FREE_PTR_SET_NULL(id);
                    FREE_PTR_SET_NULL(name);
                    break;
                }
                
                // If planet was found ask dimension and happiness and init jerry using values. If successful print this jerry
                printf("What is your Jerry's dimension ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, dim, buffer);
                printf("How happy is your Jerry now ? \n");
                scanf("%s", buffer );
                happiness = atoi(buffer);
                p_jerry = init_jerry(id, happiness, p_planet, dim);
                stat = addToHashTable(JerryBoree, id, p_jerry);
                if ( stat != success )
                    goto clean_exit;

                stat = appendNode(JerryIdList, id);
                if ( stat != success )
                    goto clean_exit;

                print_jerry(p_jerry);
                delete_jerry(p_jerry);
                FREE_PTR_SET_NULL(id);
                FREE_PTR_SET_NULL(name);
                FREE_PTR_SET_NULL(dim);
                break;
 
            case '2':  /* Add Physical Attribute to a Jerry */
                // Request Jerry ID and verify it's in system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = lookupInHashTable(JerryBoree, id);
                if (p_jerry == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    FREE_PTR_SET_NULL(id);
                    break;
                }
                
                // If Jerry is found request physical characteristic to add to Jerry
                printf("What physical characteristic can you add to Jerry - %s ? \n", id);
                scanf("%s", buffer);
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                // Check if jerry has physical characteristic
                test = property_in_jerry( p_jerry, name );
                if( test == true ){
                    printf("The information about his %s already available to the daycare ! \n", name);
                    FREE_PTR_SET_NULL(id);
                    FREE_PTR_SET_NULL(name);
                    break;
                }

                // if jerry doesn't have property - request value and add it to the jerry, finally print the jerry
                printf("What is the value of his %s ? \n", name);
                scanf("%s", buffer);
                property_value = atof(buffer);  
                stat = add_property(p_jerry, name, property_value);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = addToMultiValueHashTable(JerryCharacteristics, name, p_jerry);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = displayMultiValueHashTable(JerryCharacteristics, name);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                FREE_PTR_SET_NULL(id);
                FREE_PTR_SET_NULL(name);
                break;
 
            case '3':  /* Remove Physical Attribute from Jerry */
                // Request Jerry ID and verify it's in system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = lookupInHashTable(JerryBoree, id);
                if (p_jerry == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    FREE_PTR_SET_NULL(id);
                    break;
                }
                
                // If Jerry is found request physical characteristic to remove from Jerry
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
                scanf("%s", buffer);
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                // Check if jerry has physical characteristic
                test = property_in_jerry( p_jerry, name );
                if( test == false ){
                    printf("The information about his %s not available to the daycare ! \n", name);
                    FREE_PTR_SET_NULL(id);
                    FREE_PTR_SET_NULL(name);
                    break;
                }

                // if jerry has property - remove it from jerry and print jerry
                stat = remove_property(p_jerry, name);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = removeFromMultiValueHashTable(JerryCharacteristics, name, p_jerry);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                print_jerry( p_jerry );
                break;
 
            case '4':  /* Remove Jerry from JerryBoree by ID */
                // Request Jerry ID and verify it's in system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = lookupInHashTable(JerryBoree, id);
                if (p_jerry == NULL){
                    printf("Rick this Jerry is not in the daycare ! \n");
                    FREE_PTR_SET_NULL(id);
                    break;
                }
                if (p_jerry->number_of_properties > 0){
                    for (int i=0; i < p_jerry->number_of_properties; i++){
                        stat = removeFromMultiValueHashTable(JerryCharacteristics, p_jerry->property_array[i]->name ,p_jerry);
                        CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                    }
                }
                stat = deleteNode(JerryIdList, id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = removeFromHashTable(JerryBoree, id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                FREE_PTR_SET_NULL(id);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;
 
            case '5':  /* Remove Jerry from JerryBoree by physical characteristic */
                printf("What do you remember about your Jerry ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                linkedList jerry_list = (linkedList) lookupInMultiValueHashTable(JerryCharacteristics, name);
                    if (jerry_list == NULL){
                        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", name);
                        FREE_PTR_SET_NULL(name);
                        break;
                    }
                printf("What do you remember about the value of his %s ? \n", name);
                scanf("%s", buffer );
                property_value = atof(buffer);
                
                for (int i=1; i <= getLengthList(jerry_list); i++){
                    candidate_jerry = getDataByIndex(jerry_list, i);
                    for (int j=0; j < candidate_jerry->number_of_properties; j++){
                        if (strcmp(candidate_jerry->property_array[j]->name, name) == 0){
                            if (fabs(candidate_jerry->property_array[j]->value - property_value) < diff){
                                diff = fabs(candidate_jerry->property_array[j]->value - property_value);
                                p_jerry = candidate_jerry;
                            }
                        }
                    }
                }
                diff = INFINITY;
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(p_jerry);

                // remove this jerry from the JerryBoree databases
                if (p_jerry->number_of_properties > 0){
                    for (int i=0; i < p_jerry->number_of_properties; i++){
                        stat = removeFromMultiValueHashTable(JerryCharacteristics, p_jerry->property_array[i]->name, p_jerry);
                        CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                    }
                }
                stat = deleteNode(JerryIdList, p_jerry->id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = removeFromHashTable(JerryBoree, p_jerry->id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                FREE_PTR_SET_NULL(name);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;
            
            case '6':  /* Remove Jerry from JerryBoree by lowest happiness */
                if (getLengthList(JerryIdList) < 1){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                // Find saddest Jerry by iterating on Jerries currently in the JerryBoree and saving the lowest found so far
                for (int i=1; i <= getLengthList(JerryIdList); i++){
                    id = (char*) getDataByIndex(JerryIdList, i);
                    candidate_jerry = lookupInHashTable(JerryBoree, id);
                    FREE_PTR_SET_NULL(id);
                    if (getHappiness(candidate_jerry) < diff){
                        p_jerry = candidate_jerry;
                        diff = getHappiness(candidate_jerry);
                    }
                }
                diff = INFINITY;
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(p_jerry);
                // remove this jerry from the JerryBoree databases
                if (p_jerry->number_of_properties > 0){
                    for (int i=0; i < p_jerry->number_of_properties; i++){
                        stat = removeFromMultiValueHashTable(JerryCharacteristics, p_jerry->property_array[i]->name, p_jerry);
                        CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                    }
                }
                stat = deleteNode(JerryIdList, p_jerry->id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                stat = removeFromHashTable(JerryBoree, p_jerry->id);
                CATCH_FAILURE_CLEAN_EXIT(stat, clean_exit);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;
            
            case '7':  /* Print mini-print menu to print All Jerries, All Jerries by Attribute or All Planets */
                printf("What information do you want to know ? \n");
                printf("1 : All Jerries \n");
                printf("2 : All Jerries by physical characteristics \n");
                printf("3 : All known planets \n");
                scanf("%s[^\n]", buffer );
                if (strlen(buffer) != 1)                         // Only inputs with length == 1 are valid
                    strcpy(buffer, "default");
                switch( *buffer ){
                    case '1':
                        print_all_jerries(JerryIdList, JerryBoree);
                        break;
                    
                    case '2':
                        printf("What physical characteristics ? \n");
                        scanf("%s", buffer );
                        ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                        // Find jerries which have this Characterisics in MultiValueHashTable - O(1)
                        linkedList jerry_list = (linkedList) lookupInMultiValueHashTable(JerryCharacteristics, name);
                        if (jerry_list == NULL){
                            printf("Rick we can not help you - we do not know any Jerry's %s ! \n", name);
                            FREE_PTR_SET_NULL(name);
                            break;
                        }
                        stat = displayMultiValueHashTable(JerryCharacteristics, name);
                        FREE_PTR_SET_NULL(name);
                        break;
                    
                    case '3':
                        print_all_planets(num_planets);
                        break;

                    default:
                        printf("Rick this option is not known to the daycare ! \n");
                }
                break;

            case '8':  /* Print mini-activity menu to improve happiness */
                if (getLengthList(JerryIdList) < 1){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                printf("What activity do you want the Jerries to partake in ? \n");
                printf("1 : Interact with fake Beth \n");
                printf("2 : Play golf \n");
                printf("3 : Adjust the picture settings on the TV \n");
                scanf("%s[^\n]", buffer );
                if (strlen(buffer) != 1)                         // Only inputs with length == 1 are valid
                    strcpy(buffer, "default");
                switch( *buffer ){
                    case '1':   /* iterate over Jerries in JerryBoree and have them interact with a fake Beth */
                        JerriesActivity(JerryIdList, JerryBoree, 20, 15, 5);
                        break;
                    
                    case '2':   /* iterate over Jerries in JerryBoree and have them interact with a fake play golf */
                        JerriesActivity(JerryIdList, JerryBoree, 50, 10, 10);
                        break;
                    
                    case '3':   /* iterate over Jerries in JerryBoree and have them Adjust the picture settings on the TV */
                        JerriesActivity(JerryIdList, JerryBoree, 0, 20, 0);
                        break;

                    default:
                        printf("Rick this option is not known to the daycare ! \n");
                }
                break;

            case '9': /* Close down the JerryBoree */
                printf("The daycare is now clean and close ! \n");
                goto clean_exit;
                return 0;

            default:
                printf("Rick this option is not known to the daycare ! \n");
        }
    }
    
    /* clean exit is a label to jump to in case of failure */
    clean_exit:
        if (stat == BadMemoryAllocation)
            printf("Memory Problem");

        delete_planet_array(num_planets);
        destroyMultiValueHashTable(JerryCharacteristics);
        destroyHashTable(JerryBoree);
        destroyList(JerryIdList);
        SAFE_FREE(id);
        SAFE_FREE(name);
        SAFE_FREE(dim);

        if (strcmp(buffer, "9") == 0)
            return 0;
        return -1;
    
    return 0;
}