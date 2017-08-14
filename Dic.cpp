
//  Dic.cpp
//  dic
//
//  Created by Jaye Wang on 8/9/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "Dic.hpp"


const string DATABASE_LOCATION = "/Applications/selfmade-product/dic-master/data/dic.md";


Dic::Dic(){
    
    ifstream fin(DATABASE_LOCATION.c_str());
    
    if(!fin)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << DATABASE_LOCATION << endl;
        exit(1);
    }
    
    int index = -1;
    string key = "defalut-key", value = "default-value", str_timeAdded ="default-timeAddedStr";
    time_t timeAdded = -1;
    short familiar_index = -1;
    
    /*
     2     lap|   in someone's lap: as someone's responsibility|    1502067091|    0
     */
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
            
            // get current date/time
            /**
             The function atoll in stdlib.h convert a c-string to long
             long type.
             */
            timeAdded = (time_t)atoll(str_timeAdded.c_str());
            
            dic.pushFromFile( index, key, value, timeAdded, familiar_index);
        }
        
    }
    
    fin.close();
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



void Dic::userInteractive()
{
    string word = "word or a phrase", value = "no-explaination";
    fstream fout;
    time_t now;
    
    while (1)
    {
        cin.ignore();
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
            getline(cin,value);
            if (value == "q" || value =="Q")
            {
                cin.ignore();
                continue;
            }
            now = time(0);
            dic.push(word, value, now);
            write_new_node_to_file(fout,dic);
            cout << "\"" << value  << "\" is added to the database......\n";
        }
        
        else target->printNodeInfo();
    }
    fout.close();

}



void Dic::copyDatabaseToArg(const char arg[]) const
{
    // Creat a copy of dic to deal with LIFO issue
    List dicCopy;
    
    Node* temp = dic.get_top();
    while (temp != 0)
    {

        dicCopy.pushFromNode(temp->get_index(),temp->get_key(), temp->get_value(), temp->get_timeAdded(), temp->get_date(),temp->get_familiar_index());
        temp = temp->get_next();
    }
    
    
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
}



