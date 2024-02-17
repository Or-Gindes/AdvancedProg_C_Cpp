/* Menu for Jerry Module */
/* Author: Or Gindes */
#include "Jerry.h"

/*The following functions are defined here because they are used by only during menu commands - */

/* Define a function to catch failures of any kind while in menu and jump to clean_exit protocol */
#define CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit) {if (stat != success) {goto clean_exit; }}

/* A string allocation function used in menu after reading input to buffer */
/* free var if its not NULL, allocate memory for it based on buffer and copy buffer into it */
#define ALLOCATE_AND_COPY_BUFFER(stat, var, buffer) {SAFE_FREE(var); if((var = (char*)malloc((strlen(buffer) + 1)*sizeof(char))) == NULL) \
 {stat=BadMemoryAllocation; goto clean_exit; } else {strcpy( var, buffer ); }}

/* Because we are given in advance number the of jerries and planets they will be handled in an array */
Jerry** jerry_array = NULL;
Planet** planet_array = NULL;

/* Initialize memory blocks for planet and jerry array of pointers and initialize each element of the arrays to NULL */
status initialize_arrays(int num_planets, int num_jerries)
{
    int i;
    planet_array = malloc(num_planets*sizeof(Planet*));
    jerry_array = malloc(num_jerries*sizeof(Jerry*));
    if ((planet_array == NULL) || (jerry_array == NULL))
        return BadMemoryAllocation;
    for (i=0; i < num_planets; i++)
        planet_array[i] = NULL;
    for (i=0; i < num_jerries; i++)
        jerry_array[i] = NULL;
    return success;
}

/* Function to parse configuration file and initialize planets & jerries */
status parse_config(int num_planets, int num_jerries, char *config_path )
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
    Jerry *jerry_ptr;
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
                
                /* Add the new Physical Characteristic to the last Jerry in array */
                stat = add_property(jerry_array[j-1], prop_name, value);
                if (stat != success){
                    CLOSE_FILE(fp, line);
                    return stat;
                }
            }
            /* Otherwise its a new Jerry to initiate */
            else
            {
                id = strtok(line, DELIM);
                jerry_ptr = search_jerry( jerry_array, id, j);
                if (jerry_ptr != NULL){ /* Duplicate Jerry ID */
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
                jerry_array[j] = jerry_ptr;
                j++;
            }
        }
        i++;
    }
    CLOSE_FILE(fp, line);
    return success;
}

