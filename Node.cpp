/**
 * File: Node.cpp
 */

#include "Node.h"

int Node::numOfNodes = 0;

/**
 * creating/adding node...
 * key + value + timeAdded are intialized from the user input.
 *
 * index = the current incremented numOfNodes.
 * all new node created from the user has a familiar_index = 0 by default.
 * date is intialized based on timeAdded (the time when the node was born)
 * familiar_percent is intialized based on familiar_index, 0 in this case.
 */
Node::Node(string theKey, string theValue, Node*n, time_t t ): key(theKey), value(theValue),next(n), timeAdded(t)
{
    index = ++numOfNodes;
    familiar_index = 0;
    init_date();
    familiar_percent = 0;
}

/**
 * reading node from file...
 * index + key + value + timeAdded + familiar_index are intialized from 
 * the input file corresponding data filed.
 *
 * numOfNodes is incremented whenever a node is read from file.
 * date is intialized based on timeAdded read from file.
 * familiar_percent is intialized based on familiar_index.
 */
Node::Node(const int& i, const string& k, const string& v, const time_t& t,const short& familiar_Index, Node* n): index(i), key(k),value(v),timeAdded(t),familiar_index(familiar_Index),next(n)
{
    ++numOfNodes;
    init_date();
    familiar_percent = familiar_index/21.;
}

/**
 * copying/cloning node form another node...
 * every data member is intialized by the args.
 */
Node::Node(const int& i, const string& k, const string& v, const time_t& t, const Date& d ,const short& familiar_Index, Node* n): index(i), key(k),value(v),timeAdded(t), date(d),familiar_index(familiar_Index), next(n)
{
}

void Node::init_date()
{
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


void Node::printIndexInfo() const
{
    cout << key << " is the " << index << " word in the dic.md.\n";
}
void Node::printkeyNValue() const
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    cout  << red << value << def << "\n";
    
}
void Node::printTimeAdded() const
{
    cout << "Time Added:" << date.year2digits << "\\" << date.month << "\\" << date.day_of_month << " " << date.hour << ":" << date.minutes << ":" << date.seconds << "星期" << date.day_of_week << endl;
    
}
void Node::printFamilarIndexInfo() const
{
    
    cout << "Familiar index: " << familiar_index << ":";
    if (familiar_index < 7)
    {
        cout << "Notice! this word is a stranger to you!" <<familiar_percent << "% familiar...\n";
    }
    else if (familiar_index > 7 && familiar_index < 14)
    {
        cout << "Good! this word is a acquaintance to you!" <<familiar_percent << "% familiar...\n";
    }
    else if (familiar_index > 14)
    {
        cout << "Great! this word is gonna be your friend!" <<familiar_percent << "% familiar...\n";
    }
}

void Node::printNodeInfo() const
{
    ClearScreen();
    
    printAline();
    printIndexInfo();
    
    printAline();
    printkeyNValue();
    
    printAline();
    printFamilarIndexInfo();
    
    printAline();
    printTimeAdded();
    printAline();
}

void Node::ClearScreen() const
{
    cout << string( 100, '\n' );
}

void Node::printAline() const
{
    cout << "---------------------------------------------------------\n";
}


ostream& operator<< (ostream& out, const Node& obj)
{
    
    out << obj.get_index() << "     " << obj.get_key() << "|" << "   " << obj.get_value() << "|"  << "    " << obj.get_timeAdded() << "|" << "    " << obj.get_familiar_index() <<  endl << endl;
    return out;
}


