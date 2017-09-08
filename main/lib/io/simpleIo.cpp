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




void stdIO::justifyText(std::string& line, const int& theWidth)
{
    std::vector<std::string> tokens = String::getTokens(line);
    
    short diff = theWidth - line.size();
    
    // justify the diff width
    for (int i = 0 ; i < diff && diff < theWidth && i < tokens.size(); i++)
    {
        tokens.at(i) += " ";
    }
    
    // modify the line.
    line = "";
    
    for (int i = 0 ; i < tokens.size(); i++)
        line += " " + tokens.at(i);
    
}

/*
 * return true if all chars of the arg is numeric
 * return false if any char of the arg is not numeric
 * return false if the arg is empty
 
 * Precondition: the string should be a single token with no space.
 * If any string with token passed in, its copy will be trimed inside the function.
 */

bool String::isNumeric(const std::string& arg)
{
    std::string argCopy = arg;
    
    
    
    return true;
}
/*
 *
 */
std::string String::getToken(const std::string& line, const std::string& delimiter )
{
    std::string token;
    std::vector<std::string> tokens = getTokens(line, delimiter);
    
    token = tokens.size() >= 1 ? tokens.at(0) : "";
    return token;
}


std::vector<std::string> String::getTokens(const std::string& arg, const std::string& delimiter )
{
    //    string info = "  2455    65    33  r ";
    
    std::string argCopy, temp;
    std::vector<std::string> tokens(0);
    argCopy = simpleIO::String::trim(arg);
    size_t posStart = 0;
    size_t posEnd  = argCopy.size()-1;
    
    // getting tokens if posStart and ther is still content at argCopy
    while (posStart < posEnd && argCopy.size() > 0)
    {
        posStart = argCopy.find_first_not_of(' ');
        posEnd = argCopy.find_first_of(' ');
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
    simpleIO::UnixIO::printInColor("S", Color::FG_RED);
    simpleIO::UnixIO::printInColor("m", Color::FG_YELLOW);
    simpleIO::UnixIO::printInColor("a", Color::FG_LIGHT_Cyan);
    simpleIO::UnixIO::printInColor("r", Color::FG_PINK);
    simpleIO::UnixIO::printInColor("t", Color::FG_GREEN);
    simpleIO::UnixIO::printInColor("i", Color::FG_LIGHT_Cyan);
    simpleIO::UnixIO::printInColor("n", Color::FG_PINK);
    simpleIO::UnixIO::printInColor("o", Color::FG_GREEN);
    simpleIO::UnixIO::printInColor("t", Color::FG_RED);
    simpleIO::UnixIO::printInColor("e", Color::FG_YELLOW);

    
}


void UnixIO::displayMessage(const std::string& message)
{
    simpleIO::UnixIO::printInColor("\n➜ ", Color::FG_GREEN);
    std::cout << message;
}


void UnixIO::printInColor(const std::string& str,const int& theWidth, Color::Code pCode,const std::string& optStr)
{
    std::string strCopy;
    
    if (optStr!= "")
        strCopy = str + optStr;
    else
        strCopy = str;
    
    // define color Modifier
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);
    std::cout << color;
    
    std::vector<std::string> tokens = String::getTokens(strCopy);
    
    
    int width = 0;
    std::string token;
    std::string line = "";
    for (int i = 0; i < tokens.size() ; i++)
    {
        token = tokens.at(i) + " ";
        
//        if (token.size() < theWidth)
            width += token.size();
        
        if (width <= theWidth)
            line += token;
        else
        {
            if (line.size() > 0 )
                stdIO::justifyText(line, theWidth);
            // handle all chinese character.
            else std::cout << strCopy;
            
            std::cout << "   "
            << std::left <<  std::setw(theWidth)
            << line << "\n";
            
            width = 0;
            line = "";
        }
    }
    
    // print the last line which is definitly < theWidth
    if (line != "")
        std::cout << "    " << std::left <<  std::setw(theWidth) <<line;
    
    std::cout << defFG << "\n";
}


void UnixIO::printInColor(const std::string& str, Color::Code pCode)
{
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);
    std::cout << color << str << defFG;
}



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






