

#ifndef List_h
#define List_h

#include "Node.h"


class List
{
    Node* top;
    
public:
    List();
    ~List();
    /**
     *****************************************************************
     Adding a new node to the list.
     */
    void push(string item ,string c, time_t t );
    void pushFromFile(const int& i, const string& k, const string& v, const time_t& t, const short& familiar_index);

    void pushFromNode(const int& i, const string& k, const string& v, const time_t& t, const Date& d,const short& familiar_Index);
    void add_value(string value, Node* target);
    string pop();
    Node* get_top() const;
    /*
     Remove node based on the key value.
     */
    bool remove(const string& key);
    Node* find(const string& item) const;
    Node* find(const int& index) const;
    bool remove_Last();
    /*****************************************************************
     Review List
     */
    void reviewList(const short& num)
    {
        Node* temp = top;
        string key;
        int randNum;
        srand (time(NULL));
        
        
        cout << Node::numOfNodes << endl;
        
        for (int i = 0 ; i< num; i++)
        {
            randNum = rand()%(Node::numOfNodes - 1) + 1;
            
            cout << "Random max: " << Node::numOfNodes -1
            << "random index: " << randNum << endl;
            
            temp = find(randNum);
            
            if (temp == 0)
            {
                cout << "List.h::revieList has bug: (temp is a \" bad \" address!!! The randNum is not valid! Ex: 0, or > Node::numofNodes " << endl;
                exit(2);
            }
            
            temp->reviewNode();
            
            if (temp->get_familiar_index() == 21)
            {
                remove(key);
                if (find(key)== 0)
                {
                    cout << "Node with key: " << key << " has been deleted. " << endl;
                }
                
            }
            temp = temp->get_next();

        }
        
    }
};

std::ostream& operator << (std::ostream&, const List&);

#endif /* List_h */
