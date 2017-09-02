
//  Dic.cpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Dic.hpp"




void Dic::readOneElement(string& element, ifstream& fin, const string& tag)
{
    
    string buffer;
    fin >> buffer;
    
    size_t pos_end_of_the_element = buffer.find_first_of('|');
    
    //If it is not single word but a phrase
    // Or If the explanation is not short enough so that the temp is not a complete a explanation   ex: xx xx|
    if (pos_end_of_the_element == string::npos) // npos means no found
    {
        getline(fin, element, '|'); // delimeter '|' excludeable
        
        element = buffer + element;
    }
    
    // If it is a single word right before the dilimeter '|', remove
    // the delimeter '|'
    // Or If the explanation is short enough: ex: xx|
    else element = buffer.substr(0, pos_end_of_the_element);
    /*Debug Code*/
    
    /************************Debug Code********************************/
    //    cout << "The " << tag  << " is : " << "\"" << element  << "\"" << endl;
    /******************************************************************/
    
}


void Dic::write_new_node_to_file(fstream& fout, const List& L, const string& item)
{
    fout << * (L.get_top());
    //    cout << "\"" << item  << "\" is added to the database......\n";
    simpleIO::UnixIO::printInColor(item, 80, Color::FG_PINK, "is added to the dataabse...");
}



void Dic::retriveDataFromFile(ifstream& fin)
{
    int index = -1;
    string key = "defalut-key", value = "default-value", str_timeAdded ="default-timeAddedStr";
    time_t timeAdded = -1;
    short familiar_index = -1;
    
    while (fin.peek() != EOF)
    {
        // 0. Read index
        fin >> index;
        
        //1. Read key
        readOneElement(key, fin, "wordOrPhrase");
        
        if (dic.find(key) == 0) // Remove EOF duplicate error
        {
            //2. Read value
            readOneElement(value, fin, "explaination");
            //3. Read timeAdded
            readOneElement(str_timeAdded, fin, "timeAdded");
            // 4. Read familiar index
            fin >> familiar_index;
            /*
             get current date/time
             The function atoll in stdlib.h convert a c-string to long
             long type.
             */
            timeAdded = (time_t)atoll(str_timeAdded.c_str());
            
            dic.pushFromFile( index, key, value, timeAdded, familiar_index);
        }
        
    }
    
}

Dic::Dic(const string& DATABASE_LOCATION): FileLocation(DATABASE_LOCATION)
{
    
    ifstream fin(DATABASE_LOCATION.c_str());
    if(!fin)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << DATABASE_LOCATION << endl;
        exit(1);
    }
    
    retriveDataFromFile(fin);
    
    fin.close();
}

void Dic::userInteractive()
{
    
    string key = "word or a phrase", value = "no-explaination";
    fstream fout;
    Node * copy = nullptr;
    fout.open(FileLocation.c_str(),ios_base::app);
    if(!fout)
    {
        printf("Unable to open file at line number %d in file %s\n", __LINE__, __FILE__);
        exit(2);
    }
    while (1)
    {
        // 请求一个单词，必须是正确的全拼写。
        simpleIO::UnixIO::geeklePrompt();
        simpleIO::String::getLine(": ", key);
        // List member function 的返回值作为搜索结果
        Node* target = dic.find(key);
        
        if (key == "q" || key =="Q") break;
        else if (key == "clear") clear();
        else if (target)
        {
            target->printNodeInfo(80, Color::FG_PINK);
            copy = target;
        }
        // rm means rmove the last added node, useful when the last input accidently entered sth wrong but node has been added.
        else if (key == "rm last")
        {
            if (copy!=nullptr)
                dic.remove(copy->get_key());
            else
                break;
        }
        else if(key.substr(0,2) == "rv")
            review(key.substr(2));
        else if (key.substr(0,2) == "rm")
            deleteActivity(key.substr(2));
        else if (key == "time")
            timeInfo();
        // 如果没有找到，请求输入解释，并且加入List 和 dic file
        else if (!target)
        {
            simpleIO::String::getLine(":", value);
            if (value == "q" || value =="Q") continue;
            else if (value.rfind("--q") != std::string::npos) continue;
            else if (value == "clear") clear();
            else
            {
                dic.push(key, value, time(0));
                copy = dic.find(key);
                write_new_node_to_file(fout,dic, value);
            }
        }
        else simpleIO::String::dispalyFatalMessage(key);
    }
    fout.close();
}

void Dic::makeArgReverse(List& dicCopy) const
{
    Node* temp = dic.get_top();
    while (temp != 0)
    {
        dicCopy.pushFromNode(temp->get_index(),temp->get_key(), temp->get_value(), temp->get_timeAdded(), temp->get_date(),temp->get_familiar_index(), temp->get_familiar_percent());
        temp = temp->get_next();
    }
    
}

void Dic::copyDatabaseToArg(const char arg[]) const
{
    // Creat a copy of dic to deal with LIFO issue
    List dicCopy;
    
    makeArgReverse(dicCopy);
    
    ofstream fout;
    fout.open(arg);
    if (!fout)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << FileLocation << endl;
        exit(1);
    }
    
    fout << dicCopy ;
    fout.close();
    
    //    cout << "Number Of nodes dic: " << dic.getNumOfNodes();
    //    cout << "Number Of nodes dicCopy: " << dicCopy.getNumOfNodes();
    
}


/*
 line format: rd/st/td number
 */
void Dic::review(const std::string& line)
{
    std::string lineCopy = line;
    std::vector<std::string> tokens = simpleIO::String::getTokens(lineCopy);
    size_t length = tokens.size();
    
    int numNodesUserWantToreview = length >= 2? stoi(tokens.at(1)) : CONST::NUM_NODES_TO_REVIEW;
    
    
    if (length < 1)
        simpleIO::UnixIO::displayMessage("Fatal: rd/sc/rd is not entered");
    else if (tokens.at(0) == "rd")
        dic.reviewRandomly(numNodesUserWantToreview);
    else if (tokens.at(0) == "st")
        dic.reviewScientificly(numNodesUserWantToreview);
    else if (tokens.at(0) == "td")
        dic.reviewToday(numNodesUserWantToreview);
    else
        simpleIO::String::dispalyFatalMessage("Command ");
        


}

void Dic::reportHtmlFile(const string& location) const
{
    List dicCopy;
    makeArgReverse(dicCopy);
    dicCopy.report2HtmlFile(location);
}


void Dic::timeInfo() const
{
    tr::TimeRemainder t1(9,25,2017,0,0,0,1, "距离Fall quater 2017 begin");
    tr::TimeRemainder t2(8,17,2017,00,00,00,00, "距离上上一次...");
    tr::TimeRemainder t3(8,28,2017,00,00,00,00, "距离上一次...");
    
    cout << t1 << endl << t2 << t3 << endl;
}

void Dic::deleteActivity(string info)
{
    info = simpleIO::String::trim(info);
    
    if(info.size() < 1) simpleIO::UnixIO::printInColor("Too few arguments");
    else{
        
        vector<string> tokens = simpleIO::String::getTokensWhatTheHellTheOtherOneDoesNotWork(info);
        
        vector<string> keys(0);
        
        for ( int i = 0; i < tokens.size(); i++)
        {
            int index = stoi(tokens.at(i));
            Node* ptr = dic.find(index);
            if (ptr) keys.push_back((ptr->get_key()));
            else cout << "Invalid index: " << index << endl;
            
        }
        
        for ( int i = 0; i < keys.size(); i++)
        {
            Node copy = * dic.find(keys.at(i));
            dic.remove(keys.at(i));
            
        }
        
    }
}

