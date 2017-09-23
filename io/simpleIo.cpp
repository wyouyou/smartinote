//
//  all.cpp
//  dic
//
//  Created by Jaye Wang on 8/21/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "simpleIo.hpp"

using namespace all;
using namespace Color;


/**
 * return true if the enter key get pressed.
 */

bool all::stdIO::isEnterKeyPressed(const std::string& str)
{
    if (str.empty())
        return true;
    else
        return false;
}


std::string stdIO::getSpaces(const int& num)
{
    
    
    std::string spaces = "";
    for (int i = 0 ; i < num ; i++)
        spaces += " ";
    
    return spaces;
}

void stdIO::justifyText(std::string& line, const int& theWidth)
{
    
    // 09/11/17 It turned out the effect does not looks buautiful, stop
    //    using at at the moment
    return;
    
    std::vector<std::string> tokens = simpleIO::getTokens(line);
    
    short diff = theWidth - line.size() ;
    
    // justify the diff width
    for (int i = 0 ; i < diff && diff < theWidth && i < tokens.size(); i++)
    {
        tokens.at(i) += " ";
    }
    
    // modify the line.
    line = "";
    
    for (int i = 0 ; i < tokens.size(); i++)
        line += tokens.at(i) + " ";
    
}

/*
 * return false if any char of the arg is not numeric
 * return false if the arg is empty
 * return true if all chars of the arg is numeric
 
 * Precondition: the string should be a single token with no space.
 * If any string with token passed in, its copy will be trimed inside the function.
 */

bool simpleIO::isNumeric(const std::string& arg)
{
    std::string argCopy = arg;
    const int asciiMin = 48;
    const int asciiMax = 57;
    bool isNum = true;
    
    if (argCopy == "")
        return false;
    
    
    
    for (int i = 0 ; i< argCopy.size(); i++)
    {
        int ascii = argCopy[i];
        if (ascii >= asciiMin && ascii <= asciiMax)
            isNum = true;
        else
            return false;
    }
    
    return isNum;
}
/*
 *
 */
std::string simpleIO::getToken(const std::string& line, const std::string& delimiter )
{
    std::string token;
    std::vector<std::string> tokens = getTokens(line, delimiter);
    
    token = tokens.size() >= 1 ? tokens.at(0) : "";
    return token;
}


std::vector<std::string> simpleIO::getTokens(const std::string& arg, const std::string& delimiter )
{
    //    string info = "  2455    65    33  r ";
    std::string argCopy, temp;
    std::vector<std::string> tokens(0);
    argCopy = simpleIO::trim(arg);
    
    
    // handle some input whose first char is delimeter
    // delete the first char and continue
    if (argCopy.find_first_of(delimiter) == 0)
        argCopy = simpleIO::trim(argCopy.substr(1));
    
    // handle some input whose last char is delimeter
    // delete the last char and continue
    if (argCopy.find_last_of(delimiter) == argCopy.size()- 1)
        argCopy = simpleIO::trim(argCopy.substr(0, argCopy.size()-1));
    
    size_t posStart = 0;
    size_t posEnd  = argCopy.size() -1;
    
    
    // getting tokens if posStart and there is still content at argCopy
    while (posStart < posEnd && argCopy.size() > 0)
    {
        posStart = argCopy.find_first_not_of(delimiter);
        posEnd = argCopy.find_first_of(delimiter);
        
        // if both posStart and posEnd is valid, take the token,
        // push it to tokens and shrink argCopy
        if (posStart < argCopy.size() -1 && posEnd < argCopy.size() -1)
        {
            temp =  argCopy.substr(posStart, posEnd - posStart);
            argCopy = simpleIO::trim(argCopy.substr(posEnd+1));
            tokens.push_back(temp);
        }
        
        // The else part gracefully handle both the first token if the argCopy has only one char, also handle the last token if the argCopy has more than one token.
        else // the last tokens, OR the very first token IF the argCopy == somesth like : "1"
        {
            tokens.push_back(argCopy);
            break;
        }
        
    }
    
    return tokens;
    
}

std::string simpleIO::trim(const std::string& arg)
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
        //        std::cout << "Empty string exception.";
    }
    return argCopy;
}


void all::stdIO::printAline(const short& length)
{
    for (int i = 0; i< length; i++)
        std::cout << "-";
    std::cout << "\n";
    
}



