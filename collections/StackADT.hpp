//
//  StackADT.hpp
//  smartinote
//
//  Created by Jaye Wang on 10/18/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef StackADT_hpp
#define StackADT_hpp

#include <stdio.h>

#endif /* StackADT_hpp */

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Stack
{
private:
    // Structure for the stach nodes
    struct StackNode
    {
        T value;          // Value in the node
        StackNode *next;  // Pointer to next node
    };
    
    StackNode *top;     // Pointer to the stack top
    int count;
    
public:
    //Constructor
    Stack(){top = NULL; count = 0;}
    
    // Destructor
    ~Stack();
    
    // Stack operations
    bool push(T);
    bool pop(T &);
    bool isEmpty();
    // getCount()
    // getTop()
};
