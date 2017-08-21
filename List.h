
/*
 * File: List.h
 *
 */
#ifndef List_h
#define List_h

#include "Node.h"


class List
{
    Node* top;
    /**
     * If the familiar_index = 21 delete the node.
     * And print a message. 
     */
    void deleteNodeIfFamiliarEnough(Node* theNode);

public:
    List();
    ~List();
    /**
     *
     * Adding a new node to the list.
     */
    void push(string item ,string c, time_t t );
    /**
     * Pushing a new node read from a file.
     */
    void pushFromFile(const int& i, const string& k, const string& v, const time_t& t, const short& familiar_index);
    /**
     * Pushing a new node from a copy of another node.
     */
    void pushFromNode(const int& i, const string& k, const string& v, const time_t& t, const Date& d,const short& familiar_Index,const double& famPercent);
    /**
     *
     */
    void add_value(string value, Node* target);
    /**
     *
     */
    string pop();
    
    Node* get_top() const;
    /**
     * Remove node with the same key as the arg.
     */
    bool remove(const string& key);
    
    
    /**
     * Remove node with the same index as the arg.
     */
    bool remove(const int& index);
    
    /**
     * return the address of the node with the same key as arg.
     * return 0 if not found.
     */
    Node* find(const string& key) const;
    
    /**
     * return the address of the node with the same index as arg.
     * return 0 if not found.
     */ 
    Node* find(const int& index) const;
    
    /**
     *
     */
    bool remove_Last();
    
    /**
     * Review List randomly
     * Printing out num of nodes to console.
     * Every node's familiar_index get updated.
     */
    void reviewListRandomly(const short& num);
    
    /**
     * Review List according to the forgetness curve.
     * Print nodes with the following sequence.
     * Today's nodes.
     * 1 天前的nodes
     * 2 天前的nodes
     * 4 天前的nodes
     * 7 天前的nodes.
     */
    void reviewListScientificly();
    
    /**
     * reportHtmlFile
     * report list to a html file on the location:
     * Dic.cpp HTML_OUT_LOCATION
     *
     */
    void report2HtmlFile() const;
    
    /**
     * keepIndexContinous to keep all the nodes in an continous order.
     *
     * Usage: called whenever remove funtions get called.
     */
    void keepIndexContinous(Node* );
    
    
    
};

std::ostream& operator << (std::ostream&, const List&);

#endif /* List_h */
