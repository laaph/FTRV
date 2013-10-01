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
#include <unistd.h>

#include "utils.h"
#include "drawing.h"
#include "playerdata.h"

struct character_info random_character();
static void finish(int a);
void new_game();
struct ship_info setup_ship();

int main(int argc, char * argv[])
{

    int opt; int skiptonew;
    
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
    
    while ((opt = getopt(argc, argv, "n")) != -1)
    {
        switch (opt)
        {
            case 'n':
                skiptonew = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-n]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    if(skiptonew)
    {
        new_game();
    }
    
    introscreen();
    
    while(1)
    {
        int c = getch();
        if(c == 'n' || c == 'N')
        {
            zoom_spaceship();
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

void new_game()
{

    num_chars = 2;
    money = 1000;
    player_ship = setup_ship();
    
    characters[0] = random_character();
    characters[1] = random_character();
    characters[1].locationY = 7;

    clearscreen();
    drawspaceship (4, 2);
    drawcharacters(4, 2);
    drawroomnumbers(4, 2);
    drawstats();
    refresh();
    
    getch();
    endwin();
    exit(0);
}
struct ship_info setup_ship()
{
    struct ship_info s;
    s.health = 100;
    s.shield = 100;
    strcpy(s.name, "One Bad Rat");
    // Why do I hard code it all out like this?
    s.roomLocationX[0] = 25;
    s.roomLocationY[0] = 4;
    s.roomLocationX[1] = 25;
    s.roomLocationY[1] = 7;
    s.roomLocationX[2] = 21;
    s.roomLocationY[2] = 4;
    s.roomLocationX[3] = 21;
    s.roomLocationY[3] = 7;
    s.roomLocationX[4] = 17;
    s.roomLocationY[4] = 4;
    s.roomLocationX[5] = 17;
    s.roomLocationY[5] = 7;
    s.roomLocationX[6] = 11;
    s.roomLocationY[6] = 4;
    s.roomLocationX[7] = 11;
    s.roomLocationY[7] = 7;
    s.rooms[0] = PILOT;
    s.rooms[1] = SENSORS;
    s.rooms[2] = LASER;
    s.rooms[3] = EMPTY;
    s.rooms[4] = EMPTY;
    s.rooms[5] = EMPTY;
    s.rooms[6] = EMPTY;
    s.rooms[7] = EMPTY;
    
    return s;
}
struct character_info random_character()
{
    struct character_info number_one;
    number_one.health    = 100;
    number_one.color     = arc4random_uniform(8);
    number_one.locationX = 25;
    number_one.locationY = 5;
    strcpy(number_one.name, randomname());
    
    return number_one;
}

