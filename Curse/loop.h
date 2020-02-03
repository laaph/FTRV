//
//  loop.h
//  Curse
//
//  Created by stanza on 11/19/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#ifndef Curse_loop_h
#define Curse_loop_h

struct character_info random_character(void);
struct ship_info setup_ship(void);
void main_loop(void);
void pause_menu(void);
void launch(void);
void unimplemented(int x, int y);
void dock(void);
void refuel(void);
void upgrade_ship(void);


#endif
