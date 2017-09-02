#include "Dic.hpp"
#include "test/fstreamFile.hpp"

const string DATABASE_LOCATION = "/Applications/selfmade-product/dic-master/data/dic.md";

const char HTML_OUT_LOCATION [] = "/Applications/selfmade-product/dic-master/data/dic.html";



int main (void)
{
    // Check compatibility of the InputFile
    fstreamFile checkFile(DATABASE_LOCATION);
    checkFile.report();
    
    
    // G e e k l e program core.
    Dic myDictionary(DATABASE_LOCATION);
    myDictionary.userInteractive();
    myDictionary.copyDatabaseToArg(DATABASE_LOCATION.c_str());
    myDictionary.reportHtmlFile(HTML_OUT_LOCATION);
    cout << "program is done....." << endl;

}







