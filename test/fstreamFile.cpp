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
    std::string temp;
    while (!fin.eof())
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
    
    return true;;
}


bool fstreamFile::checkIndex()
{
    ContinousIndex = 1;
    int diff;
    for (int i = 0; i< lineCount-1; i++)
    {
        diff = index[i] - index[i+1];
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
    if (ValidLine) return;
    else if (!ContinousIndex)
        std::cout << path << " file's "
        << " indexs is not continous"
        << std::endl << "Error line around: " << errorLine
        << std::endl;
    else if (!ValidLine)
        std::cout << path << " file's "
        << " line is not valid for the driver program!"
        << std::endl << "Error line around: " << errorLine
        << std::endl;
    else
        std::cout << "Never got here!";
    
}
