
//  Dic.cpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Dic.hpp"


const string DATABASE_LOCATION = "/Applications/selfmade-product/dic-master/data/test.md";


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
    cout << "\"" << item  << "\" is added to the database......\n";
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

Dic::Dic()
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
    
    string word = "word or a phrase", value = "no-explaination";
    fstream fout;
    fout.open(DATABASE_LOCATION.c_str(),ios_base::app);
    
    if(!fout)
    {
        printf("Unable to open file at line number %d in file %s\n", __LINE__, __FILE__);
        exit(2);
    }
    cin.ignore();
    
    while (1)
    {
        // 请求一个单词，必须是正确的全拼写。
        
        simpleIO::UnixIO::printInColor("\n➜ ", Color::FG_GREEN);
        simpleIO::String::getLine("***Enter key:(Enter 'q' or 'Q' to stop):", word);
        //        cout << "\n***Enter key:(Enter 'q' or 'Q' to stop): ";
        //        getline(cin, word);
        if (word == "q" || word =="Q") break;
        
        // List member function 的返回值作为搜索结果
        Node* target = dic.find(word);
        // 如果没有找到，请求输入解释，并且加入List 和 dic file
        if (target == 0)
        {
            //            cout << "Not found....Enter value: ";
            //            getline(cin,value);
            simpleIO::String::getLine("Not found....Enter value:", value);
            
            if (value == "q" || value =="Q") continue;
            else if (value == "clear")
            {
                clear();
            }
            else
            {
                dic.push(word, value, time(0));
                write_new_node_to_file(fout,dic, value);
            }
            
            
        }
        else target->printNodeInfo(80, Color::FG_LIGHT_Cyan);
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
        cerr << "Unable to open: " << DATABASE_LOCATION << endl;
        exit(1);
    }
    
    fout << dicCopy ;
    fout.close();
    
    //    cout << "Number Of nodes dic: " << dic.getNumOfNodes();
    //    cout << "Number Of nodes dicCopy: " << dicCopy.getNumOfNodes();
    
}

void Dic::reviewListRandomly(const short &num)
{
    dic.reviewListRandomly(num);
}

void Dic::reportHtmlFile() const
{
    List dicCopy;
    makeArgReverse(dicCopy);
    dicCopy.report2HtmlFile();
}

void Dic::dicCore()
{
    string command;
    
    while(1)
    {
        simpleIO::UnixIO::printInColor("➜ ", Color::FG_GREEN);
        simpleIO::String::getLine("Command Dic: ",command,Color::FG_LIGHT_Cyan);
        
        if (command == "dic")
        {
            userInteractive();
        }
        else if(command == "review")
        {
            reviewListRandomly(10);
        }
        else if (command == "q" || command == "Q")
        {
            break;
        }
        else if (command.substr(0,2) == "rm")
        {
            deleteActivity(command.substr(3));
        }
        else if (command == "time")
        {
            timeInfo();
        }
        else if (command == "clear")
        {
            clear();
        }
        else simpleIO::String::dispalyFatalMessage(command);
        
    }
    
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
    
    size_t posStart = info.find_first_not_of(' ');
    size_t posEnd = info.find_last_not_of(' ');
    info = info.substr(posStart, posEnd-posStart+1);
    
    exit(10);
    
    Node copy = * dic.find(stoi(info));
    
    if(dic.remove(stoi(info)))
        copy.printNodeInfo(80, Color::FG_RED);
    simpleIO::UnixIO::printInColor(" is removed", Color::FG_RED);
    
}

