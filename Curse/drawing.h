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
void draw_launch_menu(int x, int y);
void draw_unimplemented(int x, int y);
void draw_dock_menu(int x, int y);
void draw_no_fuel(int x, int y);


#endif
