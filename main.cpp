#include "Dic.hpp"



/**
 
 
 
 Key         Value
        1. English_Dic                  单词|词组      解释
        2. Film_Critic                  电影名字       影评
        3. Diary                        日期          日记
        4. Daliy_Sentence               问题或者标题    一句话
        5. To_Do_Lists                  宏观目标     具体步骤1.2.3.4.5
 
 *********************************************************************
 */


int main (void)
{ 
    Dic myDictionary;
    
    myDictionary.dicCore();
    
    myDictionary.copyDatabaseToArg("/Applications/selfmade-product/dic-master/data/dic.md");
    myDictionary.reportHtmlFile();
    cout << "program is done....." << endl;

}







