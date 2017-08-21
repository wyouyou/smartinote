//
//  String.cpp
//  dic
//
//  Created by Jaye Wang on 8/20/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "String.hpp"


void appendSpace(std::string& prompt) {
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
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
std::string getLine(const std::string& prompt) {
    std::string line;
    getLine(prompt, line);
    return line;
}

void getLine(const std::string& prompt,
             std::string& out) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    std::cout << promptCopy;
    getline(std::cin, out);
}

void getLine(std::istream& input,
             std::string& out) {
    getline(input, out);
}
