

#ifndef Node_h
#define Node_h

#include <iostream>
#include <string>

using namespace std;

struct Date{
    int year2digits; //
    int year4digits; // >= 2000
    int month; // [1,12]
    int day_of_month; // [1-31]
    int day_of_week; // [1,7]
    int day_in_the_year; // [1,366]
    int hour; // [0,24]
    int minutes; //[0,59]
    int seconds;//[0,59]
};


/**
 Two parts of this Node.
 1. Data members contains the data stored in the node.
 2. A pointer points to another node in the list
 */
class Node
{
    
    static int numOfNodes;
    int index;
    string key;
    string value;
    time_t timeAdded;
    Date date;
    short familiar_index;
    Node* next; //self-referential data structure.
    
public:
    Node (string d, string c, Node*n, time_t t );
    /**
     ********************************************************************
     Add 1 to the familiar index.
     
     根据艾宾浩斯记忆曲线指数。
     If the familiar_index == 21, delete the node and add it to a file to
     save for later use.
     */
    void incre_familiar_index(const string& fileName);
    
    /**
     ********************************************************************
     Subtract 1 from the familiar index.
     
     */
    void decre_familiar_index();
    
    /**
     ********************************************************************
     Accessor functions
     */
    int get_index() const;
    string get_key() const;
    string get_value() const;
    time_t get_timeAdded() const;
    short get_familiar_index() const;
    Date get_date() const;
    Node* get_next() const;
    void set_next(Node* ptr);
    /**
     ********************************************************************
     Modify data member value.
     */
    
    void add_value(string);
};


std::ostream& operator<< (std:: ostream&, const Node&);

#endif /* Node_h */
