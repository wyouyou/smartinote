#include <iostream>
#include "Dic.hpp"

/**
 To do list
 
 创建一个个file arg：fileName.extension
 
 
 **********************************************************************

 Adding Printing in FIFO manner by sorting the list.
 
 Add 艾宾浩斯记忆曲线记忆模式
    If the familiar index = 21, delete the node, and fix side effects.
 D
 ********************************************************************
 Add 枚举类型【Unix,
    在请求输入Key之前，请求“Enter the corresponding numbers to corresponding 
 tag type
                                        Key         Value
        1. English_Dic                  单词|词组      解释
        2. Film_Critic                  电影名字       影评
        3. Diary                        日期          日记
        4. Daliy_Sentence               问题或者标题    一句话
 
        5. To_Do_Lists                  宏观目标     具体步骤1.2.3.4.5
 *********************************************************************
 利用枚举输入 random 色彩
 
 
 
 */


int main (void)
{
    
    
    
    Dic myDictionary;
    string choice;
    

    
    do
    {
        cout << "command tool Dic:";
        cin >> choice;
        
        if (choice == "dic")
        {
            myDictionary.userInteractive();
        }
        else if(choice == "review")
        {
            myDictionary.reviewByForgetiveCurve(2);
        }
        
        else
        {
            break;
        }
        myDictionary.copyDatabaseToArg("/Applications/selfmade-product/dic-master/data/dicCopy.md");


    } while (choice != "q" and choice != "Q");
    
    cout << "program is done....." << endl;

}






