//
//  playerdata.h
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <wchar.h>

#ifndef Curse_playerdata_h
#define Curse_playerdata_h

enum room_info
{
    EMPTY, PILOT, SENSORS, BEAM, LASER, MISSILE, TELEPORT, MEDBAY, FUELBAY, STORAGE
};

struct character_info
{
    int  health;
    char name[14];
    int  color;
    int  locationX;
    int  locationY;
};

struct ship_info
{
    enum room_info rooms[8];  // Largest ship should be 8 rooms
    int roomLocationX[8];
    int roomLocationY[8];
    int health;
    int shield;
    int fuel;
    char name[52];
};

       int            num_chars;
struct character_info characters[8]; // Max characters
struct ship_info      player_ship;
       int            money;
       int            current_system;


extern int spaceshipsizey;
extern int spaceshipsizex;

extern char spaceship_pic[13][30]; 
extern char room_info_strings[11][12];  // May require more than 12 chars at some point
#endif
