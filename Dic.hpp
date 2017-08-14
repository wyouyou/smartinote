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
#include <fstream> 

 
class Dic
{
private:
    List dic;
    
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
    void write_new_node_to_file(fstream& fout, const List& L, const string& fileName = "/Applications/selfmade-product/dic-master/data/dic.md" );

public:
    
    /**
     * Constructor
     * Retrive data from local database folder.
     */
    Dic();
    
    /**
     *
     */
    void userInteractive();
    /**
     *
     * 备份 database to the location where the arg is.
     * 或者 更新数据库
     */
    void copyDatabaseToArg(const char arg[]) const;
    
    /**
     *
     */
    void reviewListRandomly(const short& num);
    /**
     *
     */
    
    
    
    
};

#endif /* Dic_hpp */
