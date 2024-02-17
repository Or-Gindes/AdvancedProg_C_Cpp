#ifndef JERRY_H_
#define JERRY_H_
#include "Defs.h"

/* definition of a data structure for holding a Planets information - */
/* Array implementation because number of planets is known in advance */
typedef struct Planet_t
{
    char *name;
    float x,y,z;
}Planet;

/* initialize planet with pointer to name of planet as well x,y,z locations in space */
Planet* init_planet( char *name, float x, float y, float z );
status print_planet( Planet* planet );
Planet* search_planet( Planet** planet_array, char *name, int number_of_planets );
void delete_planet( Planet* planet );

/* definition of a data structure for holding a Jerrys Origin information */
/* Origin functions {init, print, delete} are static and only called by Jerry */
typedef struct Origin_t
{
    char *dimension;
    Planet *planet;
}Origin;

/* definition of a data structure for holding a Jerrys information - initiator and destractor functions are static and hidden from user */
typedef struct PhysicalCharacteristic_t
{
    char *name;
    float value;
}PhysicalCharacteristic;

/* definition of a data structure for holding a Jerrys information */
/* Array implementation because number of Jerries is known in advance */
typedef struct Jerry_t
{
    char *id;
    int happiness;
    Origin *origin;
    PhysicalCharacteristic **property_array;
    int number_of_properties;
}Jerry;

Jerry* init_jerry( char *id, int happiness, Planet* planet, char *dim_name );
status print_jerry( Jerry* jerry );
int getHappiness(Jerry* jerry);
status setHappiness(Jerry* jerry, int newHappiness);
status delete_jerry( Jerry* jerry );
status add_property( Jerry* jerry, char *property_name, float property_value );
bool property_in_jerry( Jerry* jerry, char *property_name );
status remove_property( Jerry* jerry, char *property_name );

#endif /* JERRY_H_ */