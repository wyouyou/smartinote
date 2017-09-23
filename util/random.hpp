//
//  random.hpp
//  smartinote
//
//  Created by Jaye Wang on 9/22/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

#include <stdio.h>
#include <cstdlib>



class random{
    
public:
/*
 * Function: randomIntegerBetween
 * Usage: int n = randomIntegerBetween(min, max);
 *
 * return a number between min and max, Inclusive.
 */
static int randomIntegerBetween(const int& min, const int& max);
};
#endif /* random_hpp */
