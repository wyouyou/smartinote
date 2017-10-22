//
//  QueueADT.hpp
//  smartinote
//
//  Created by Jaye Wang on 10/18/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef QueueADT_hpp
#define QueueADT_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    // Structure for the queue nodes
    struct QueueNode
    {
        T value;          // Value in the node
        QueueNode *next;  // Pointer to next node
    };
    
    QueueNode *front;    // Pointer to the queue front
    QueueNode *rear;     // Pointer to the queue rear
    int count;
    
public:
    //Constructor
    Queue(){front = rear = NULL; count = 0;}
    
    // Destructor
    ~Queue();
    
    // Queue operations
    bool enqueue(T);
    bool dequeue(T &);
    bool isEmpty();
    int  getCount();
    bool queueFront(T &);
    bool queueRear(T &);
};


#endif /* QueueADT_hpp */

