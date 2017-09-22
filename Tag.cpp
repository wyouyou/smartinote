//
//  Tag.cpp
//  dic
//
//  Created by Jaye Wang on 9/8/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Tag.hpp"


Tag::Tag()
{
}

Tag::Tag(const std::string& theInfo): info(theInfo)
{
    
    
    subInfos = simpleIO::getTokens(theInfo, "-");
}


/*
 * Tokenize the theInfo
 * get union of subInfos and all the new tokenized subinfo
 */
void Tag::update(const std::string& theInfo)
{
    if (theInfo.size() == 0)
        return;
    
    std::vector<std::string> tempInfos =simpleIO::getTokens(theInfo, "-");

    // adding each element of the tempInfos to subInfos if the element does not exist in the subInfos
    // ...use set_union
    
    std::vector<std::string> subInfosCopy = subInfos;
    //http://en.cppreference.com/w/cpp/algorithm/set_union
    
    std::set_union(subInfosCopy.begin(), subInfosCopy.end(),
                   tempInfos.begin(), tempInfos.end(),
                   std::back_inserter(subInfos));
}


std::vector<std::string> Tag::getSubInfos() const
{
    return subInfos;
}


short Tag::getNumSubInfos() const
{
    return numSubInfos;
}


bool Tag::isEmpty() const
{
    if (numSubInfos == 0)
        return true;
    else
        return false;
}

void Tag::printTrace() const
{
    if (isEmpty())
        std::cout << "Default tag" << std::endl;
    else
    {
        for (int i = 0; i < subInfos.size(); i++)
            std::cout << subInfos.at(i) << "->";
        std::cout << std::endl;
    }
}

