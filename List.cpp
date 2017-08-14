

#include "List.h"


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


void List::pushFromNode(const int& i, const string& k, const string& v, const time_t& t, const Date& d, const short& familiar_Index)
{
    Node* temp = new Node(i, k, v, t, d,familiar_Index, top);
    
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

bool List::remove(const string& key)
{
    if(! find(key))
    {
        cerr << key << "is not in the List" << endl;
        return false;
    }
    
    Node* temp1 = top;
    Node* temp2;
    if (top->get_key() == key)
    {
        top = top ->  get_next();
        delete temp1;
        return true;
    }
    
    while(temp1->get_next()->get_key() != key)
    {
        temp1 = temp1->get_next();
    }
    temp2 = temp1 -> get_next();
    temp1 -> set_next(temp2->get_next());
    delete temp2;
    return true;
}


Node*	List::find(const string& item) const
// very similar to the prstring function
{
    Node* temp = top;
    while (temp != 0)
    {
        if (temp->get_key() == item)
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
// very similar to the prstring function
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


