
/*
 * File: Node.h
 *
 */

#ifndef Node_h
#define Node_h


#include <iostream>
#include <string>
#include <fstream>
#include "io/simpleIo.hpp"
#include "time/TimeRemainder.hpp"
#include "Tag.hpp"





#define clear() printf("\033[H\033[J")

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
    
    void set_Date(tm* timeInfo)
    {
        year2digits = timeInfo->tm_year % 100;
        year4digits = 2000 + year2digits;
        month = timeInfo->tm_mon + 1;
        day_of_month = timeInfo->tm_mday;
        day_of_week = timeInfo->tm_wday;
        day_in_the_year = timeInfo->tm_yday;
        hour = timeInfo->tm_hour;
        minutes = timeInfo->tm_min;
        seconds = timeInfo->tm_sec;
    }
};


/*
 Notes for adding a data member:
 
 add data member declaration inside class declration
 
 add accessor function for this data member.
 
 */


/**
 Two parts of this Node.
 1. Data members contains the data stored in the node.
 2. A pointer points to another node in the list
 */
class Node
{
    
    int index;
    string key;
    string value;
    time_t timeAdded;
    
    /**
     * date is assigned whenever timeAdded is assigned.
     * date get chance to be assigned value for any args only
     * if copying/cloning node happens.
     */
    Date date;
    
    /**
     * familiar_index = Times user have commited that they have known key
     *
     */
    short familiar_index;
    
    /**
     * familiar_percent = familiar_index / 21;
     * familiar_percent is assigned whenever familiar_index is assigned.
     * familiar_percent get chance to be assigned value for any args only
     * if copying/cloning node happens
     */
    double familiar_percent;
    
    
    Tag tag;
    
    Node* next; //self-referential data structure.
    
    
    
    
    
public:
    
    /**
     * intialize a data struct
     */
    void init_date();

    /**
     * Usage: when remove node happen, call this.
     */
    static void decrementNumOfNodes();
    
    /**
     * numofNodes will get incremented  when creating/adding a new node 
     * and reading node from file.
     *
     * Will not change when coping/cloning node.
     */
    static int numOfNodes;
    /**
     * Adding a node, 增加数据时候使用
     * index class 内部自动更新
     * date is initalized based on timeAdded.
     */
    Node (string key, string value, Node*n, time_t t );
    /**
     Reading a node, used when retrive data from the local file.
     index, key , value , timeAdded, are all read from the local file.
     date is intialized based on timeAdded.
     */
    Node(const int& i, const string& k, const string& v, const time_t& t,const short& familiar_Index, Node* n );

    /**
     * Copying/clone a node, used when make a copy of list so that every
     * data member is passed in from outside.
     */
    Node(const int& i, const string& k, const string& v, const time_t& t, const Date& d,const short& familiar_Index,const double& famPercent, Node* n );

    /**
      * Add 1 to the familiar index.
     *
     * 根据艾宾浩斯记忆曲线指数。
     * If the familiar_index == 21, delete the node and add it to a file
     * to save for later use.
     */
    void incre_familiar_index();
    
    /**
     * Subtract 1 from the familiar index.
     */
    void decre_familiar_index();
    
    /**
     * Accessor functions
     */
    int get_index() const;
    string get_key() const;
    string get_value() const;
    time_t get_timeAdded() const;
    short get_familiar_index() const;
    double get_familiar_percent() const;
    Date get_date() const;
    Node* get_next() const;
    void set_next(Node* ptr);
    bool set_value(const string& theValue);
    bool append_value(const string& toBeAppend);
    void valueUpdating(const string& newStuff,
                       const string& choice);
    
    void decrementIndex();
    void incrementIndex();

    /**
     * Modify data member value.
     */
    void add_value(string);
    /**
     *
     */
    std::string review();
    
    /** 
     * console output functions
     */
    void printIndexInfo() const;
    void printTimeAdded() const;
    void printFamilarIndexInfo() const;
    
    /**
     * print node in a specified width and color,
     *
     * default case: no parameter, print in default setting color.
     */
    void printNodeInfo(const int& width , Color::Code = Color::BG_DEFAULT) const;
    
    /**
     *
     */
    void report2HtmlFile(ofstream& fout) const;
    
    /**
     * write html table heading
     */
    static void write2HtmlTableHeading(ofstream& fout);
    
    /**
     * write html table tail.
     */
    static void write2HtmlTableTail(ofstream& fout);
    
    /**
     * write one row html of table.
     */
    void write2Html1RowOfTb(ofstream& fout) const;
    
    bool isBornedToday() const;
    
    bool is124711DaysAgo() const;
    
    
    
    

    
    
    
};


std::ostream& operator<< (std:: ostream&, const Node&);

#endif /* Node_h */
