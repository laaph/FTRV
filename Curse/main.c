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
void main_loop();
void pause_menu();
void launch();
void unimplemented();
void dock();
void refuel();

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

    for(int i = 0; i < NUM_OF_STARS; i++)
    {
        planets[i] = setup_planet(i);
    }
    
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
                refuel();
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
void refuel()
{
    int input;
    int cost_of_fuel = 2;
    int max_fuel = 20;
    
    while(true)
    {
        clearscreen();
        drawspaceship (4, 2);
        drawcharacters(4, 2);
        drawroomnumbers(4, 2);
        drawstats();

        if(player_ship.fuel >= max_fuel)
        {
            draw_gas_station_all_full(10,10);
            refresh();
            getch();
            return;
        }
        draw_gas_station(10, 10, player_ship.fuel, max_fuel, cost_of_fuel);
        refresh();
        
        input = getch();
        if(input == 27 || input == 'x' || input == 'X')
        {
            return;
        }
        if(input == '0' && (max_fuel - player_ship.fuel > 10) && (money > 10 * cost_of_fuel))
        {
            money = money - (10 * cost_of_fuel);
            player_ship.fuel = player_ship.fuel + 10;
        }
        if(input >= '1' && input <= '9')
        {
            // We can do this later
        }
        if((input == 'F' || input == 'f') && ( money >= 10 * cost_of_fuel * (max_fuel - player_ship.fuel)))
        {
            money = money - cost_of_fuel * (max_fuel - player_ship.fuel);
            player_ship.fuel = 20;
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
        draw_map(current_system);
        draw_no_fuel(10, 10);
        getch();
        return;
    }
    
    int fuel_usage;
    int select = current_system;
    int input;
    while(true)
    {
        draw_map(select);
        fuel_usage = draw_launch_menu(2, 19, select);
        refresh();

        input = getch();
        
        if(input == 27 || input == 'X' || input == 'x')
        {
            return;
        }
        if(input >= 'A' && input < 'A' + NUM_OF_STARS)
        {
            select = input - 'A';
        }
        if(input >= 'a' && input < 'a' + NUM_OF_STARS)
        {
            select = input - 'a';
        }
        if(input == '\t')
        {
            select++;
            if(select == NUM_OF_STARS)
                select = 0;
        }
        if(input == '\n' || input == KEY_ENTER || input == '\r')// '\n works on my machine but the others are
                                                                // here in case it works on others
        {
            if(player_ship.fuel >= fuel_usage)
            {
                player_ship.fuel = player_ship.fuel - fuel_usage;
                current_system = select;
                return;
            } else {
                draw_not_enough_fuel(15, 10);
                getch();
            }
            
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

struct character_info random_character()
{
    struct character_info number_one;
    number_one.health    = 100;
    number_one.color     = 
    number_one.locationX = 22;
    number_one.locationY = 5;
    strcpy(number_one.name, randomname());
    
    return number_one;
}

