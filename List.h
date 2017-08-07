

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
    void push(string item ,string c, time_t t = 1501467877);
    void add_explanation(string explanation, Node* target);
    string pop();
    Node* get_top() const;
    bool remove(string item);
    Node* find(string item) const;
    bool remove_Last();
};

std::ostream& operator << (std::ostream&, const List&);

#endif /* List_h */
