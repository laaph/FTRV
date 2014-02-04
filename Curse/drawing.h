//
//  drawing.h
//  Curse
//
//  Created by stanza on 9/26/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#ifndef Curse_drawing_h
#define Curse_drawing_h

void drawspaceship(int y, int x);
void drawcharacters(int y, int x);
void drawflame(int y, int x, int flamesize);
void introscreen();
void set_colors();
void clearscreen();
void drawroomnumbers(int y, int x);
void drawstats();
void zoom_spaceship();
void draw_main_menu(int x, int y);
void draw_pause_menu(int x, int y);
int  draw_launch_menu(int x, int y, int s);
void draw_unimplemented(int x, int y);
void draw_dock_menu(int x, int y);
void draw_no_fuel(int x, int y);
void draw_not_enough_fuel(int x, int y);
void draw_map(int select);
void draw_gas_station(int x, int y, int current_fuel, int max_fuel, int cost_per_fuel);
void draw_gas_station_all_full(int x, int y);
void drawing_setup();
void draw_ship_info(int x, int y);
void draw_generic(int x, int y, int width, int argc, char * argv[]);
void draw_upgrade_menu(int x, int y);

#endif
