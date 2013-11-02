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
#include "galaxy_data.h"

struct character_info random_character();
static void finish(int a);
void new_game();
struct ship_info setup_ship();
struct planet_info setup_earth();
void main_loop();
void pause_menu();

int main(int argc, char * argv[])
{

    int opt; int skiptonew;
    
    while ((opt = getopt(argc, argv, "nl")) != -1)
    {
        switch (opt)
        {
            case 'n':
                skiptonew = 1;
                break;
            case 'l':
                skiptonew = 0;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-n]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
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

    noecho();
    
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
    current_system = 0;
    
    characters[0] = random_character();
    characters[1] = random_character();
    characters[1].locationY = 8;

    planets[0] = setup_earth();
    
    main_loop();
    
    endwin();
    exit(0);
}

void main_loop()
{
    int input;
    while(true)
    {
        clearscreen();
        drawspaceship (4, 2);
        drawcharacters(4, 2);
        drawroomnumbers(4, 2);
        draw_main_menu(30, 2);
        drawstats();
        refresh();
        
        input = getch();
        switch(input)
        {
            case '1':
                //Launch
                break;
            case '2':
                // Dock
                break;
            case '3':
                // Trouble
                break;
            case '4':
                // Details
                break;
            case 27: // Escape character - what, no macro?
                pause_menu();
                break;
        }
    }
}

void pause_menu() // I'll rename this later, I'm sure
{
    draw_pause_menu(32, 4);
    refresh();

    int input; // c89 purists fuck you
    input = getch();
    switch(input)
    {
        case 'r':
        case 'R':
        case 27:  // Escape, go back to game
            return;
            break;
        case 'Q':
        case 'q':
            endwin();
            exit(0);
            exit(0);
            break;
        case 's':
        case 'S':
            // Save
            break;
        case 'n':
        case 'N':
            // New game
            break;
        case 'l':
        case 'L': // Load game
            break;
    }

}


struct ship_info setup_ship()
{
    struct ship_info s;
    s.health = 100;
    s.shield = 100;
    strcpy(s.name, "One Bad Rat");
    // Why do I hard code it all out like this?
    s.roomLocationX[0] = 22;
    s.roomLocationY[0] = 4;
    s.roomLocationX[1] = 22;
    s.roomLocationY[1] = 7;
    s.roomLocationX[2] = 18;
    s.roomLocationY[2] = 4;
    s.roomLocationX[3] = 18;
    s.roomLocationY[3] = 7;
    s.roomLocationX[4] = 11;
    s.roomLocationY[4] = 4;
    s.roomLocationX[5] = 11;
    s.roomLocationY[5] = 7;
    s.roomLocationX[6] = 4;
    s.roomLocationY[6] = 4;
    s.roomLocationX[7] = 4;
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

struct planet_info setup_earth()
{
    struct planet_info p;
    strcpy(p.name, "Sol System");
    p.color = COLOR_GREEN;
    p.locationX = 0;
    p.locationY = 0;
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

struct character_info random_character()
{
    struct character_info number_one;
    number_one.health    = 100;
    number_one.color     = arc4random_uniform(8);
    number_one.locationX = 22;
    number_one.locationY = 5;
    strcpy(number_one.name, randomname());
    
    return number_one;
}

