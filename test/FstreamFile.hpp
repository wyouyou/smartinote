//
//  FstreamFile.hpp
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



namespace test
{
    class FstreamFile;
    
}

class FstreamFile{
    
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
    
    FstreamFile(const std::string&);
    ~FstreamFile();
    std::string path;
    bool validFile;
    bool ContinousIndex;
    bool ValidLine;
    std::vector<int> indexs;
    /**
     * If the input file meeting cetain requirements.
     Program continue;
     * elif the input file has line with non continous index
     exit program and prompt error line
     * elif the input file does not meet the delimiters setting
     eixt program and prompt the error line.
     */
    void report() const;
};









#endif /* fstreamFile_hpp */

