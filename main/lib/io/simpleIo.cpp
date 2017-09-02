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


/*
 *
 */
std::string String::getToken(const std::string& line, const std::string& delimiter )
{
    std::string token;
    std::vector<std::string> tokens = getTokens(line, delimiter);
    
    token = tokens.size() >= 1 ? tokens.at(1) : "";
    return token;
}


std::vector<std::string> String::getTokens(const std::string& arg, const std::string& delimiter )
{
    std::string argCopy, temp;
    std::vector<std::string> tokens(0);
    argCopy = simpleIO::String::trim(arg);
    size_t posStart = 0;
    size_t posEnd  = argCopy.size()-1;
    
    // getting tokens if posStart and there is still content at argCopy
    while (posStart < posEnd && argCopy.size() > 0)
    {
        posStart = argCopy.find_first_not_of(delimiter);
        posEnd = argCopy.find_first_of(delimiter);
        if (posStart < argCopy.size() && posEnd < argCopy.size())
        {
            temp =  argCopy.substr(posStart, posEnd - posStart);
            argCopy = simpleIO::String::trim(argCopy.substr(posEnd));
            tokens.push_back(temp);
        }
        else // the last tokens
        {
            tokens.push_back(argCopy);
            break;
        }
    }
    return tokens;
    
}


std::string String::trim(const std::string& arg)
{
    /*
     @ 08/31  Added exception handling when only the Enter key get passed / empty string:
     libc++abi.dylib: terminating with uncaught exception of type std::out_of_range: basic_string
     [1]    10832 abort      ./dic
     
     */
    
    std::string argCopy = arg;
    try
    {
        if (argCopy.size() == 0)
            throw argCopy;
        size_t posStart = arg.find_first_not_of(' ');
        size_t posEnd = arg.find_last_not_of(' ');
        argCopy = arg.substr(posStart, posEnd-posStart+1);

    }
//    catch(std::string str)  // catch specific message.
    catch(...) // catch general error messages
    {
        std::cout << "Empty string exception.";
    }
    return argCopy;
}


void simpleIO::stdIO::printAline(const short& length)
{
    for (int i = 0; i< length; i++)
        std::cout << "-";
    std::cout << "\n";

}



void UnixIO::geeklePrompt()
{
    // A nice prompt for geek ~
    
    simpleIO::UnixIO::printInColor("\n➜ ", Color::FG_GREEN);
    simpleIO::UnixIO::printInColor("G", Color::FG_RED);
    simpleIO::UnixIO::printInColor("e", Color::FG_YELLOW);
    simpleIO::UnixIO::printInColor("e", Color::FG_GREEN);
    simpleIO::UnixIO::printInColor("k", Color::FG_LIGHT_Cyan);
    simpleIO::UnixIO::printInColor("l", Color::FG_PINK);
    simpleIO::UnixIO::printInColor("e", Color::FG_GREEN);

}




void UnixIO::displayMessage(const std::string& message)
{
    simpleIO::UnixIO::printInColor("\n➜ ", Color::FG_GREEN);
    std::cout << message;
}


void UnixIO::printInColor(const std::string& str,const int& width, Color::Code pCode,const std::string& optStr)
{
    std::string strCopy = str + optStr;
    
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);

    std::cout << color;
    
    for (int i = 0; i<strCopy.size(); i++)
    {
        if (i != 0 && i % width == 0) std::cout << "\n";
        std::cout << strCopy[i];
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
    getline(std::cin, out);


}


void String::appendSpace(std::string& prompt)
{
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}






