//
//  String.hpp
//  dic
//
//  Created by Jaye Wang on 8/20/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <string>
#include <iostream>


const std::string DATA_LOCATION = "/Applications/selfmade-product/dic-master/data/dic.md";


/*
 * Function: appendSpace
 * ---------------------
 * Adds a space at the end of the given string by reference if none is present.
 */
void appendSpace(std::string& prompt);

/*
 * Alternate version of getLine that accepts a prompt and fills a given output
 * variable with its result.
 */
void getLine(const std::string& prompt,
             std::string& out);

/*
 * Alternate version of getLine that accepts an input stream to read from.
 * Meant as a drop-in replacement for the standard C++ getline (lowercase L)
 * function.
 */
void getLine(std::istream& input,
             std::string& out);


#endif /* String_hpp */
