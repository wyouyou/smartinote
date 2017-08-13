//
//  Dic.hpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef Dic_hpp
#define Dic_hpp

#include <stdio.h>
#include <iostream>
#include "List.h"
#include <fstream>
#include <cstdlib>

class Dic
{
private:
    List dic;
    
    /**
     *****************************************************************
     The third parameter tag: is used to debug (printing out) purpose.
     Tag describe what element is read. Ex: key, value, timeAdded....
     */
    void readOneElement(string& element, ifstream& fin, const string& tag);
    /**
     *****************************************************************
     Append mode. If the file already exists, its contents are preserved
     andall output is written to the end of the file. Bydefault,this
     flag causes the file to be created if it does not exist.
     */
    void write_new_node_to_file(fstream& fout, const List& L, const string& fileName = "/Applications/selfmade-product/dic-master/data/dic.md" );

public:
    
    /**
     ***************************************************************
     Retrive data from local database folder.
     */
    Dic();
    void userInteractive();
    /**
     **************************************************************
     备份 database to the location where the arg is.
     */
    void copyDatabaseToArg(const char arg[]) const;
    /**
     ****************************************************************
     */
    void reviewByForgetiveCurve(const short& num)
    {
        dic.reviewList(num);
    }
    
    
    
};

#endif /* Dic_hpp */
