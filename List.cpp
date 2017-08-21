/*
 * File: List.cpp
 *
 */

#include "List.h"

const char HTML_OUT_LOCATION [] = "/Applications/selfmade-product/dic-master/data/dic.html";

List::List():top(0){
    
}

List::~List()
{
    Node*temp = top;
    while (temp != nullptr)
    {
        top = top->get_next();
        delete temp;
        temp = top;
    }
}

void List::deleteNodeIfFamiliarEnough(Node* theNode)
{
    if (theNode->get_familiar_index() >=  21)
    {
        remove(theNode->get_key());
        if (find(theNode->get_key())== 0)
            cout << "Node with key: " << theNode->get_key()
            << " has been deleted. " << endl;
    }
}


void List::push(string item, string c, time_t t)
{
    Node* temp = new Node(item, c, top, t);
    
    top = temp;
}

void List::pushFromFile(const int& i, const string& k, const string& v, const time_t& t, const short& familiar_Index)
{
    Node* temp = new Node(i, k, v, t,familiar_Index, top);
    
    top = temp;
}


void List::pushFromNode(const int& i, const string& k, const string& v, const time_t& t, const Date& d, const short& familiar_Index,const double& famPercent)
{
    Node* temp = new Node(i, k, v, t, d,familiar_Index,famPercent, top);
    
    top = temp;

}

void List::add_value(string value, Node* target)
{
    target->add_value(value);
}

string List::pop()
{
    Node* temp = top;
    top = top->get_next();
    string value = temp->get_key();
    delete temp;
    return value;
}

Node* List::get_top() const
{
    return top;
}



/**
 * If there is no node with same key as arg
 *      prompt message and return false.
 * If there is
 *      remove the node
        keepIndexContinous
 */
bool List::remove(const string& key)
{
    if(!find(key))
    {
        cerr << key << "is not in the List" << endl;
        return false;
    }
    
    Node* temp1 = top;
    Node* temp2;
    if (top->get_key() == key)
    {
        top = top -> get_next();
        delete temp1;
        return true;
    }
    
    while(temp1->get_next()->get_key() != key)
    {
        temp1 = temp1->get_next();
    }
    temp2 = temp1 -> get_next();
    temp1 -> set_next(temp2->get_next());
    
    keepIndexContinous(temp1->get_next());
    
    delete temp2;
    return true;
}

/**
 * If there is no node with same index as arg
 *      prompt message and return false.
 * If there is
 *      remove the node
        keepIndexContinous
 */
bool List::remove(const int& index)
{
    if(!find(index))
    {
        cerr << index << "is not in the List" << endl;
        return false;
    }
    
    Node* temp1 = top;
    Node* temp2;
    if (top->get_index() == index)
    {
        top = top -> get_next();
        delete temp1;
        return true;
    }
    
    while(temp1->get_next()->get_index() != index)
    {
        temp1 = temp1->get_next();
    }
    temp2 = temp1 -> get_next();
    temp1 -> set_next(temp2->get_next());
    
    keepIndexContinous(temp1->get_next());
    
    delete temp2;
    return true;
}
/**
 * Starting poisition at top.
 * decrement Index from the top location until the ptr position.
 *
 */
void List::keepIndexContinous(Node* ptr)
{

    Node* start = top;
    while (start != ptr)
    {
        start->decrementIndex();
        start = start->get_next();
    }
}





Node* List::find(const string& key) const
{
    Node* temp = top;
    while (temp != 0)
    {
        if (temp->get_key() == key)
        {
            if (temp->get_value().size() < 1) // if there is no value definition, means the targer need to be updated, also means not found
            {
                return 0;
            }
            return temp;

        }
        temp = temp -> get_next();
    }
    return 0;
}


Node* List::find(const int& index) const
{
    Node* temp = top;
    while (temp != 0)
    {
        if (temp->get_index() == index)
        {
            return temp;
        }
        temp = temp -> get_next();
    }
    return 0;
}

bool List::remove_Last()
{
    //First, test if the Linked List is empty.
    if (top == NULL) return 0;
    
    if (top -> get_next()==NULL)
    {
        delete top;
        top = 0;
        return true;
    }
    
    Node* temp = top;
    
    while(temp->get_next()->get_next()!= NULL )
    {
        temp =  temp->get_next();
    }
    delete temp->get_next();
    temp->set_next(0);
    
    return true;
}


void List::reviewListRandomly(const short& num)
{
    Node* temp = top;
    int randomIndex;
    srand (time(NULL));
    
    for (int i = 0 ; i< num; i++)
    {
        randomIndex = rand()%(Node::numOfNodes - 1) + 1;
        cout << "Random max: " << Node::numOfNodes -1
        << "random index: " << randomIndex << endl;
        
        temp = find(randomIndex);
        
        if (temp == 0)
        {
            cout << "List.h::revieList has bug: (temp is a \" bad \" address!!! The randNum is not valid! Ex: 0, or > Node::numofNodes " << endl;
            exit(2);
        }
        
        temp->reviewNode();
        deleteNodeIfFamiliarEnough(temp);
        temp = temp->get_next();
    }
    
}

void List::reviewListScientificly()
{
    
}

ostream& operator<< (ostream& out , const List& object)
{
    Node* temp = object.get_top();
    while (temp != 0)
    {
        out << *temp << ' ';
        
        temp = temp->get_next();
        
    }
    
    return out;
}

void List::report2HtmlFile() const
{
    ofstream fout;
    fout.open(HTML_OUT_LOCATION);
    if (!fout)
    {
        printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
        cerr << "Unable to open: " << HTML_OUT_LOCATION << endl;
        exit(1);
    }
    Node::write2HtmlTableHeading(fout);

    Node* temp = this->get_top();
    while (temp!=0)
    {
        temp->report2HtmlFile(fout);

        temp = temp->get_next();
    }
    Node::write2HtmlTableTail(fout);

    
    fout.close();
    
}

