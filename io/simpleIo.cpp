//
//  simpleIo.cpp
//  dic
//
//  Created by Jaye Wang on 8/21/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "simpleIo.hpp"
using namespace simpleIO;

/**
 * This is how rand() works:
 * v1 = rand() % 100;         // v1 in the range 0 to 99
 * v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
 */
int simpleIO::Integer::randomIntegerBetween(const int &min, const int &max)
{
    return rand()% (max - min + 1) + min;
}


/*****************************************************************/

void String::dispalyFatalMessage(const std::string& commandInfo)
{
    std::cout << "fatal: " << commandInfo << " is not found.\n";
}

/*
 * Implementation notes: getLine
 * -----------------------------
 * The getLine function simply combines the process of displaying a
 * prompt and reading an input line into a single call.  The primary
 * reason for including this function in the library is to ensure
 * that the process of reading integers, floating-point numbers, and
 * strings remains as consistent as possible.
 */
std::string String::getLine(const std::string& prompt) {
    std::string line;
    getLine(prompt, line);
    return line;
}


void String::getLine(const std::string& prompt,
             std::string& out) {
    std::string promptCopy = prompt;
    String::appendSpace(promptCopy);
    std::cout << promptCopy;
    getline(std::cin, out);
}


void String::appendSpace(std::string& prompt)
{
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}






