//
//  Dic.cpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Dic.hpp"


using namespace std;
const string DATABASE_LOCATION = "/Applications/selfmade-product/dic-master/data/dic.md";

/**
 ************************************************************************
 Print colorful context in Linux. 待定
 https://stackoverflow.com/a/17469726
 */
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
        
        
    };
    class Modifier {
        Code code;
    public:
        Modifier(){};
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
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


void Dic::write_new_node_to_file(fstream& fout, const List& L, const string& fileName)
{
    
    fout.open(DATABASE_LOCATION.c_str(),ios_base::app);
    
    if(!fout)
    {
        cerr << "Invalid directory: " << DATABASE_LOCATION;
    }
    
    // update the output file where the user typed
    fout << * (L.get_top());
}


Dic::Dic(){
    ifstream fin(DATABASE_LOCATION.c_str());
    if(!fin)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << DATABASE_LOCATION << endl;
        exit(1);
    }
    
    int index;
    string wordOrPhrase = "true", explaination = "", str_timeAdded ="";
    time_t timeAdded;
    short familiar_index;
    
    
    while (fin.peek() != EOF)
    {
        // 0. Read index
        //        fin >> index;
        
        //1. Read key
        readOneElement(wordOrPhrase, fin, "wordOrPhrase");
        
        if (dic.find(wordOrPhrase) == 0) // Remove EOF duplicate error
        {
            //2. Read value
            readOneElement(explaination, fin, "explaination");
            
            //3. Read timeAdded
            readOneElement(str_timeAdded, fin, "timeAdded");
            
            // 4. Read familiar index
            //            fin >> familiar_index;
            
            // get current date/time
            /**
             The function atoll in stdlib.h convert a c-string to long
             long type.
             */
            timeAdded = (time_t)atoll(str_timeAdded.c_str());
            
            dic.push(wordOrPhrase, explaination, timeAdded);
        }
        
    }
    
    fin.close();
}


void Dic::userInteractive()
{
    string word = "word or a phrase", value = "n o-explaination";
    string doubleCheckIfSpellRightBuffer = "111";
    char doubleCheckIfSpellRight = '1';
    fstream fout;
    time_t now;
    
    while (1)
    {
//        cin.clear();
        // 请求一个单词，必须是正确的全拼写。
        cout << "\n***Enter key:(Enter 'q' or 'Q' to stop): ";
        getline(cin, word);
        if (word == "q" || word =="Q") break;
        
        // List member function 的返回值作为搜索结果
        Node* target = dic.find(word);
        // 如果没有找到，请求输入解释，并且加入List 和 dic file
        if (target == 0)
        {
            cout << "Not found....Enter value: \n";
            getline(cin,value,'|');
            if (value == "q" || value =="Q")
                
            {
                cin.ignore();
                continue;

            }

            now = time(0);
            dic.push(word, value, now);
            write_new_node_to_file(fout,dic);
            cout << "\"" << value  << "\" is added to the database......\n";
            cin.ignore();

        }
        // 如果找到，输出 单词 和 释义, Linux shell 输入解释的时候是红色
        else
        {
            Color::Modifier red(Color::FG_RED);
            Color::Modifier def(Color::FG_DEFAULT);
            cout  << "\n" << red << target->get_value()<< def << "\n";
            // print the time added
            Date date = target->get_date();
            cout << "Time Added:" << date.year2digits << "\\" << date.month << "\\" << date.day_of_month << " " << date.hour << ":" << date.minutes << ":" << date.seconds << "星期" << date.day_of_week << endl;
            
            
        }
    }
    
    fout.close();

}


void Dic::copyDatabaseToArg(const char arg[]) const
{
    ofstream fout;
    fout.open(arg);
    if (!fout)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << DATABASE_LOCATION << endl;
        exit(1);
    }
    
    fout << dic ;
    fout.close();
}



