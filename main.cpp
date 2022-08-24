#include <iostream>

using namespace std;

class node
{
public:
    node(int _val = (int)NULL) : next(nullptr), exp(_val) { };
    node* next;
    int exp;
    int change(int a) { return exp = a; }
};

int main()
{
    int a;
    node* head = nullptr;
    node* tail = nullptr;
    node* newNode = nullptr;
    
    while (true)
    {
        cin >> a;
        
        if(a < 0) break;

        newNode = new node(a);

        if(head == nullptr) head = newNode;
        else                (*tail).next = newNode;

        tail = newNode;
    }

    if(head == nullptr) cout << 'x';
    else
    {
        node* cur = head;

        while(cur != nullptr)
        {
            cout << (*cur).exp << ' ';
            cur = (*cur).next;
        }
    }

    cout << endl;
}