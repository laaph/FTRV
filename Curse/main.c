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

// We should probably move all non-main stuff out of this file.
struct character_info random_character();
static void finish(int a);
void new_game();
struct ship_info setup_ship();
struct planet_info setup_earth();
void main_loop();
void pause_menu();
void launch();
void unimplemented();
void dock();


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
    galaxy_setup();
    
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
                launch();
                break;
            case '2':
                // Dock
                dock();
                break;
            case '3':
                // Trouble
                unimplemented(34, 4);
                break;
            case '4':
                // Details
                unimplemented(34, 4);
                break;
            case 'x':
            case 'X':
            case 27: // Escape character - what, no macro?
                pause_menu();
                break;
        }
    }
}
void dock()
{
    while(true)
    {
        draw_dock_menu(34, 4);
        refresh();

        int input = getch();
        switch(input)
        {
            case 'x':
            case 'X':
            case 27:  // Escape, go back to game
                return;
                break;
            case '1':
                unimplemented(36, 6);
                break;
            case '2':
                unimplemented(36, 6);
                break;
            case '3':
                unimplemented(36, 6);
                break;
            case '4':
                unimplemented(36, 6);
                break;
            case '5':
                unimplemented(36, 6);
                break;
        }
    }
    
}

void unimplemented(int x, int y)
{
    draw_unimplemented(x, y);
    refresh();
    getch();
    return;
}

void launch()
{
    // This will be hard eventually, as we have to make a map that I haven't done
    // yet, and figure out how to encode the information.  However, for now, I'll
    // just list ALL the planets, and you can decide which one to jump to.
    
    if(player_ship.fuel == 0)
    {
        draw_no_fuel(32, 4);
        return;
    }
    
    draw_launch_menu(32, 4);
    refresh();
 
    while(true)
    {
        int input = getch();
        if(input == 27 || input == 'X' || input == 'x')
        {
            return;
        }
        if(input > '0' || input < '2')
        {
            int new_system =input - '0';
            if(new_system != current_system)
                player_ship.fuel--;
            current_system = new_system;
            return;
        }
    }

}

void pause_menu() // I'll rename this later, I'm sure
{
    draw_pause_menu(34, 4);
    refresh();

    while(true)
    {
        int input; // c89 purists fuck you
        input = getch();
        switch(input)
        {
            case 'x':
            case 'X':
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
                unimplemented(36, 6);
                break;
            case 'n':
            case 'N':
                unimplemented(36, 6);
                break;
            case 'l':
            case 'L': // Load game
                unimplemented(36, 6);
                break;
        }
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
    s.fuel = 20;
    
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

