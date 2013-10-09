//
//  galaxy_data.h
//  Curse
//
//  Created by stanza on 10/8/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#ifndef Curse_galaxy_data_h
#define Curse_galaxy_data_h

enum planet_services
{
    REPAIR, GOODS, FUEL, MISSIONS, HIREABLES
};

struct planet_info
{
    int  ID;  // uppercase to not conflict with Obj-C's id
    char name[28];
    int  color;
    int  locationX;
    int  locationY;
    planet_services services[10]; // Can't have them all?
};


#endif
