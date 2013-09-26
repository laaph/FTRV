//
//  playerdata.h
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#ifndef Curse_playerdata_h
#define Curse_playerdata_h

enum room_info
{
    PILOT, SENSORS, BEAM, LASER, MISSILE, TELEPORT, MEDBAY, EMPTY
};

struct character_info
{
    int health;
    char name[14];
    int color;
    int locationX;
    int locationY;
};

struct ship_info
{
    enum room_info rooms[8];  // Largest ship should be 8 rooms
    int roomLocationX[8];
    int roomLocationY[8];
    int health;
    char name[52];
};

       int            num_chars;
struct character_info characters[8]; // Max characters
struct ship_info      player_ship;
       int            money;

extern int spaceshipsizey;
extern int spaceshipsizex;

extern char spaceship_pic[13][30]; /* =
{
    "----------------\\            ",
    " \\               \\           ",
    "  \\               \\          ",
    "   \\---------------\\------\\  ",
    "   |                |   |  \\ ",
    "   |                |   |   \\",
    "    ----------------+---+---|",
    "   |                |   |   /",
    "   |                |   |  / ",
    "   /---------------/------/  ",
    "  /               /          ",
    " /               /           ",
    "----------------/            "
}; */


#endif
