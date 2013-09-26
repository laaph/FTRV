//
//  utils
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <stdlib.h>
#include <ncurses.h>

char * randomname()
{
    int num_names = 3;
    
    switch (arc4random_uniform(num_names))
    {
        case 0:
            return "Maximillian";
            break;
        case 1:
            return "Leila";
        default:
            return "Chuck";
            break;
    }
}
void clearscreen()
{
    int num = 80*24;
    move(0, 0);
    while(num--)
        addch(' ');
}