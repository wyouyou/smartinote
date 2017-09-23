//
//  Tag.hpp
//  dic
//
//  Created by Jaye Wang on 9/8/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef Tag_hpp
#define Tag_hpp

#include <stdio.h>
#include "io/simpleIo.hpp"
#include <iostream>
#include <vector>

/*
 
 */
class Tag{
private:
    // a line of info
    std::string info;
    // a vector of info tokenized based on the info
    std::vector<std::string> subInfos;
    // number of subInfos
    short numSubInfos;
    
public:
    Tag();
    Tag(const std::string& info);
    
    // Modifies
    /**
     * update the subInfos based on the new info.
     */
    void update(const std::string& );
    
    // Accessors
    std::vector<std::string> getSubInfos() const;
    short getNumSubInfos() const;

    bool isEmpty() const;
    
    /**
     * Print the infoTrace from general to specific.
     */
    void printTrace() const;
    
};




#endif /* Tag_hpp */
