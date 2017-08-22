#include "Dic.hpp"


int main (void)
{
    
    Dic myDictionary;
    
    myDictionary.dicCore();
    myDictionary.copyDatabaseToArg("/Applications/selfmade-product/dic-master/data/dic.md");
    myDictionary.reportHtmlFile();
    cout << "program is done....." << endl;

}







