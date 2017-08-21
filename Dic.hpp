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
    void write_new_node_to_file(fstream& fout, const List& L, const string& message = " ");
    
    
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
    void reportHtmlFile() const;
    /**
     * Make arg a reverse order copy of dic.
     *
     */
    void makeArgReverse(List& dicCopy) const ;
    
    /**
     * deleteActivity member function Deleting node manually.
     * Deleting mode: by index, key.
     *
     */
    void deleteActivity()
    {
        string Index;
        
        while (1)
        {
            cout << "Enter a index: ";
            cin >> Index;
            if (Index == "q" || Index == "Q") break;
            
            else if (Index == "clear") clear();
            
            else
            {
                
                if(dic.remove(stoi(Index)))
                    cout << "Node with index: " << Index << " has been deleted.\n";
            }

        }
        
    }
    /**
     * run
     */
    void dicCore();
    
    
    
    
    
    
    
};

#endif /* Dic_hpp */
