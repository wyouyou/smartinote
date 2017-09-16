//
//  Dic.hpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef Dic_hpp
#define Dic_hpp

#include "List.h"
#include "lib/time/TimeRemainder.hpp"
//#include "time/TimeRemainder.cpp"




class Dic
{
private:

    List dic;
    string FileLocation;

    /**
     * Retrive all nodes from local file:
     *
     */
    void retriveDataFromFile(ifstream& fin);
    
    /**
     * The third parameter tag: is used to debug (printing out) purpose.
     * Tag describe what element is read. Ex: key, value, timeAdded....
     */
    void readOneElement(string& element, ifstream& fin, const string& tag);
    
    /**
     *
     * Append mode. If the file already exists, its contents are preserved
     * and all output is written to the end of the file. Bydefault,this
     * flag causes the file to be created if it does not exist.
     */
    void write_new_node_to_file(fstream& fout, const List& L, const string& message = " ");
    
    
public:
    
    /**
     * Constructor
     * Retrive data from local database folder.
     */
    Dic(const string& DATABASE_LOCATION);
    
    /**
     *
     */
    void userInteractive();
    /**
     * The core feature menus of the Dic application.
     * 备份 database to the location where the arg is.
     * 或者 更新数据库
     */
    void copyDatabaseToArg(const char arg[]) const;
    
    /**
     *
     */
    void reviewActivity(const std::string& line);
    /**
     *
     */
    void reportHtmlFile(const string& location) const;
    /**
     * Make arg a reverse order copy of dic.
     *
     */
    void makeArgReverse(List& dicCopy) const ;
    
    /**
     * print nodets found after search
     * update previousNode ptr
     */
    void printActivity(Node*& previousNode, Node* target);
    

    
    /**
     * A single note insertion
     */
    void singleActivity(const string& key,Node*& node);
    
    /**
     * groupActivity is a sub dic process with a set of specific tag
     * multiple notes insertion
     */
    void groupActiviy(std::string info);
    
    /**
     * deleteActivity member function Deleting node manually.
     * delete mutiple node based on the tokens of info
     */
    void deleteActivity(const Node* previousPtr, std::string info);
    
    void timeActivity(const string& info) const;

};

#endif /* Dic_hpp */
