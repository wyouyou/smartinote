#include "Smartinote.hpp"
#include "test/FstreamFile.hpp"


int main (void)
{
    // Check compatibility of the InputFile
    FstreamFile checkFile(CONST::DATABASE_LOCATION);
    checkFile.report();
    
    
    // G e e k l e programCore
    
    //备份数据
    Dic myDictionary(CONST::DATABASE_LOCATION);
    myDictionary.copyDatabaseToArg(CONST::DATABASE_LOCATION.c_str());

    // User interaction
    myDictionary.userInteractive();
    // update the database
    myDictionary.copyDatabaseToArg(CONST::DATABASE_LOCATION.c_str());
    // update formatted file
    myDictionary.reportHtmlFile(CONST::HTML_OUT_LOCATION);
    
    all::UnixIO::displayMessage("Program is done...");
}







