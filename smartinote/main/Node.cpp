/**
 * File: Node.cpp
 */

#include "Node.h"

int Node::numOfNodes = 0;

void Node::decrementNumOfNodes() { numOfNodes--;}

/**
 * creating/adding node...
 * key + value + timeAdded are intialized from the user input.
 *
 * index = the current incremented numOfNodes.
 * all new node created from the user has a familiar_index = 0 by default.
 * date is intialized based on timeAdded (the time when the node was born)
 * familiar_percent is intialized based on familiar_index, 0 in this case.
 */
Node::Node(string theKey, string theValue, Node*n, time_t t ): key(theKey), value(theValue),next(n), timeAdded(t)
{
    index = ++numOfNodes;
    familiar_index = 0;
    init_date();
    familiar_percent = 0;
    
    // tag part
//    tag = Tag(theInfo);
    
}

/**
 * reading node from file...
 * index + key + value + timeAdded + familiar_index are intialized from
 * the input file corresponding data filed.
 *
 * numOfNodes is incremented whenever a node is read from file.
 * date is intialized based on timeAdded read from file.
 * familiar_percent is intialized based on familiar_index.
 */
Node::Node(const int& i, const string& k, const string& v, const time_t& t,const short& familiar_Index, Node* n): index(i), key(k),value(v),timeAdded(t),familiar_index(familiar_Index),next(n)
{
    ++numOfNodes;
    init_date();
    familiar_percent = 100*(familiar_index/21.);
}

/**
 * copying/cloning node form another node...
 * every data member is intialized by the args.
 */
Node::Node(const int& i, const string& k, const string& v, const time_t& t, const Date& d ,const short& familiar_Index, const double& famPercent, Node* n): index(i), key(k),value(v),timeAdded(t), date(d),familiar_index(familiar_Index),familiar_percent(famPercent), next(n)
{
}

void Node::init_date()
{
    tm* timeInfo  = localtime(&timeAdded);
    date.year2digits = timeInfo->tm_year % 100;
    date.year4digits = 2000 + date.year2digits;
    date.month = timeInfo->tm_mon + 1;
    date.day_of_month = timeInfo->tm_mday;
    date.day_of_week = timeInfo->tm_wday;
    date.day_in_the_year = timeInfo->tm_yday;
    date.hour = timeInfo->tm_hour;
    date.minutes = timeInfo->tm_min;
    date.seconds = timeInfo->tm_sec;
}

std::string Node::review()
{
    std::string reviewResult = "reviewed";
    string remember;
    do
    {
    string prompt = "\n\n认识: " + this->key + " 吗？Press 'Y' or 'y', press 'N' or 'n' 如果不认识, 'D' or 'd' to delete:";
    //    simpleIO::UnixIO::printInColor(" ☞"
    
    simpleIO::UnixIO::printInColor("\n ☞ ", Color::FG_GREEN);
    
    remember = simpleIO::String::getLine(this->key+ ": ");
    
    if (remember[0] == 'Y'  or remember[0] == 'y')
    {
        familiar_index++;
        printNodeInfo(CONST::PRINT_WIDTH, Color::FG_PINK);
        
    }
    else if (remember[0] == 'N' or remember[0] == 'n')
    {
        familiar_index--;
        printNodeInfo(CONST::PRINT_WIDTH, Color::FG_RED);
    }
    else if (remember == "clear" ) clear();
    else if (remember == "rm last") return remember;
    else if (remember == "rm this") return remember;
    else if (remember == "q") return remember;
    else if (simpleIO::stdIO::isEnterKeyPressed(remember))
    {
        clear();
        continue;
    }
    else if (remember.substr(0,3) == "rst" || remember.substr(0,3) == "app")
        return remember;
    else simpleIO::String::dispalyFatalMessage("command");
        
    }while (simpleIO::stdIO::isEnterKeyPressed(remember));
    
    return reviewResult;
}



int Node::get_index() const
{
    return index;
}

Date Node::get_date() const
{
    return date;
}
string Node::get_key() const
{
    return key;
}

string Node::get_value() const
{
    return value;
}

Node* Node::get_next() const
{
    return next;
}

time_t Node::get_timeAdded() const
{
    return timeAdded;
}

short Node::get_familiar_index() const
{
    return familiar_index;
}

double Node::get_familiar_percent() const
{
    return familiar_percent;
}

void Node::set_next(Node *ptr)
{
    next = ptr;
}
bool Node::set_value(const string& theValue)
{
    if (theValue != "")
    {
        value = theValue;
        return true;
    }
    
    return false;
}
bool Node::append_value(const string& toBeAppend)
{
    if (toBeAppend != "")
    {
        value += toBeAppend;
        return true;
    }
    return false;

}

void Node::valueUpdating(const string& newStuff,
                            const string& choice)
{
    // reset
    if (choice == "rst")
        this->set_value(newStuff);
    // append
    if (choice == "app")
        this->append_value(newStuff);
    else
        std::cout << "semantic issue: " << __LINE__ << __FILE__ <<endl;
    
    string message = "The new value now is : ";
    simpleIO::UnixIO::displayMessage(message);
    cout << endl;
    this->printNodeInfo(CONST::PRINT_WIDTH, Color::FG_PINK);
    
}



void Node::add_value(string value)
{
    value = value + ", " + value;
}

void Node::incre_familiar_index()
{
    ++familiar_index;
}

void Node::decre_familiar_index()
{
    --familiar_index;
}

void Node::incrementIndex()
{
    index++;
}

void Node::decrementIndex()
{
    index--;
}

