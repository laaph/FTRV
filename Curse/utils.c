//
//  utils
//  Curse
//
//  Created by stanza on 9/24/13.
//  Copyright (c) 2013 Laaph. All rights reserved.
//

#include <stdlib.h>

char * randomname()
{
    int num_names = 4;
    
    char *names[4] =
    {
        "Maximillian",
        "Leila",
        "Sebastian",
        "Chuck"
    };
    
    return names[arc4random_uniform(num_names)];
    
}
char * starname(int system_number)
{
    char *names[3] =
    {
        "Riga",
        "Aldebaran",
        "Arcturus"
    };
    return names[system_number];
}