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
    
    switch (arc4random_uniform(num_names))
    {
        case 0:
            return "Maximillian";
            break;
        case 1:
            return "Leila";
        case 2:
            return "Sebastian";
        default:
            return "Chuck";
            break;
    }
}
char * starname(int system_number)
{
    return "Riga";
}