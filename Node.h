

#ifndef Node_h
#define Node_h

#include <iostream>
#include <string>

using namespace std;

/**
 ************************************************************************
 Print colorful context in Linux. 待定
 https://stackoverflow.com/a/17469726
 */
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
        
        
    };
    class Modifier {
        Code code;
    public:
        Modifier(){};
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}



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
    
    int index;
    string key;
    string value;
    time_t timeAdded;
    Date date;
    short familiar_index;
    Node* next; //self-referential data structure.
    void init_date();
    
public:
    static int numOfNodes;
    /**
     ********************************************************************
     Adding a node, 增加数据时候使用
     index class 内部自动更新
     date is initalized based on timeAdded.
     */
    Node (string key, string value, Node*n, time_t t );
    /**
     ********************************************************************
     Reading a node, used when retrive data from the local file.
     index, key , value , timeAdded, are all read from the local file.
     date is intialized based on timeAdded.
     */
    Node(const int& i, const string& k, const string& v, const time_t& t,const short& familiar_Index, Node* n );

    /**
     ********************************************************************
     Copying/clone a node, used when make a copy of list so that every 
     data member is passed in from outside.
    */
    Node(const int& i, const string& k, const string& v, const time_t& t, const Date& d,const short& familiar_Index, Node* n );

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
    /**
     ********************************************************************
     */
    void reviewNode()
    {
        char remember;
        string validRemember = "YyNn";
        cout << "\n\n认识这个key吗？--------->" << this->key << "\n\nPress 'Y' or 'y', press 'N' or 'n' 如果不认识: ";
        cin >> remember;
        
        do{
        if (remember == 'Y'  or remember == 'y')
        {
            familiar_index++;
            cout << "Familar index + 1: " << familiar_index << endl;
        }
        else if (remember == 'N' or remember == 'n')
        {
            familiar_index--;
            cout << "Familar index - 1: " << familiar_index << endl;

        }
            cout << "---------------------->" << value << "\n";
        } while (validRemember.find(remember) == string::npos);
    }
    
    void printIndexInfo() const;
    void printkeyNValue() const;
    void printTimeAdded() const;
    void printFamilarIndexInfo() const;
    void printNodeInfo() const;
    
    
};


std::ostream& operator<< (std:: ostream&, const Node&);

#endif /* Node_h */
