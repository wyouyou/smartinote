//
//  random.cpp
//  smartinote
//
//  Created by Jaye Wang on 9/22/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "random.hpp"

/**
 * This is how rand() works:
 * v1 = rand() % 100;         // v1 in the range 0 to 99
 * v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
 */
int random::randomIntegerBetween(const int &min, const int &max)
{
    return rand()% (max - min + 1) + min;
}
