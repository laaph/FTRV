//
//  main.c
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

#include "playerdata.h"
#include "utils.h"

struct character_info random_character();
static void finish(int a);
void introscreen();
void drawspaceship(int y, int x);
void set_colors();
void drawflame(int y, int x, int flamesize);
void new_game();
void drawcharacters(int y, int x);

int main(int argc, const char * argv[])
{

    // insert code here...
    
    signal(SIGINT, finish);
    WINDOW * w = initscr();
    if(getmaxx(w) < 80 || getmaxy(w) < 24)
    {
        endwin();
        printf("This game requires a terminal of at least 24x80 to run.\n");
        exit(0);
    }

    if(has_colors())
    {
        start_color();
        set_colors();
    }
    
    introscreen();
    
    finish(1);
    return 0;
}

static void finish(int a)
{
    endwin();
    exit(0);
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
    while(1)
    {
        int c = getch();
        if(c == 'n' || c == 'N')
        {
            new_game();
        }
        if(c == 'q' || c == 'Q')
        {
            endwin();
            exit(0);
        }
    }
}

void drawflame(int y, int x, int flamesize)
{
    // Warning!  This function will not check to verify you'll still be on the screen.  Be careful!
}

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

void update_stats()
{
    int left = 0;
    for(int i = 0; i < num_chars; i++)
    {
        move(i, left);
        attrset(COLOR_PAIR(characters[i].color));
        addch('@');
        attrset(COLOR_PAIR(7));
        addch(' ');
        addstr(characters[i].name);
        char t[4];
        sprintf(t, "%i", characters[i].health);
        move(i, left + 14);
        addstr(t);
    }
        
}

void new_game()
{
    clearscreen();
    for(int i = 1; i < 80; i++)
    {
        delay_output(20);
        clearscreen();
        drawspaceship(4, i);
        move(24,78);
        addch(' ');
        refresh();
    }

    
    num_chars = 2;
    
    characters[0] = random_character();
    characters[1] = random_character();
    characters[1].locationY = 7;

    clearscreen();
    drawspaceship (4, 18);
    drawcharacters(4, 18);
    update_stats();
    refresh();
    
    getch();
    endwin();
    exit(0);
}
struct ship_info setup_ship()
{
    struct ship_info s;
    s.health = 100;
    strcpy(s.name, "One Bad Rat");
    s.roomLocationX[0] = 28;
    s.roomLocationY[0] = 4;
    s.rooms[0] = EMPTY;
    // Finish the rest of the spaceshipinfo
    
    return s;
}
struct character_info random_character()
{
    struct character_info number_one;
    number_one.health    = 100;
    number_one.color     = arc4random_uniform(8);
    number_one.locationX = 25;
    number_one.locationY = 4;
    strcpy(number_one.name, randomname());
    
    return number_one;
}

