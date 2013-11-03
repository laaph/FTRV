
//
//  drawing.c
//  Curse
//
//  Created by stanza on 9/26/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <ncurses.h>

#include "playerdata.h"
#include "utils.h"
#include "wchar.h"
#include "galaxy_data.h"

// Putting this here because it has to go somewhere and it's pictures! Yeah.
int spaceshipsizey = 13;
int spaceshipsizex = 30;

char  spaceship_pic[13][30] =
{
    "--------------\\           ",
    " \\            \\           ",
    "  \\            \\          ",
    "   \\------------\\------\\  ",
    "   |      |      |   |  \\ ",
    "   |      |      |   |   \\",
    "    ------+------+---+---|",
    "   |      |      |   |   /",
    "   |      |      |   |  / ",
    "   /------------/------/  ",
    "  /            /          ",
    " /            /           ",
    "-------------/            "
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
        move(1, 0);
        addstr("Laaph Productions and Rogue Nation Rogue-like Players Present...");
        move(3, 0);
        addstr("                  ESCAPE FROM ROGUELIKE VELOCITY                ");
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
        move(1, 0);
        addstr("Laaph Productions and Rogue Nation Rogue-like Players Present...");
        move(3, 0);
        addstr("                  ESCAPE FROM ROGUELIKE VELOCITY                ");
        drawspaceship(4, 1);
        move(j, endX);
        addch('@');
        refresh();
        delay_output(100);
    }
    move(22, 0);
    addstr("An adventure to discover that ncurses does not support UTF8");
    move(23, 0);
    addstr("Press [N] for a new game, or [C] to continue a game.");

}

void drawflame(int y, int x, int flamesize)
{
    char * flames = "-----";
    int min = 0;
    int wid = flamesize;
    attrset(COLOR_PAIR(3));
    if(x < 2)
    {
        min = 5 - x;
        x = 2;
    }
    if((77 - x) < flamesize)
    {
        wid = 77 - x;
    }
        
    for(int i = 0; i < 5; i++)
    {
        move(i + y + 4, x - 2);
        addnstr(&flames[min], wid);
    }
    attrset(COLOR_PAIR(7));
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

void drawstats()
{
    char t[80];

    int left = 0;
    for(int i = 0; i < num_chars; i++)
    {
        move(i, left);
        attrset(COLOR_PAIR(characters[i].color));
        addch(i + '1');
        addstr(" @ ");
        attrset(COLOR_PAIR(7));
        addstr(characters[i].name);
        sprintf(t, "%i", characters[i].health);
        move(i, left + 16);
        addstr(t);
    }
    sprintf(t, "|Ship Hull:    %i", player_ship.health);
    move(0, left + 20);
    addstr(t);
    sprintf(t, "|Ship Shields: %i", player_ship.shield);
    move(1, left + 20);
    addstr(t);
    sprintf(t, "|Money:          %i", money);
    move(0, left + 38);
    addstr(t);
    sprintf(t, "|Current System: %s", starname(current_system));
    move(1, left + 38);
    addstr(t);
}

void draw_main_menu(int x, int y)
{
    move(y + 0, x);
    addstr(" ---------------------------------- ");
    move(y + 1, x);
    addstr("| 1 Launch to other system         |");
    move(y + 2, x);
    addstr("| 2 Dock with planet               |");
    move(y + 3, x);
    addstr("| 3 Look for trouble               |");
    move(y + 4, x);
    addstr("| 4 See details of ship and crew   |");
    move(y + 5, x);
    addstr(" ---------------------------------- ");
}
void draw_pause_menu(int x, int y)
{
    move(y + 0, x);
    addstr(" ---------------------------------- ");
    move(y + 1, x);
    addstr("| Q Quit                           |");
    move(y + 2, x);
    addstr("| N New game                       |");
    move(y + 3, x);
    addstr("| S Save game                      |");
    move(y + 4, x);
    addstr("| L Load game                      |");
    move(y + 5, x);
    addstr("| X Return to game                 |");
    move(y + 6, x);
    addstr(" ---------------------------------- ");
}

void draw_unimplemented(int x, int y)
{
    move(y + 0, x);
    addstr(" ---------------------------------- ");
    move(y + 1, x);
    addstr("| This has not yet been            |");
    move(y + 2, x);
    addstr("| implemented.                     |");
    move(y + 3, x);
    addstr("|                                  |");
    move(y + 4, x);
    addstr("| Terribly sorry.   :(             |");
    move(y + 5, x);
    addstr(" ---------------------------------- ");
    
}
void draw_launch_menu(int x, int y)
{
    int a = 1;
    int b;
    char line[35];
    move(y + 0, x);
    addstr(" ---------------------------------- ");
    for(b = 0; b < num_of_stars; b++)
    {
        if(b != current_system)
        {
            move(y + a, x);
            addstr("|                                  |");
            move(y + a, x);
            snprintf(line, 35, "| %i %s", b, starname(b));
            addstr(line);
            a++;
        }
    }
    move(y + a, x);
    addstr(" ---------------------------------- ");
}
void zoom_spaceship()
{
    int flamesize;
    clearscreen();
    for(int i = 1; i < 80; i++)
    {
        delay_output(20);
        clearscreen();
        drawspaceship(4, i);
        flamesize = 5; if (i < flamesize) { flamesize = i; }
        drawflame(4, i - 1, flamesize);
        move(24,78);
        addch(' ');
        refresh();
    }
}