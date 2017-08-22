#include "Dic.hpp"
#include "time/TimeRemainder.hpp"


int main (void)
{
    
    tr::TimeRemainder timeLeft_tillFallBegin(9,25,2017,0,0,0,1, "距离Fall quater 2017 begin");

    Dic myDictionary;
    
    myDictionary.dicCore();
    
    myDictionary.copyDatabaseToArg("/Applications/selfmade-product/dic-master/data/dic.md");
    myDictionary.reportHtmlFile();
    cout << "program is done....." << endl;

}







