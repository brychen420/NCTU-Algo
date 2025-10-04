#include <iostream>
using namespace std;

class List;

class Node
{
private:
    int data;
    Node *next;
    Node *prev;

public:
    Node() : data(0), next(NULL), prev(NULL){};
    Node(int n) : data(n), next(NULL), prev(NULL){};

    friend class List;
};

class List
{
private:
    Node *head;

public:
    List() : head(NULL){};
    void Print();
    void RePrint();
    void Pushback(int data);
    void PushFront(int data);
    void Insert(int data, int n);
    void Delete(int n);
};

int main()
{
    List l;
    char ins;
    while (cin >> ins)
    {
        if (ins == 'p')
        {
            l.Print();
        }
        if (ins == 'q')
        {
            l.RePrint();
        }
        if (ins == 'b')
        {
            int data;
            cin >> data;
            l.Pushback(data);
        }
        if (ins == 'f')
        {
            int data;
            cin >> data;
            l.PushFront(data);
        }
        /*
        if (ins == 'i')
        {
            int data, n;
            cin >> data >> n;
            l.Insert(data, n);
        }
        if (ins == 'd')
        {
            int n;
            cin >> n;
            l.Delete(n);
        }
        return 0;
        */
    }
}

void List::Print()
{
    if (head == NULL)
    {
        cout << "Empty";
    }
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}


void List::RePrint()
{
    if (head == NULL)
    {
        cout << "Empty\n";
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << "\n";
}

void List::Pushback(int data)
{
    Node *Newnode = new Node(data);
    if (head == NULL)
    {
        head = Newnode;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = Newnode;
    Newnode->prev = temp;
}
void List::PushFront(int data)
{
    Node *Newnode = new Node(data);
    if (head == NULL)
    {
        head = Newnode;
        return;
    }
    Newnode->next = head;
    head->prev = Newnode;
    head = Newnode;
}
void List::Insert(int data, int n){ //have not finished yet
    Node *Newnode = new Node(data);
    Node* temp = head;
    if(n == 1){
        Newnode->next = head;
        temp->prev = Newnode;
        head = Newnode;
        return;
    }
    for(int i = 1; i < n-1; i++){
        temp = temp->next;
    }
    Newnode->next = temp->next;
    Newnode->prev = temp;
    temp->next = Newnode;
    //
}