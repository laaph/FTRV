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

#include "utils.h"
#include "drawing.h"
#include "playerdata.h"

struct character_info random_character();
static void finish(int a);
void new_game();
void update_stats();
struct ship_info setup_ship();


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
    
    finish(1);
    return 0;
}

static void finish(int a)
{
    endwin();
    exit(0);
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

