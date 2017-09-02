//
//  fstreamFile.hpp
//  dic
//
//  Created by Jaye Wang on 8/29/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef fstreamFile_hpp
#define fstreamFile_hpp
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
//#include "io/simpleIo.hpp"

namespace test
{
    class fstreamFile;

}

class fstreamFile{
    
private:
    int errorLine;
    int * index;
    std::string * line;
    bool checkLine();
    bool checkIndex();
    int lineCount;
    /**
     *inti lineCount and allocate memory for index and line
     */
    void alloc(std::ifstream& fin);
    void init(std::ifstream& fin);

    
public:
    
    fstreamFile(const std::string&);
    ~fstreamFile();
    std::string path;
    bool validFile;
    bool ContinousIndex;
    bool ValidLine;
    std::vector<int> indexs;
    void report() const;
};









#endif /* fstreamFile_hpp */
