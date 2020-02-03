//
//  loop.c
//  Curse
//
//  Created by stanza on 11/19/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

// The following includes were blindly copied from main.c.  If I were a little
// more devoted, I would go through them and try and figure out what was needed
// or not.



#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"
#include "drawing.h"
#include "playerdata.h"
#include "galaxy_data.h"
#include "loop.h"

void main_loop()
{
    int input;
    while(1)
    {
        clearscreen();
        drawspaceship (4, 2);
        drawcharacters(4, 2);
        drawroomnumbers(4, 2);
        draw_main_menu(30, 2);
        drawstats();
        refresh_screen();
        
        input = get_single_char_input();
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
    while(1)
    {
        draw_dock_menu(34, 4);
        refresh_screen();
        
        int input = get_single_char_input();
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
                upgrade_ship();
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
    
    while(1)
    {
        clearscreen();
        drawspaceship (4, 2);
        drawcharacters(4, 2);
        drawroomnumbers(4, 2);
        drawstats();
        
        if(player_ship.fuel >= max_fuel)
        {
            draw_gas_station_all_full(10,10);
            refresh_screen();
            get_single_char_input();
            return;
        }
        draw_gas_station(10, 10, player_ship.fuel, max_fuel, cost_of_fuel);
        refresh_screen();
        
        input = get_single_char_input();
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
    refresh_screen();
    get_single_char_input();
    return;
}

void launch(void)
{
    // This will be hard eventually, as we have to make a map that I haven't done
    // yet, and figure out how to encode the information.  However, for now, I'll
    // just list ALL the planets, and you can decide which one to jump to.
    
    if(player_ship.fuel == 0)
    {
        draw_map(current_system);
        draw_no_fuel(10, 10);
        get_single_char_input();
        return;
    }
    
    int fuel_usage;
    int select = current_system;
    int input;
    while(1)
    {
        draw_map(select);
        fuel_usage = draw_launch_menu(2, 19, select);
        refresh_screen();
        
        input = get_single_char_input();
        
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
        if(input == '\n' || input == FTRV_ENTER || input == '\r')// '\n works on my machine but the others are
            // here in case it works on others
        {
            if(player_ship.fuel >= fuel_usage)
            {
                player_ship.fuel = player_ship.fuel - fuel_usage;
                current_system = select;
                return;
            } else {
                draw_not_enough_fuel(15, 10);
                get_single_char_input();
            }
            
        }
    }
    
}

void pause_menu() // I'll rename this later, I'm sure
{
    draw_pause_menu(34, 4);
    refresh_screen();
    
    while(1)
    {
        int input; // c89 purists fuck you
        input = get_single_char_input();
        switch(input)
        {
            case 'x':
            case 'X':
            case 27:  // Escape, go back to game
                return;
                break;
            case 'Q':
            case 'q':
                tear_down();
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

void upgrade_ship()
{
    clearscreen();
    draw_ship_info(2, 2);
    draw_upgrade_menu(42, 2);
    // Do upgrade switch
    
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
