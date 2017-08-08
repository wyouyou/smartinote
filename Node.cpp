/**
 This Node contail a general English word contaning value value.
 
 */

#include "Node.h"
#include <iostream>

using namespace std;

int Node::numOfNodes = 0;

Node::Node(string d,string c ,Node* n, time_t t): key(d), value(c),next(n), timeAdded(t)
{
    index = ++numOfNodes;
    
    familiar_index = 0;
    tm* timeInfo  = localtime(&timeAdded);
    date.year2digits = timeInfo->tm_year % 100;
    date.year4digits = 2000 + date.year2digits;
    date.month = timeInfo->tm_mon + 1;
    date.day_of_month = timeInfo->tm_mday;
    date.day_of_week = timeInfo->tm_wday;
    date.day_in_the_year = timeInfo->tm_yday;
    date.hour = timeInfo->tm_hour;
    date.minutes = timeInfo->tm_min;
    date.seconds = timeInfo->tm_sec;
}

int Node::get_index() const
{
    return index;
}

short Node::get_familiar_index() const
{
    return familiar_index;
}


Date Node::get_date() const
{
    return date;
}
string Node::get_key() const
{
    return key;
}

string Node::get_value() const
{
    return value;
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
void Node::add_value(string value)
{
    value = value + ", " + value;
}


ostream& operator<< (ostream& out, const Node& obj)
{
    
    out  << obj.get_key() << "|" << "   " << obj.get_value() << "|"  << "    " << obj.get_timeAdded() << "|" <<  endl << endl;

    // Use after finish to do list.
//    out << obj.get_index() << "     " << obj.get_key() << "|" << "   " << obj.get_value() << "|"  << "    " << obj.get_timeAdded() << "|" << "    " << obj.get_familiar_index() <<  endl << endl;
    return out;
}


