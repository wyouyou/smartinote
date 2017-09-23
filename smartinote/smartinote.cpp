
//  Smartinote.hpp
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Smartinote.hpp"


void Dic::write_new_node_to_file(fstream& fout, const List& L, const string& item)
{
    fout << * (L.get_top());
    
    L.get_top()->printNodeInfo(CONST::PRINT_WIDTH);
    //    cout << "\"" << item  << "\" is added to the database......\n";
//    all::UnixIO::printInColor(item, UnixIO::printWidth, Color::FG_PINK, " is added to the database :)\n");
    all::UnixIO::printInColor("    ...\n", Color::FG_PINK);
    
    // instant synchronization whenever note is added.
    copyDatabaseToArg(CONST::DATABASE_LOCATION.c_str());
    reportHtmlFile(CONST::HTML_OUT_LOCATION);

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
    
    string input = "word or a phrase", value = "no-explaination";
    Node * previousPtr = nullptr;
    
    // input tokens
    string first2chars;
    string first3chars;

    while (1)
    {
        // 请求一个单词，必须是正确的全拼写。
        all::UnixIO::smartinotePrompt();
        std:: cout << "(";
        tr::TimeRemainder::printCurrentTime();
        std::cout << ")";

        simpleIO::getLine(": ", input);
        
        string first4chars = input.substr(0,4);
        input = simpleIO::trim(input);
        
        first2chars = input.substr(0,2);
        first3chars = input.substr(0,3);
        
        // List member function 的返回值作为搜索结果
        Node* target = dic.find(input);
        // 如果找到，输出释义
        if (target)
            printActivity(previousPtr, target);
        // 如果没有找到，请求输入解释，并且加入List 和 dic file
        else if (previousPtr!=nullptr && (first3chars == "rst"||first4chars =="app "))
            previousPtr->valueUpdating(input.substr(3), first3chars);
        else if (input == "q" || input =="Q")
            break;
        else if (input == "clear")
            clear();
        else if (all::stdIO::isEnterKeyPressed(input))
            continue;
        else if(first2chars == "rv")
            reviewActivity(input.substr(2));
        else if (first2chars == "rm")
            deleteActivity(previousPtr,input.substr(2));
        else if (first3chars == "tag")
            groupActiviy(input.substr(3));
        else if (first2chars == "tm")
            timeActivity(input.substr(2));
        else if (!target)
            singleActivity(input, previousPtr);
        else simpleIO::dispalyFatalMessage(input);
    }
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
void Dic::reviewActivity(const std::string& line)
{
    std::string lineCopy = line;
    std::vector<std::string> tokens = simpleIO::getTokens(lineCopy);
    size_t length = tokens.size();
    
    int numNodesUserWantToreview = length >= 2? stoi(tokens.at(1)) : Node::numOfNodes;
    
    if (length < 1)
        all::UnixIO::displayMessage("Fatal: rd/sc/rd is not entered");
    else if (tokens.at(0) == "rd")
        dic.reviewRandomly(numNodesUserWantToreview);
    else if (tokens.at(0) == "st")
        dic.reviewScientificly(numNodesUserWantToreview);
    else if (tokens.at(0) == "td")
        dic.reviewToday(numNodesUserWantToreview);
    else
        simpleIO::dispalyFatalMessage("Command ");
    
}

void Dic::reportHtmlFile(const string& location) const
{
    List dicCopy;
    makeArgReverse(dicCopy);
    dicCopy.report2HtmlFile(location);
}


void Dic::timeActivity(const string& info) const
{
    string infoCoy = simpleIO::trim(info);
    vector<string> tokens = simpleIO::getTokens(infoCoy);
    
    // to do
    
//    if (tokens.at(0) == "add")
    
    
    tr::TimeRemainder t1(9,25,2017,0,0,0,1, "爱秋");
    tr::TimeRemainder t2(9,19,2017,18,49,00,1, "偏执");
    
    
    t1.printTimeDiffInfo();
    t2.printTimeDiffInfo();
    
    tr::TimeRemainder::printCurrentTime();
    
//    cout << t1 << endl << t2 << endl;
}


/**
 * IF the info is "", run as main prcess
 * If the info has content, run as sub main process
 *
 */
void Dic::groupActiviy(std::string info)
{
   // to do
}



void Dic::printActivity(Node*& previousNode, Node* target)
{
    target->printNodeInfo(CONST::PRINT_WIDTH, Color::FG_PINK);
    previousNode = target;

}



/**
 * Asking for inputing a value for the key arg.
 */
void Dic::singleActivity(const string& key, Node*& lastNode)
{
    string value = "no-explaination";
    fstream fout;
    //    Node * lastNode = nullptr;
    fout.open(FileLocation.c_str(),ios_base::app);
    if(!fout)
    {
        printf("Unable to open file at line number %d in file %s\n", __LINE__, __FILE__);
        exit(2);
    }
    
    // do while loop handle enter key accidently entered
    do
    {
        simpleIO::getLine(":", value);
        if (value == "q" || value =="Q") continue;
        else if (value.rfind("--q") != std::string::npos) continue;
        else if (value == "clear") clear();
        else if (all::stdIO::isEnterKeyPressed(value))
            continue;
        else
        {
            dic.push(key, value, time(0));
            lastNode = dic.find(key);
            write_new_node_to_file(fout,dic, value);
        }
    }while(value.empty());
    
    fout.close();
    
}


/*
 * Parse tokens and convert them all to ints stored in a vector.
 * remove multiple node based the indexs stored in the vector.
 */
void Dic::deleteActivity(const Node* previousPtr, string info)
{
    // remove the leading and tailing space
    info = simpleIO::trim(info);

    // rmove the last added node, useful when the last input accidently entered sth wrong but node has been added.
    if (info == "last")
    {
        if (previousPtr!=nullptr)
            dic.remove(previousPtr->get_key());
        else
            all::UnixIO::displayMessage("The node is alreay removed or does not exist.");
        
    }

    // if there is no real content
    if(info.size() < 1) all::UnixIO::printInColor("Too few arguments", Color::BG_RED);
    else{
        vector<string> tokens
        = simpleIO::getTokens(info);
        vector<string> keys(0);
        int index;
        
        for ( int i = 0; i < tokens.size(); i++)
        {
            // If the str is numeric, convert it to int
            //  else continue
            if (simpleIO::isNumeric(tokens.at(i)))
                index = stoi(tokens.at(i));
            else
                continue;
            // determine if the index is a within valid indexs
            // if it is valid index, add to the index to keys vectors
            Node* ptr = dic.find(index);
            // if ptr is null, means the index in out of range
            if (ptr != nullptr)
                keys.push_back((ptr->get_key()));
        }
        
        // remove node(s) based on the keys vector.
        for ( int i = 0; i < keys.size(); i++)
        {
//            Node copy = * dic.find(keys.at(i));
            Node * ptr = dic.find(keys.at(i));
            // if ptr is null means indexs has duplicates
            if (ptr != nullptr)
                dic.remove(keys.at(i));
        }
        
    }
}

