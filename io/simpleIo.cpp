//
//  simpleIo.cpp
//  dic
//
//  Created by Jaye Wang on 8/21/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "simpleIo.hpp"
using namespace simpleIO;
using namespace Color;



std::string String::trim(const std::string& arg)
{
    
    std::string argCopy = arg;
    size_t posStart = arg.find_first_not_of(' ');
    size_t posEnd = arg.find_last_not_of(' ');
    argCopy = arg.substr(posStart, posEnd-posStart+1);
    return argCopy;
}


void simpleIO::stdIO::printAline(const short& length)
{
    for (int i = 0; i< length; i++)
        std::cout << "-";
    std::cout << "\n";

}

void UnixIO::printInColor(const std::string& value,const int& width, Color::Code pCode)
{
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);

    std::cout << color;
    
    for (int i = 0; i<value.size(); i++)
    {
        if (i != 0 && i % width == 0) std::cout << "\n";
        std::cout << value[i];
    }
    
    std::cout << defFG << "\n";
}


void UnixIO::printInColor(const std::string& str, Color::Code pCode)
{
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);
    std::cout << color << str << defFG;
}




/*----------------------------------------------------------------*/


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
std::string String::getLine(const std::string& prompt,Color::Code pCode) {
    std::string line;
    getLine(prompt, line, pCode);
    return line;
}


void String::getLine(const std::string& prompt,
             std::string& out,Color::Code pCode )
{
    std::string promptCopy = prompt;
    String::appendSpace(promptCopy);
    
    
    UnixIO::printInColor(prompt, pCode);
//    std::cout << promptCopy;
    getline(std::cin, out);
}


void String::appendSpace(std::string& prompt)
{
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}