/* iterate jerry array and print all jerry unless runs into an empty pointer */
status print_all_jerries(int num_of_jerries )
{
    status stat = success;
    int i=0;
    if (NULL != jerry_array && num_of_jerries > 0)
    {
        while(stat == success && i < num_of_jerries)
        {
            stat = print_jerry(jerry_array[i]);
            i++;
        }
        return stat;
    }
    return BadArgs;
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

/* Function will print jerry by planet, return BadArgs if planet not in array or false if no jerries found from requested planet */
status print_jerry_by_planet(char *planet_name, int num_planets, int num_jerries )
{
    status stat = failure;
    Planet *planet_ptr = search_planet(planet_array, planet_name, num_planets);
    if (NULL == planet_ptr )
        return BadArgs;
    
    for (int i=0; i < num_jerries; i++)
    {
        if ( strcmp( jerry_array[i]->origin->planet->name, planet_name ) == 0 )
            stat = print_jerry( jerry_array[i] );
    }
    return stat;

}

/* Function will print each jerry that has property name, return false if no jerries found with request property */
status print_jerry_by_property(char *property_name, int num_jerries )
{
    status stat = failure;
    for (int i=0; i < num_jerries; i++)
    {
        for (int j=0; j < jerry_array[i]->number_of_properties; j++)
        {
            if ( strcmp( jerry_array[i]->property_array[j]->name, property_name ) == 0 )
                stat = print_jerry( jerry_array[i] );
        }
    }
    return stat;
}

/* Free each element in either array using relevant destractor and finally free array*/
void delete_arrays(int num_planets, int num_jerries)
{
    int i;
    if (NULL != planet_array){
        for (i=0; i < num_planets; i++)
            delete_planet(planet_array[i]);
        free(planet_array);
    }
    
    if (NULL != jerry_array){
        for (i=0; i < num_jerries; i++)
            delete_jerry(jerry_array[i]);
        free(jerry_array);
    }
}

/* Main function to help Rick get each Jerry to his home */
int main(int argc, char *argv[])
{   /* First - check that all required arguments are provided */
    if (argc<=3)
        return -1;

    /* if all 3 provided assume they are legit (testing input not required) and continue to variable initialization */
    /* Parsing variables */
    int num_planets = atoi(argv[1]);
    int num_jerries = atoi(argv[2]);
    char *config_path = argv[3];

    /* Menu variables */
    status stat = success;
    bool test = false;
    char buffer[BUFFER_SIZE] = {'\0'};
    char ch[2] = {'\0'};
    char *id = NULL;
    char *name = NULL;
    Jerry *p_jerry = NULL;
    
    /* assign memory for array of points to planet and jerry structs which we'll parse from the configuration file */
    stat = initialize_arrays(num_planets, num_jerries);
    CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
    
    /* Parse configuration file and free it's pointer */
    stat = parse_config(num_planets, num_jerries, config_path);
    CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
  
    while( strcmp(ch, "7") != 0 ) {
        printf("AW JEEZ RICK, what do you want to do now ? \n");
        printf("1 : Print all Jerries \n");
        printf("2 : Print all Planets \n");
        printf("3 : Add physical characteristic to Jerry \n");
        printf("4 : Remove physical characteristic from Jerry \n");
        printf("5 : Print Jerries by a planet \n");
        printf("6 : Print Jerries by a physical characteristic \n");
        printf("7 : Go home \n");
        scanf("%1s", ch );
        switch( *ch )
        {
            case '1':  /* Print all Jerries */
                stat = print_all_jerries(num_jerries);
                CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
                break;
 
            case '2':  /* Print all Planets */
                stat = print_all_planets(num_planets);
                CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
                break;
 
            case '3':  /* Add physical characteristic to Jerry */
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = search_jerry( jerry_array, id, num_jerries );

                if( NULL == p_jerry ){
                    printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                }
                else
                {
                    printf("What physical characteristic can you add to Jerry - %s ? \n", id);
                    scanf("%s", buffer);
                    ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                    /* Check if jerry has physical characteristic */
                    test = property_in_jerry( p_jerry, name );
                    if( test == true ){
                        STR_TO_UPPER(name);
                        printf("RICK I ALREADY KNOW HIS %s ! \n", name);
                    }
                    else
                    {
                        printf("What is the value of his %s ? \n", name);
                        scanf("%s", buffer);
                        float property_value = atof(buffer);
                        stat = add_property(p_jerry, name, property_value);
                        CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
                        print_jerry( p_jerry );
                    }
                }
                break;
 
            case '4':  /* Remove physical characteristic from Jerry */
                printf("What is your Jerry's ID ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, id, buffer);
                p_jerry = search_jerry( jerry_array, id, num_jerries );

                if( NULL == p_jerry ){
                    printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                }
                else
                {
                    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
                    scanf("%s", buffer);
                    ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                    /* Check if jerry has physical characteristic */
                    test = property_in_jerry( p_jerry, name );
                    if( test == false ){
                        STR_TO_UPPER(name);
                        printf("RICK I DON'T KNOW HIS %s ! \n", name);
                    }
                    else
                    {
                        stat = remove_property(p_jerry, name);
                        CATCH_FAILURE_CLEAN_EXIT(stat, num_planets, num_jerries, clean_exit);
                        print_jerry( p_jerry );
                    }
                }
                break;
 
            case '5':  /* Print Jerries by a planet */
                printf("What planet is your Jerry from ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                stat = print_jerry_by_planet(name, num_planets, num_jerries);
                STR_TO_UPPER(name);
                if ( stat == failure ){
                    printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n", name);
                }
                else if ( stat == BadArgs ){
                    printf("RICK I NEVER HEARD ABOUT %s ! \n", name);
                }
                break;

            case '6':  /* Print Jerries by a physical characteristic */
                printf("What do you know about your Jerry ? \n");
                scanf("%s", buffer );
                ALLOCATE_AND_COPY_BUFFER(stat, name, buffer);
                stat = print_jerry_by_property(name, num_jerries);
                if (stat == failure){
                    STR_TO_UPPER(name);
                    printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n", name);
                }
                break;

            case '7': /* Go home - free global arrays and pointers used - free is null protected so no need to check */
                delete_arrays(num_planets, num_jerries);
                SAFE_FREE(id);
                SAFE_FREE(name);
                printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
                return 0;

            default:
                printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");
        }
    }
    /* clean exit is a label to jump to in case of failure */
    clean_exit:
        if (stat == BadMemoryAllocation)
            printf("Memory Problem");
        delete_arrays(num_planets, num_jerries);
        SAFE_FREE(id);
        SAFE_FREE(name);
        return -1;
}
