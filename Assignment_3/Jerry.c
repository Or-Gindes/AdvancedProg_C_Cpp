#include "Jerry.h"

/* Planet related functions */

/* Initialize planet with name and x,y,z locations */
Planet* init_planet( char *p_name, float x, float y, float z )
{
   Planet *planet_ptr;
   /* Allocate memory for planet pointer and for name of planet according to length of name or return NULL if allocation fails */
   ALLOCATE(planet_ptr, Planet, 1);
   ALLOCATE(planet_ptr->name, char, strlen(p_name) + 1);
   /* Memory allocated successfully -> initialize planet values */
   memcpy(planet_ptr->name, p_name, strlen(p_name) + 1);
   planet_ptr->x = x;
   planet_ptr->y = y;
   planet_ptr->z = z;
   return planet_ptr;
}

/* Print planet function assuming pointer is initialized */
status print_planet( Planet* planet_ptr )
{
   if (NULL != planet_ptr){
      printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet_ptr->name, planet_ptr->x, planet_ptr->y, planet_ptr->z);
      return success;
   }
   return failure;
}

/* Delete planet function assuming pointer is initialized, free up memory allocated to planet name and planet itself */
void delete_planet( Planet* planet_ptr )
{
   if (NULL != planet_ptr){
      /* Free up memory allocation for planet name and planet pointer */
      free(planet_ptr->name);
      free(planet_ptr);
   }
}

/* Origin related functions */

/* Initialize origin with dimension name and pointer to a planet struct - Origins are only initiated by Jerries */
static Origin* init_origin( char *dimension, Planet* planet)
{
   if (NULL == planet)
      return NULL;
   Origin *orig_ptr;
   /* Allocate memory for origin pointer and for pointer to dimension according to length of dimension name or return NULL if allocation fails */
   ALLOCATE(orig_ptr, Origin, 1);
   ALLOCATE(orig_ptr->dimension, char, strlen(dimension) + 1);
   /* Memory allocated successfully -> initialize origin values */
   memcpy(orig_ptr->dimension, dimension, strlen(dimension) + 1);
   orig_ptr->planet = planet;
   return orig_ptr;
}

/* Print origin function assuming pointer is initialized - will only be used in print jerry function */
static status print_origin( Origin* origin)
{
   status stat = failure;
   if (NULL != origin){
      printf("Origin : %s \n", origin->dimension);
      stat = print_planet( origin->planet );
      return stat;
   }
   return stat;
}

/* Delete origin function assuming pointer is initialized, free up memory allocated to dimension name, will be called by delete jerry function */
static void delete_origin( Origin* origin )
{
   if (NULL != origin){
      /* Free up memory allocation for origin dimension and origin pointer */
      free(origin->dimension);
      free(origin);
   }
}

/* Initialize PhysicalCharacteristic structure for a Jerry */
static PhysicalCharacteristic* init_property( char *name, float value)
{
   PhysicalCharacteristic *property_ptr;
   /* Allocate memory for physical characteristic */
   ALLOCATE(property_ptr, PhysicalCharacteristic, 1);
   ALLOCATE(property_ptr->name, char, strlen(name) + 1);
   /* Memory allocated successfully -> initialize property values */
   memcpy(property_ptr->name, name, strlen(name) + 1);
   property_ptr->value = value;
   return property_ptr;
}

/* Delete property function to be used when destorying jerry or removing physical Characteristic from jerry */
static void delete_property( PhysicalCharacteristic* property_ptr )
{
   if (NULL != property_ptr){
      /* Free up memory allocation for property name and property pointer */
      free(property_ptr->name);
      free(property_ptr);
   }
}

/* Jerry related functions */

/* Initialize Jerry with id happiness, pointer to a planet struct and dimension which will initialize his origin */
/* a Jerry is initialized with no physical characteristics which will be added elsewhere */
Jerry* init_jerry( char *id, int happiness, Planet* planet, char *dim_name )
{
   Jerry *jerry_ptr;
   /* Allocate memory for jerry pointer and for pointer to dimension according to length of dimension name */
   ALLOCATE(jerry_ptr, Jerry, 1);
   ALLOCATE(jerry_ptr->id, char, strlen(id) + 1);
   /* Memory allocated successfully -> initialize Jerry values */
   memcpy(jerry_ptr->id, id, strlen(id) + 1);
   jerry_ptr->origin = init_origin(dim_name, planet);
   if (jerry_ptr->origin == NULL){
      free(jerry_ptr->id);
      free(jerry_ptr);
      return NULL;
   }
   jerry_ptr->happiness = happiness;
   jerry_ptr->number_of_properties = 0;
   jerry_ptr->property_array = NULL;
   return jerry_ptr;
}


