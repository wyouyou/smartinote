#include "main/Dic.hpp"
#include "test/fstreamFile.hpp"


int main (void)
{
    // Check compatibility of the InputFile
    fstreamFile checkFile(CONST::DATABASE_LOCATION);
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
    cout << "program is done....." << endl;

}







