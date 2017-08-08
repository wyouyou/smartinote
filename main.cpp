#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "List.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

/**
 To do list
 ************************************************************************

 Adding Printing in FIFO manner by sorting the list.
 
 Add 艾宾浩斯记忆曲线记忆模式
    If the familiar index = 21, delete the node, and fix side effects.
 
 ************************************************************************
 Add 枚举类型【Unix,
    在请求输入Key之前，请求“Enter the corresponding numbers to corresponding 
 tag type
                                        Key         Value
        1. English_Dic                  单词|词组      解释
        2. Film_Critic                  电影名字       影评
        3. Diary                        日期          日记
        4. Daliy_Sentence               问题或者标题    一句话
 
        5. To_Do_Lists                  宏观目标     具体步骤1.2.3.4.5
 ************************************************************************
 利用枚举输入 random 色彩
 
 
 */

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


void ClearScreen()
{
    cout << string( 100, '\n' );
}


using namespace std;

const string OUTPUT_PATH = "/Applications/selfmade-product/dic-master/data/dic.md";
string inputfile_num;

const int FILE_NUMBER = 999;

void read_dic2List(List& l);
void create_dic(List&L);
void user_interactive(List& L);
void creat_variable_number_of_files(List &L);
void read_the_elment(string& element, ifstream& fin, const string& tag = "element");
void write_new_node_to_file(fstream& fout, const List& L, const string& fileName = "/Applications/selfmade-product/dic-master/data/dic.md" );

int main (void)
{
    List my_dic;
    read_dic2List(my_dic);
    user_interactive(my_dic);
}

/**
 ***********************************************************************
 A infinite loop until you enter stop.
 
 Type a word to search the explanation definition. If there is no explanation definition, type one to it.
 If there is one, it will show up on the screen.
 
 If the word is misspelled or the word not found in the List my_dic, not found prompt will show up on the screen.
 
 */

void user_interactive(List& L)
{
    string word = "word or a phrase", explaination = "no-explaination";
    string doubleCheckIfSpellRightBuffer = "111";
    char doubleCheckIfSpellRight = '1';
    fstream fout;
    time_t now;

    while (1)
    {
        // 请求一个单词，必须是正确的全拼写。
        cout << "\n\n***Enter a word or phrase ('Enter' key is the delimeter, Enter 'q' or 'Q' to stop): ";
        getline(cin, word);
        if (word == "q" || word =="Q") break;
        
        // List member function 的返回值作为搜索结果
        Node* target = L.find(word);
        // 如果没有找到，请求输入解释，并且加入List 和 dic file
        if (target == 0)
        {
            cout << "\n.......Not found. 重新检查是否输入正确的Key, 输入0如果认为你输入的单词有错误 ('Enter' key is the delimeter）: ";
            getline(cin, doubleCheckIfSpellRightBuffer);
            doubleCheckIfSpellRight = doubleCheckIfSpellRightBuffer[0];
            cout << "\n";
        

           if (doubleCheckIfSpellRight != '0')
            {
                cout << "\nAdd it to the libray now, " << "Enter explaination: ";
                getline(cin,explaination);
                
                cout << "The explanation you entered is : " << "\"" << explaination  << "\"";


                if (explaination == "q" || explaination =="Q") break;
                
                now = time(0);
                L.push(word, explaination, now);
                write_new_node_to_file(fout,L); // Has default third arg for fileName
            }
                   }
        // 如果找到，输出 单词 和 释义, Linux shell 输入解释的时候是红色
        else
        {
            Color::Modifier red(Color::FG_RED);
            Color::Modifier def(Color::FG_DEFAULT);
            cout << "\n\n"  <<  word << ": \n" <<  red << target->get_value()<< def << "\n";
            // print the time added
            Date date = target->get_date();
            cout << "Time Added:" << date.year2digits << "\\" << date.month << "\\" << date.day_of_month << " " << date.hour << ":" << date.minutes << ":" << date.seconds << "星期" << date.day_of_week << endl;
            
            
        }
        
        fout.close();
        
  
        
// 备份
        fout.open("/Applications/selfmade-product/dic-master/data/dicCopy.md");
        if (!fout)
        {
            cerr << "Unable open file : ";
            exit(6);
        }
        
        fout << L ;
        fout.close();
        
        
    }
}



/**
 ***********************************************************************
 Post-condition: the element get modified.
 
 ***********************************************************************
 The third parameter:
    Is used to debug (printing out) purpose.
 
 ***********************************************************************
 Debug code (printing out)
 cout << "The " << tag  << " is : " << "\"" << element  << "\"" << endl;
 
 ***********************************************************************
 Input format:
 单词 或 词组|  解释|
 */
void read_the_element(string& element, ifstream& fin, const string& tag)
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
}


/**
 ************************************************************************
 Pre condition: l is most likey a empity list to be insert nodes.
 Post condition: l will have as many nodes as the number of nodes in the
 */
void read_dic2List(List& l)
{
    ifstream fin(OUTPUT_PATH.c_str());
    if(!fin)
    {
        cerr << "Unable open file: " << OUTPUT_PATH << endl;
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
        read_the_element(wordOrPhrase, fin, "wordOrPhrase");
        
        if (l.find(wordOrPhrase) == 0) // Remove EOF duplicate error
        {
            //2. Read value
            read_the_element(explaination, fin, "explaination");
            
            //3. Read timeAdded
            read_the_element(str_timeAdded, fin, "timeAdded");
            
            // 4. Read familiar index
//            fin >> familiar_index;
            
            // get current date/time
            /**
             The function atoll in stdlib.h convert a c-string to long 
             long type.
             */
            timeAdded = (time_t)atoll(str_timeAdded.c_str());
            
            l.push(wordOrPhrase, explaination, timeAdded);
        }
        
    }

    fin.close();
    
}


/**
 ************************************************************************
 Append mode. If the file already exists, its contents are preserved and
 all output is written to the end of the file. By default, this flag
 causes the file to be created if it does not exist.
 */
void write_new_node_to_file(fstream& fout, const List& L, const string& fileName)
{

    
    fout.open(OUTPUT_PATH.c_str(),ios_base::app);
    
    if(!fout)
    {
        cerr << "Invalid directory: " << OUTPUT_PATH;
    }
    
    // update the output file where the user typed
    fout << * (L.get_top());
}


/**
 ************************************************************************
 Precondition: Nothing
 Postcondition: create variable number of outfile files.
 
 Location: depending on file_path
 extension: depending on file_extension
 */
void creat_variable_number_of_files(List &L)
{
    string iterator_file_name;
    ofstream fout;
    string file_path = "";
    string file_extension = ".txt";
    
    
    
    for (int i = 0; i < FILE_NUMBER; i++)
    {
        //  update the output file num by using to_string to convert int to string so that the iterator_input is updated.
        inputfile_num  = to_string(i);
        iterator_file_name = file_path + inputfile_num + file_extension;
        
        fout.open(iterator_file_name.c_str());
        if(!fout)
        {
            cerr << "Unable to open : " << iterator_file_name << endl;
            cerr << "File num 0 to " << i -1 << " have been processed." << endl;
            break;
        }
        //  clear the iterator_file_name otherwise, the next updated inputfile would suprise you!!!
        fout.close();
        iterator_file_name.clear();
        
    }
    
}





