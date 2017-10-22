//
//  StackADT.cpp
//  smartinote
//
//  Created by Jaye Wang on 10/18/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "StackADT.hpp"

/**~*~*
 Destructor
 *~**/
template <class T>
Stack<T>::~Stack()
{
    StackNode * Curr, prev;
    
    // Curr start at the top of the stack
    Curr = top;
    
    // Traverse the list deleting each node
    while (Curr)
    {
        prev = Curr->prev;
        delete Curr;
        Curr = prev;
    }
}

/**~*~*
 Member function push pushes the argument onto
 the stack.
 *~**/
template <class T>
bool Stack<T>::push(T item)
{
    StackNode* newN = new StackNode;
    newN->value = item;
    
    if (!newN)
        return false;
    
    // update 2 links, and update the counter
    newN->prev = top;
    top = newN;
    count++;
    
    return true;
}

/**~*~*
 Member function pop pops the value at the top
 of the stack off, and copies it into the variable
 passed as an argument.
 *~**/
template <class T>
bool Stack<T>::pop(T &item)
{
    
    // empty stack case
    if (isEmpty())
        return false;
    
    item = top->value;

    StackNode *deletePtr = top;
    top = top->prev;
    delete deletePtr;
    count--;
    
    return true;
    
}

/**~*~*
 Member function isEmpty returns true if the stack
 is empty, or false otherwise.
 *~**/
template <class T>
bool Stack<T>::isEmpty()
{
    return count == 0;
}
