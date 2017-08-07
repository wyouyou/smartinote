/**
 This Node contail a general English word contaning explanation explanation.
 
 */

#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(string d,string c ,Node* n, time_t t): data(d), explanation(c),next(n), timeAdded(t)
{
}

Node::Node(string d,string c ,Node* n) : data(d), explanation(c),next(n)
{
    add_timeAdded();
}


string Node::get_data() const
{
    return data;
}

string Node::get_explanation() const
{
    return explanation;
}

Node* Node::get_next() const
{
    return next;
}

time_t Node::get_timeAdded() const
{
    return timeAdded;
}

void Node::set_next(Node *ptr)
{
    next = ptr;
}
void Node::add_explanation(string explanation)
{
    explanation = explanation + ", " + explanation;
}

void Node::add_timeAdded()
{
    time_t now_time;
    now_time = time(NULL);
    timeAdded = now_time;    
}

ostream& operator<< (ostream& out, const Node& obj)
{
    out << obj.get_data() << "|" << "   " << obj.get_explanation() << "|"  << "    " << obj.get_timeAdded() << "|" << endl << endl;
    return out;
}


