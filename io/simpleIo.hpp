//
//  simpleIo.hpp
//  dic
//
//  Created by Jaye Wang on 8/21/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef simpleIo_hpp
#define simpleIo_hpp

#include <stdio.h>
#include <iostream>

namespace simpleIO{
    
    class Integer{
    public:
        /*
         * Function: randomIntegerBetween
         * Usage: int n = randomIntegerBetween(min, max);
         *
         * return a number between min and max, Inclusive.
         */

        static int randomIntegerBetween(const int& min, const int& max);
        
    };
    
    class String{
        
    public:
        static void appendSpace(std::string& prompt);

        /**
         * Display fatal message with info specified by the arg: commandInfo.
         *
         * Usage simpleIo::String::dispalyFatalMessage(arg);
         */
        static void dispalyFatalMessage(const std::string& commandInfo);
        
        /*
         * Function: getLine
         * Usage: string line = simpleIo::String::getLine(prompt);
         * -------------------------------------
         * Reads a line of text from cin and returns that line
         * as a string.  The newline character that terminates the input is
         * not stored as part of the return value.
         */
        static std::string getLine(const std::string& prompt);
        
        /*
         * Alternate version of getLine that accepts a prompt and fills a given output
         * variable with its result.
         */
        static void getLine(const std::string& prompt,
                               std::string& out);
        
        

        
    };
    
}

#endif /* simpleIo_hpp */
