//
//  fstreamFile.cpp
//  dic
//
//  Created by Jaye Wang on 8/29/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "fstreamFile.hpp"


fstreamFile::fstreamFile(const std::string& location): path(location), lineCount(0)
{
    std::ifstream fin(path.c_str());
    if (fin.fail())
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        std::cerr << "Unable to open: " << location << std::endl;
        exit(1);
    }
    alloc(fin);
    
    fin.open(path.c_str());
    init(fin);
    
    if(checkLine() && checkIndex()) validFile = true;
}


fstreamFile::~fstreamFile()
{
    delete [] index;
    delete [] line;
}

void fstreamFile::alloc(std::ifstream& fin)
{
    // Calculate number of "valid line"s in the database file
    std::string temp;
    while (fin >> temp)
    {
        getline(fin,temp);
        lineCount++;
    }
    
    index = new int[lineCount];
    line = new std::string[lineCount];
    
    fin.close();
    
}


void fstreamFile::init(std::ifstream& fin)
{
    std::cout << "Line count: " << lineCount << std::endl;
    for (int i = 0; i < lineCount; i++)
    {
        fin >> index[i];
        getline(fin,line[i]);
    }
    fin.close();
}

bool fstreamFile::checkLine()
{
    // 09/01: To be done when list member is complete.
    ValidLine = 1;
    
    return true;
}

// determine whether all the index 是以1为公差的等差数列
bool fstreamFile::checkIndex()
{
    
    ContinousIndex = true;
    int diff;
    for (int i = 0; i< lineCount-1; i++)
    {
        diff = index[i+1] - index[i];
        if (diff < 0) diff = -diff;
        if (diff!= 1)
        {
            ContinousIndex = false;
            errorLine = i;
        }
    }
    return ContinousIndex;
}


void fstreamFile::report() const
{
    
    if(validFile)
    {
        return;
    }
    else  if (!ContinousIndex)
     {
        std::cout << path << " file's "
        << " indexs is not continous"
        << std::endl << "Error line around: " << errorLine
        << std::endl;
         exit(1);
     }
    else if (!ValidLine)
    {
                std::cout << path << " file's "
        << " line is not valid for the driver program!"
        << std::endl << "Error line around: " << errorLine
        << std::endl;
        exit(2);

    }
    else
        std::cout << "Never got here!";
    
}
