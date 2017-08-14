/**
 This Node contail a general English word contaning value value.
 
 */

#include "Node.h"

int Node::numOfNodes = 0;

Node::Node(string d,string c ,Node* n, time_t t): key(d), value(c),next(n), timeAdded(t)
{
    index = ++numOfNodes;
    familiar_index = 0;
    init_date();
}

Node::Node(const int& i, const string& k, const string& v, const time_t& t,const short& familiar_Index, Node* n): index(i), key(k),value(v),timeAdded(t),familiar_index(familiar_Index),next(n)
{
    
}

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
    cout << "\nThis the " << index << " node in the dic file.\n";
}
void Node::printkeyNValue() const
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    cout  << "\n" << red << value << def << "\n";

}
void Node::printTimeAdded() const
{
    cout << "\nTime Added:" << date.year2digits << "\\" << date.month << "\\" << date.day_of_month << " " << date.hour << ":" << date.minutes << ":" << date.seconds << "星期" << date.day_of_week << endl;
    
}
void Node::printFamilarIndexInfo() const
{
    cout << "\n Familiar index: " << familiar_index << ":";
    if (familiar_index < 7)
    {
        cout << "Notice! this word is a stranger to you.\n";
    }
    else if (familiar_index > 7 && familiar_index < 14)
    {
        cout << "Good! this word is a acquaintance to you.\n";
    }
    else if (familiar_index > 14)
    {
        cout << "Great! this word is gonna be your friend.\n";
    }
}

void Node::printNodeInfo() const
{
    printIndexInfo();
    printkeyNValue();
    printFamilarIndexInfo();
    printTimeAdded();
}



ostream& operator<< (ostream& out, const Node& obj)
{
    
//    out  << obj.get_key() << "|" << "   " << obj.get_value() << "|"  << "    " << obj.get_timeAdded() << "|" <<  endl << endl;

//     Use after finish to do list.
    out << obj.get_index() << "     " << obj.get_key() << "|" << "   " << obj.get_value() << "|"  << "    " << obj.get_timeAdded() << "|" << "    " << obj.get_familiar_index() <<  endl << endl;
    return out;
}


