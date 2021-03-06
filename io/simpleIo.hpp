//
//  all.hpp
//  dic
//
//  Created by Jaye Wang on 8/21/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef simpleIo_hpp
#define simpleIo_hpp

/* Test for pull request */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>

namespace CONST{
    
    const int PRINT_WIDTH = 75;
    
    const int NUM_NODES_TO_REVIEW = 10;
    
    const std::string DATABASE_LOCATION = "/Users/zhouwang/Github/smartinote-data/dic.md";
    
    const char HTML_OUT_LOCATION [] = "/Users/zhouwang/Github/smartinote-data/dic.html";
    
    const std::string DATABASE_COPY_LOCATION = "/Users/zhouwang/Github/smartinote-data/dicCopy.md";
    
    const bool SIPPORT_COLOR = true;
}


/*
 * Refer:https://stackoverflow.com/a/2616912/8023309
 */
namespace Color {
    enum Code {
        //        Foreground (text)
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_DEFAULT  = 39,
        FG_LIGHT_Cyan = 96,
        FG_PINK = 91,
        FG_ORANGE = 1,
        FG_YELLOW = 33,
        FG_LIGHTYELLO = 2,
        FG_PURPLE = 94,
        
        
        
        //        Background
        BG_LIGHT_GREEN = 102,
        BG_LIGHT_BLUE = 104,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };


    
    class Modifier {
        Code code;
    public:
        Modifier(){};
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}



class simpleIO{
    
public:
    /**
     * return true if the str passed in is numeric
     * return false otherwise
     */
    static bool isNumeric(const std::string&);
    
    
    /**
     * return a vector of tokens tokenized,delimited by
     * the second argument, default is whitespace.
     *
     */
    static std::vector<std::string> getTokens(const std::string& arg, const std::string& delimiter = " ");
    
    /**
     * return the first token of the argment string delimited by
     * the second argument, default is whitespace.
     */
    
    static std::string getToken(const std::string& line, const std::string& delimiter = " ");
    
    /**
     * return a copy of arg but with leading and trailing whitespace removed.
     */
    static std::string trim(const std::string& arg);
    
    static void appendSpace(std::string& prompt);
    
    /**
     * Function: getLine
     * Usage: string line = simpleIo::String::getLine(prompt);
     * -------------------------------------
     * Reads a line of text from cin and returns that line
     * as a string.  The newline character that terminates the input is
     * not stored as part of the return value.
     */
    static std::string getLine(const std::string& prompt, Color::Code = Color::BG_DEFAULT);
    
    
    /**
     * Alternate version of getLine that accepts a prompt and fills a given output
     * variable with its result.
     */
    static void getLine(const std::string& prompt,
                        std::string& out,Color::Code = Color::BG_DEFAULT);
    
    
    /**
     * Display fatal message with info specified by the arg: commandInfo.
     *
     * Usage simpleIo::String::dispalyFatalMessage(arg);
     */
    static void dispalyFatalMessage(const std::string& commandInfo);
    
};




//class stdIO



namespace all{
    class UnixIO
    {
    public:
        
        
        /**
         * Print str in the color specified by the client.
         * Optional optStr is used to add extra info to console
         * Issue: Only support ASCII coding. 
         *
         */
        static void printInColor(const std::string& str,
                                 const int& width,
                                 Color::Code pCode = Color::BG_DEFAULT,
                                 const std::string& optStr = "");
        /**
         * Another version of printInColor
         * Handle the case : where the prompt symbol destroy the 
         * alignment.
         * all::UnixIO::printInColor("   ◉ ", Color::FG_LIGHT_Cyan);
         * all::UnixIO::printInColor(tokens.at(i), width, pCode);
         */
        static void printInColor(const int& intilWidth,
                                 const std::string& str,
                                 const int& width,
                                 Color::Code pCode = Color::BG_DEFAULT,
                                 const std::string& optStr = "");

        
        /**
         * Print exactly what the arg str is with specified color.
         */
        static void printInColor(const std::string& str,
                                 Color::Code pCode );
        
        static void printInWidth(const int& intialDiff,
                          const int& theWidth,
                          std::vector<std::string> tokens);
        
//        static void printInColor(const std::string& str, Color::Code pCode);

        static void smartinotePrompt();
        static void displayMessage(const std::string& message);
        
    };
    
    class stdIO
    {
    public:
        
        static bool isEnterKeyPressed(const std::string& str);
        static void printAline(const short& length);
        /**
         * Modify the string with the width specific.
         * Justfiy the text width in order to format console
         */
        static void justifyText(std::string& str, const int& theWidth);
        static std::string getSpaces(const int& num);

    };
        
}

#endif /* simpleIo_hpp */
