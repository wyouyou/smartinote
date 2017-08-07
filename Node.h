

#ifndef Node_h
#define Node_h

#include <iostream>
#include <string>

using namespace std;


/**
Two parts of this Node.
 1. Data members contains the data stored in the node. 
 2. A postringer points to another node in the list
 */
class Node
{

    time_t timeAdded;
    string data;
    string explanation;
    Node* next; //self-referential data structure.
public:
    Node (string d, string c, Node*n, time_t t );
    Node (string d, string c, Node* );
    string get_data() const;
    string get_explanation() const;
    time_t get_timeAdded() const;
    Node* get_next() const;
    void set_next(Node* ptr);
    void add_explanation(string);
    /*
     初始化当前时间以秒的形式到timeAdded. 
     
     目的：用于根据单词添加时间来排序单词
     
     To do：添加一个成员函数用来输出时间格式
     */
    void add_timeAdded();
};

std::ostream& operator<< (std:: ostream&, const Node&);

#endif /* Node_h */