/* Print jerry function assuming pointer is initialized */
status print_jerry( Jerry* jerry )
{
   status stat = failure;
   if( NULL != jerry ){
      printf("Jerry , ID - %s : \nHappiness level : %d \n", jerry->id, jerry->happiness);
      stat = print_origin(jerry->origin);
      if ( stat != success )
         return stat;
      
      /* Only print physical Characetristics if there are any under jerry*/
      if( jerry->number_of_properties > 0 ){
         printf("Jerry's physical Characteristics available : \n\t");
         
         /* Iterate on the number of physical Characteristics in array, print each one */
         for(int i=0; i < jerry->number_of_properties; i++ ){
            if (i > 0)
               printf(", ");
            printf("%s : %.2f ", jerry->property_array[i]->name, jerry->property_array[i]->value);
         }
         printf("\n");
      return stat;
      }
   }
   return stat;
}

int getHappiness(Jerry* jerry)
{
   return jerry->happiness;
}

/* Set Jerry's Happiness to new value, must be between 0 and 100, exceeding values are brought back to limit */
status setHappiness(Jerry* jerry, int newHappiness)
{
   if (newHappiness >= 0 && newHappiness <= 100){
      jerry->happiness = newHappiness;
   }
   else if (newHappiness < 0 ){
      jerry->happiness = 0;
   }
   else{
      jerry->happiness = 100;
   }
   return success;
}

/* Delete jerry function assuming pointer is initialized, free up memory allocated to fields in jerry including freeing up origin allocation */
status delete_jerry( Jerry* jerry )
{
   if( NULL != jerry ){
      /* Free up memory allocation for jerry id, origin, physical characteristics and jerry pointer */
      free(jerry->id);
      delete_origin(jerry->origin);

      /* free each property pointer and struct in property array before freeing array itself */
      /* but first - verify array wasn't allocated to NULL in a memory error */
      if (jerry->property_array != NULL){ 
         for (int i=0; i < jerry->number_of_properties; i++)
            delete_property( jerry->property_array[i] );
         free(jerry->property_array);
      }
      free(jerry);
      return success;
   }
   return BadArgs;
}

/* Add property to jerry in the end of the property array */
status add_property( Jerry* jerry, char *property_name, float property_value )
{
   if( NULL != jerry && NULL != property_name ){
      /* Check that jerry doesn't already have this property, otherwise return BadArgs*/
      bool test = property_in_jerry( jerry, property_name );
      if ( test == true )
         return BadArgs;
                  
      /* Incrase property_array memory size to accomedate new property pointer */
      /* if no property_array was NULL as initialized, realloc behaves like malloc */
      jerry->property_array = realloc( jerry->property_array, (jerry->number_of_properties + 1) * sizeof(PhysicalCharacteristic*) );
      
      /* Check to see if realloc was succesful */
      if ( jerry->property_array == NULL )
         return BadMemoryAllocation;

      /* if memory was reallocated succesfully, init and append new property to the end of the array and increase number of properties in jerry*/
      PhysicalCharacteristic* property = init_property(property_name, property_value);
      if (property == NULL)
         return BadMemoryAllocation;
      jerry->property_array[jerry->number_of_properties] = property;
      jerry->number_of_properties++;
      return success;
   }
   return failure;
}

/* Check if property in jerry */
bool property_in_jerry( Jerry* jerry, char *property_name )
{
   if( NULL != jerry ){
      /* Iterate over physical characteristics in property array and compare names with property_name provided */
      for (int i=0; i < jerry->number_of_properties; i++)
      {
         if ( strcmp(jerry->property_array[i]->name, property_name) == 0 )
            return true;
      }
   }
   /* Empty jerry means property isn't in jerry by default */
   return false;
}

status remove_property( Jerry* jerry, char *property_name )
{
   if( NULL != jerry ){
      /* Check that jerry has this property to remove */
      bool test = property_in_jerry( jerry, property_name );
      if ( test == false)
         return failure;
      
      /* iterate on property array to find element we want to remove */
      for (int i=0; i < jerry->number_of_properties; i++)
      {
         if ( strcmp(jerry->property_array[i]->name, property_name) == 0 ){
            
            /* when property to delete is found delete property struct and shift left remaining property_array before reallocing memory */
            delete_property( jerry->property_array[i] );
            for (int j=i; j < (jerry->number_of_properties - 1); j++)
               jerry->property_array[j] = jerry->property_array[j+1];
            jerry->property_array = realloc( jerry->property_array, (jerry->number_of_properties - 1) * sizeof(PhysicalCharacteristic*) );
            jerry->number_of_properties--;      
            
            /* Check to see if realloc was succesful - property is correctly NULL if number of properties is 0*/
            if ( jerry->property_array == NULL && jerry->number_of_properties > 0)
               return BadMemoryAllocation;
            
            return success;
         }
      }
   }
   /* Can't remove property from empty jerry */
   return failure;
}