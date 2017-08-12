

#ifndef List_h
#define List_h

#include "Node.h"
#include <iostream>

class List
{
    Node* top;
    
public:
    List();
    ~List();
    /**
     ******************************************************************
     Adding a new node to the list.
     */
    void push(string item ,string c, time_t t );
    void add_value(string value, Node* target);
    string pop();
    Node* get_top() const;
    bool remove(string item);
    Node* find(string item) const;
    bool remove_Last();
};

std::ostream& operator << (std::ostream&, const List&);

#endif /* List_h */
