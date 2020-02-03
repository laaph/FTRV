//
//  galaxy_data.c
//  Curse
//
//  Created by stanza on 11/2/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <string.h>
#include <stdlib.h>

#include "galaxy_data.h"

void galaxy_setup()
{
    //num_of_stars = NUM_OF_STARS;
}

char * starname(int system_number)
{
    char *names[NUM_OF_STARS] =
    {
        "Arcturus",
        "Betelgeuse",
        "Cor Caroli",
        "Draconis",
        "Eudamus",
        "Riga"
    };
    return names[system_number];
}

struct planet_info setup_planet(int planet_num)
{
    struct planet_info p;
    strcpy(p.name, starname(planet_num));
    p.color = arc4random_uniform(6) + 1;
    p.locationX = arc4random_uniform(66) + 4;
    p.locationY = arc4random_uniform(12) + 4;
    // Services REALLY REALLY needs to turn in to a bit field.
    p.services[0] = REPAIR;
    p.services[1] = GOODS;
    p.services[2] = FUEL;
    p.services[3] = MISSIONS;
    p.services[4] = HIREABLES;
    p.connections[0] = 1;   // Not that planets 1 and 2 exist yet
    p.connections[1] = 2;
    return p;
}