void UnixIO::smartinotePrompt()
{
    // A nice prompt for geek ~
    
    all::UnixIO::printInColor("\n➜ ", Color::FG_GREEN);
    all::UnixIO::printInColor("S", Color::FG_RED);
    all::UnixIO::printInColor("m", Color::FG_YELLOW);
    all::UnixIO::printInColor("a", Color::FG_LIGHT_Cyan);
    all::UnixIO::printInColor("r", Color::FG_PINK);
    all::UnixIO::printInColor("t", Color::FG_GREEN);
    all::UnixIO::printInColor("i", Color::FG_LIGHT_Cyan);
    all::UnixIO::printInColor("n", Color::FG_PINK);
    all::UnixIO::printInColor("o", Color::FG_GREEN);
    all::UnixIO::printInColor("t", Color::FG_RED);
    all::UnixIO::printInColor("e", Color::FG_YELLOW);
    
    
}


void UnixIO::displayMessage(const std::string& message)
{
    std::cout << "   ";
    all::UnixIO::printInColor("➠  ", Color::FG_RED);
    std::cout << message;
}


void UnixIO::printInWidth(const int& intialDiff,
                          const int& theWidth,
                          std::vector<std::string> tokens)
{
    // handle all chinese character, chinese chars are all wide bytes, the probaly one line of sentece can only be tokenized by 1 token if the line has all the chinese character.
    std::string strCopy = "";
    for (int i =0 ; i < tokens.size(); i++)
        strCopy = tokens.at(i) + " ";
    
    int width = intialDiff;
    std::string token;
    std::string line = "";
    bool theFirstLine = true;
    for (int i = 0; i < tokens.size() ; i++)
    {
        token = tokens.at(i) + " "; // token to be print
        width += token.size();
        
        if (width <= theWidth)
            line += token;
        else // else the line content width greater than theWidth
        {
            i--; // give chance to the current token to be played around.
            if (line.size() > 0 && line.size() < theWidth )
                stdIO::justifyText(line, theWidth);
            // handle all chinese character.
            // 宽字符的中文，在这里需要手动break
            // othwise infinite loop
            else
            {
                std::cout << strCopy;
                break;
                
            }
            
            // The first line with front symbol
            if (theFirstLine)
                std::cout << line << "\n";
            // other lines
            else
                std::cout << stdIO::getSpaces(intialDiff)
                << line << "\n";
            
            width = intialDiff;
            line = "";
            theFirstLine = false;
        }
    }
    
    // print the last line which is definitly < theWidth
    if (line != "" && theFirstLine == true)
        std::cout << line ;
    else if (line != "" && theFirstLine == false)
        std::cout << stdIO::getSpaces(intialDiff)
        << line ;
    else return;
    
    
}


/*
 *
 * Issue: width adjustment does not support chinese characters.
 *
 */
void UnixIO::printInColor(const std::string& str,
                          const int& theWidth, Color::Code pCode,
                          const std::string& optStr)
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
    
    std::vector<std::string> tokens = simpleIO::getTokens(strCopy);
    
    
    UnixIO::printInWidth(0, theWidth, tokens);
    
    
    std::cout << defFG ;
}



void UnixIO::printInColor(const int& intilWidth,
                          const std::string& str,
                          const int& width,
                          Color::Code pCode,
                          const std::string& optStr)
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
    
    std::vector<std::string> tokens = simpleIO::getTokens(strCopy);
    
    
    
    
    UnixIO::printInWidth(intilWidth, width, tokens);
    std::cout << defFG ;
    
}


void UnixIO::printInColor(const std::string& str, Color::Code pCode)
{
    Color::Modifier color(pCode);
    Color::Modifier defFG(Color::FG_DEFAULT);
    std::cout << color << str << defFG;
}



/*****************************************************************/

void simpleIO::dispalyFatalMessage(const std::string& commandInfo)
{
    std::cout << "    ";
    all::UnixIO::printInColor("➠  fatal ", Color::FG_RED);
    std::cout << commandInfo  << " is not found" << std::endl;
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
std::string simpleIO::getLine(const std::string& prompt,Color::Code pCode) {
    std::string line;
    getLine(prompt, line, pCode);
    return line;
}


void simpleIO::getLine(const std::string& prompt,
                       std::string& out,Color::Code pCode )
{
    std::string promptCopy = prompt;
    simpleIO::appendSpace(promptCopy);
    
    
    UnixIO::printInColor(prompt, pCode);
    getline(std::cin, out);
    
    
}


void simpleIO::appendSpace(std::string& prompt)
{
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}





