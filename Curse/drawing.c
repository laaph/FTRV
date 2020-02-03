
//
//  drawing.c
//  Curse
//
//  Created by stanza on 9/26/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <ncurses.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "drawing.h"
#include "playerdata.h"
#include "utils.h"
#include "wchar.h"
#include "galaxy_data.h"

// Putting this here because it has to go somewhere and it's pictures! Yeah.
int spaceshipsizey = 13;
int spaceshipsizex = 30;

char  spaceship_pic[13][30] =
{
    "-------------\\           ",
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

char room_info_strings[11][12] =
{
    "EMPTY", "BRIDGE", "SENSORS", "BEAM", "LASER", "MISSILE", "TELEPORT", "MEDBAY", "FUELBAY",  "STORAGE", "BARRACKS"
};

static void finish(int a)
{
    endwin();
    exit(0);
}

void drawing_setup()
{
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
        addstr("                  FASTER THAN ROGUELIKE VELOCITY                ");
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
        addstr("                  FASTER THAN ROGUELIKE VELOCITY                ");
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
 /*   for(int i = 0; i < num_chars; i++)
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
    }*/
    sprintf(t, "Ship Fuel:       %2i", player_ship.fuel);
    move(0, left);
    addstr(t);
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

void draw_ship_info(int x, int y)
{
    // Not going to use draw_generic for this
    // Oh yes we are go look at other examples
    
    int linelength = 9;
    int linecount  = 12;
    char lines[linecount][linelength];
    char *  linesPtr = lines[0];

    strcpy("", &lines[0][0]);
    for(int i = 0; i < 8; i++)
    {
        snprintf(&lines[i+1][0], linelength, "%i %s", i + 1, room_info_strings[i]);
    }
    strcpy("", &lines[9][0]);

    draw_generic(x, y, 15, linecount, &linesPtr);
}
void draw_upgrade_menu(int x, int y)
{
    char *s[] = {
        "1 Buy new component",
        "2 Sell component",
        "3 Upgrade component",
        "X Return To Orbit"
    };
    draw_generic(x, y, 28, 4, s);
}


void draw_generic(int x, int y, int width, int argc, char * argv[])
{
    int i; // For the purpose of having an index when we are done in the loop
    char topbottom[width];
    char line[width];
    for(i = 1; i < width - 2; i++)
    {
        topbottom[i] = '-';
    }
    topbottom[0] = ' '; topbottom[i] = ' '; topbottom[i+1] = ' ';
    move(y, x);
    addnstr(topbottom, width);
    for(i = 0; i < argc; i++)
    {
        int length = width - 4 - (int)strlen(argv[i]);
        snprintf(line, width, "| %s %*s", argv[i], length, "|");
        move(y + 1 + i, x);
        addnstr(line, width);
    }
    move(y + 1 + i, x);
    addnstr(topbottom, width);
}
void draw_dock_menu(int x, int y)
{
    char *s[] = {
        "1 Refuel",
        "2 Buy/Sell Ship Upgrades",
        "3 Buy/Sell Goods",
        "4 Hire/Dismiss Crew",
        "5 Browse Mission Computer",
        "X Return To Orbit"
    };
    draw_generic(x, y, 38, 6, s);
}
void draw_no_fuel(int x, int y)
{
    char *s[] = {
        "You are unable to go ot another system",
        "due to no fuel.  Refuel and try again."
    };
    draw_generic(x, y, 38, 2, s);
}
void draw_main_menu(int x, int y)
{
    char *s[] = {
        "1 Launch to other system",
        "2 Dock with planet",
        "3 Look for trouble",
        "4 See details of ship and crew",
        "X System Menu"
    };
    draw_generic(x, y, 38, 5, s);
}
void draw_pause_menu(int x, int y)
{
    char *s[] = {
        "Q Quit",
        "N New game",
        "S Save game",
        "L Load game",
        "X Return to game"
    };
    draw_generic(x, y, 38, 5, s);
}
void draw_gas_station_all_full(int x, int y)
{
    char *s[] = {
        "Your ship has a full tank of fuel."
    };
    draw_generic(x, y, 38, 1, s);
}
void draw_map(int select) // Could add x, y but I suspect it will be hardcoded in any case
{
    char *s[] = {
        "", "", "", "", "",
        "", "", "", "", "",
        "", "", "", "", "",
        "", "", "", "", ""
    };
    draw_generic(2, 2, 76, 16, s);
    for(int i = 0; i < NUM_OF_STARS; i++)
    {
        move(planets[i].locationY + 3, planets[i].locationX + 3);

        attrset(COLOR_PAIR(planets[i].color));
        if(i == select)
        {
            // set inverse
            attrset(A_REVERSE);
            
        }
        addch('A' + i); // Good for 26 planets
        // Er except X implies escape, so um...
        // We could do many other things too...
        // Ideally we'd do 1, 2, ... for planets we
        // can jump to and * for others
        // otherwise fuel and time go up with distance

        attrset(COLOR_PAIR(7));
        attrset(A_NORMAL);
        refresh();
    }
    refresh();
}
void draw_unimplemented(int x, int y)
{
    char *s[] = {
        "This has not yet been",
        "implemented.",
        "",
        "Terribly sorry.    :( ",
    };
    draw_generic(x, y, 38, 4, s);
}
int draw_launch_menu(int x, int y, int s)
{
#define LL 76  // line_length  // Bad bad bad how can I fix this?
    char line1[LL] = "TAB: choose planet  ENTER: jump, X: cancel";
    char line2[LL] = "";
    char line3[LL];
    int xdelta = abs(planets[s].locationX - planets[current_system].locationX);
    int ydelta = abs(planets[s].locationY - planets[current_system].locationY);
    double distance = sqrt((xdelta*xdelta)+(ydelta*ydelta));
    int fuel_use = (int)distance;

    snprintf(line3, sizeof(line3), "Current target: %s (%i, %i), Distance:%i, Fuel cost:%i", starname(s),
             planets[s].locationX, planets[s].locationY, (int)(distance * 314000) , fuel_use);
    
    char *ss[3] =
    {
        line1, line2, line3
    };
    
    draw_generic(x, y, LL, 3, ss);
    return fuel_use;
}
void draw_not_enough_fuel(int x, int y)
{
    char *s[] = {
        "You don't have enough fuel to get there.",
    };
    draw_generic(x, y, 45, 1, s);
}
void draw_gas_station(int x, int y, int current_fuel, int max_fuel, int cost_per_fuel)
{
    char line1[53];
    char line2[53];
    char line3[53];
    char line4[53];
    char line5[53];
    snprintf(line1, sizeof(line1), "You have %i fuel.  You most can carry is %i.", current_fuel, max_fuel);
    snprintf(line2, sizeof(line2), "The fuel here costs $%i per unit.", cost_per_fuel);
    if(max_fuel - current_fuel > 9)
    {
        snprintf(line3, sizeof(line3), "Press F to fill the tank, 0 to buy 10 units");
    } else {
        snprintf(line3, sizeof(line3), "Press F to fill the tank,");
    }
    snprintf(line4, sizeof(line4), "or 1-9 to buy 1 to 9 units of fuel");
    snprintf(line5, sizeof(line5), "Press X to leave the fueling station");
    char *ss[5] =
    {
        line1, line2, line3, line4, line5
    };
    draw_generic(x, y, 53, 5, ss);
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
