
//
//  drawing.c
//  Curse
//
//  Created by stanza on 9/26/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <ncurses.h>

#include "playerdata.h"

// Putting this here because it has to go somewhere and it's pictures! Yeah.
int spaceshipsizey = 13;
int spaceshipsizex = 30;

char spaceship_pic[13][30] =
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
};

void drawspaceship(int y, int x)
{
    int min = 0;
    int wid = spaceshipsizex;
    if(x < 0)
    {
        min = -x;
        x = 0;
    }
    if((80 - x) < spaceshipsizex)
    {
        wid = 80 - x;
    }
    
    for(int i = 0; i < spaceshipsizey; i++)
    {
        move(i + y, x);
        addnstr(&spaceship_pic[i][min], wid);
    }
}

void drawcharacters(int y, int x)
{
    for(int i = 0; i < num_chars; i++)
    {
        int xx = x + characters[i].locationX;
        int yy = y + characters[i].locationY;
        
        if(xx < 0 || yy < 0 || xx > 79 || yy > 23)
        {
            //  printf("nothing drawn.\n");
        }
        else
        {
            move(yy, xx);
            attrset(COLOR_PAIR(characters[i].color));
            addch('@');
            attrset(COLOR_PAIR(7));
        }
    }
}
void drawroomnumbers(int y, int x)
{
    for(int i = 0; i < 8; i++)
    {
        int xx = x + player_ship.roomLocationX[i];
        int yy = y + player_ship.roomLocationY[i];
        
        if(xx < 0 || yy < 0 || xx > 79 || yy > 23)
        {
            //  printf("nothing drawn.\n");
        }
        else
        {
            move(yy, xx);
            addch(i + '1');
        }
    }
}

void introscreen()
{
    int endX = 25;
    int endY = 10;
    for(int i = 0; i < endX; i++)
    {
        move(2, 0);
        addstr("                                                              ");
        move(3, 0);
        addstr("Laaph Productions and Rogue Nation Rogue-like Players Present...");
        drawspaceship(4, 1);
        move(2, i);
        addch('@');
        refresh();
        delay_output(100);
    }
    for(int j = 2; j < endY; j++)
    {
        move(2, 0);
        addstr("                                                              ");
        move(3, 0);
        addstr("Laaph Productions and Rogue Nation Rogue-like Players Present...");
        drawspaceship(4, 1);
        move(j, endX);
        addch('@');
        refresh();
        delay_output(100);
    }
    move(22, 0);
    addstr("The flight of one bad mouse");
    move(23, 0);
    addstr("Press [N] for a new game, or [C] to continue a game.");

}

void drawflame(int y, int x, int flamesize)
{
    // Warning!  This function will not check to verify you'll still be on the screen.  Be careful!
}

void set_colors()
{
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
}
void clearscreen()
{
    int num = 80*24;
    move(0, 0);
    while(num--)
        addch(' ');
}
