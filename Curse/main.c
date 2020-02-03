//
//  main.c
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

// The following includes may not be needed after moving all the code to loop.c.
// Were I really with it I would go through and delete the includes not needed, but
// I will save that task for when I am procrastinating.

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
#include "loop.h"

void new_game(void); // Even this might need to go in to loop.c

static void finish(int a)
{
    endwin();
    exit(0);
}

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
    
    drawing_setup();
    
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
    
    //finish(1);
    return 0;
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