void Node::printIndexInfo() const
{
    cout << key << " is the " << index << " word in the dic.md.\n";
}
void Node::printTimeAdded() const
{
    cout << "Time Added:" << date.year2digits << "\\" << date.month << "\\" << date.day_of_month << " " << date.hour << ":" << date.minutes << ":" << date.seconds << "星期" << date.day_of_week << endl;
    
}
void Node::printFamilarIndexInfo() const
{
    
    if (familiar_index < 7)
    {
        cout << "Notice! this word is a stranger to you!";
    }
    else if (familiar_index > 7 && familiar_index < 14)
    {
        cout << "Good! this word is a acquaintance to you!";
    }
    else if (familiar_index > 14)
    {
        cout << "Great! this word is gonna be your friend!";
    }
    cout << familiar_index << "/21:" <<  familiar_percent << "% familiar.\n";
    
}

/*
 *
 */
void Node::printNodeInfo(const int& width, Color::Code pCode) const
{

    std::string valueCopy = value;
    
    //    size_t pos = copy.find("，");
    //    cout << "sizeOf ，：" << sizeof("，");
    //    cout << "sizeOf ，：" << sizeof(",");
    //    cout << "sizeOf ，：" << sizeof("字");
    
    // Todo 汉字的 adjustment widht issue
    
    /*
     * #9 print value in ordered list based delimiter '#'
     */
    
    vector<string> tokens = simpleIO::String::getTokens(valueCopy, "#");
    
    for (unsigned short i = 0; i < tokens.size(); i++)
    {
//        std::cout << tokens.at(i) << endl;
        Color::Code printColor;

        
        if ((i +1)%2 != 0)
            printColor = pCode;
        else
            printColor = Color::FG_DEFAULT;
        
        
        
        std::string intial = "   - ";
        simpleIO::UnixIO::printInColor(intial, Color::FG_LIGHT_Cyan);
        simpleIO::UnixIO::printInColor((int)intial.size(), tokens.at(i), width,printColor);
        cout << endl;
    }
    
    
}


void Node::report2HtmlFile(ofstream& fout) const
{
    write2Html1RowOfTb(fout);
}

void Node::write2HtmlTableHeading(ofstream& fout)
{
    fout << "<!DOCTYPE html>\n" << "<html>\n" << "<head>\n" << "<style>\n"
    << "table \n{\tfont-family: arial, sans-serif;\n\tborder-collapse: collapse;\n\twidth: 100%;\n}" << "\n\ntd, th \n{\nborder: 1px solid #dddddd;text-align: left;padding: 8px;\n}\n\n" << "tr:nth-child(even) \n{\nbackground-color: #dddddd;\n}\n\n</style>\n</head>\n<body>\n<table>\n" << endl
    << "\t<tr>\n"
    << "\t\t<th>" << "编号" << "</th>\n"
    << "\t\t<th>" << "单词" << "</th>\n"
    << "\t\t<th>" << "定义" << "</th>\n"
    << "\t\t<th>" << "熟悉指数" << "</th>\n"
    << "\t\t<th>" << "熟悉比例" << "</th>\n"
    << "\t\t<th>" << "诞生时间" << "</th>\n"
    
    << "\t</tr>\n";
    
    
}

void Node::write2Html1RowOfTb(ofstream& fout) const
{
    fout<< "\t<tr>\n"
    << "\t\t<td width=\"8%\">" << index << "</td>\n"
    << "\t\t<td width=\"15%\">" << key << "</td>\n"
    << "\t\t<td width=\"53%\">" << value << "</td>\n"
    << "\t\t<td width=\"8%\">" << familiar_index << "</td>\n"
    << "\t\t<td width=\"8%\">" << familiar_percent << "</td>\n"
    << "\t\t<td width=\"8%\">" << date.month << ":" << date.day_of_month << ":" << date.year2digits << "</td>\n"
    << "\t</tr>\n";
    
}

void Node::write2HtmlTableTail(ofstream& fout)
{
    fout << "</table>\n</body>\n</html>\n" << endl;
}

bool Node::isBornedToday() const
{
    time_t currentTime = time(0);
    Date now;
    tm* timeInfo  = localtime(&currentTime);
    now.set_Date(timeInfo);
    
    
    
    if (this->get_date().year4digits == now.year4digits
        && this->get_date().day_in_the_year == now.day_in_the_year)
        return true;
    else
        return 0;
}

bool Node::is124711DaysAgo() const
{
    time_t currentTime = time(0);
    Date now;
    tm* timeInfo  = localtime(&currentTime);
    now.set_Date(timeInfo);
    if (this->get_date().year4digits != now.year4digits)
        return false;
    
    int dayDiff = now.day_in_the_year - this->get_date().day_in_the_year;
    int scentificDayDiff[] = {1, 2, 4 , 7, 11, 16};
    
    // get array lengeth
    int len = sizeof(scentificDayDiff) / sizeof(int);
    
    //    cout << "dayDiff:" << dayDiff << endl;
    
    for (int i = 0; i < len; i++)
    {
        if (dayDiff == scentificDayDiff[i])
            return true;
    }
    return false;
}


ostream& operator<< (ostream& out, const Node& obj)
{
    
    //    2     踏平坎坷成大道|   Uneven roads are trodden down|    1503269819|    1
    out << obj.get_index() << "     "
    << obj.get_key()<< "|" << "   "
    << obj.get_value() << "|"  << "    "
    << obj.get_timeAdded() << "|" << "    "
    << obj.get_familiar_index() <<  endl << endl;
    
//    
//    // add vector tag data member
//    out << obj.get_index() << "     "
//    << obj.get_key()<< "|" << "   "
//    << obj.get_value() << "|"  << "    "
//    << obj.get_timeAdded() << "|" << "    "
//    << obj.get_familiar_index();
//    
//    // to to: is it possible overload insertion operator for vector?
//    
    
//    out <<  endl << endl;
    
    return out;
}



