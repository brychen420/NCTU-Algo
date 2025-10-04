#include <iostream>
using namespace std;

class List;

class Node
{
private:
    int data;
    Node *next;

public:
    Node() : data(0), next(NULL){};
    Node(int n) : data(n), next(NULL){};

    friend class List;
};
class List
{
private:
    Node *head;

public:
    List() : head(NULL){};
    void Print();
    void Pushback(int data);
    void Insert(int data, int n);
    void Delete(int n);
    void Reverse();
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
        if (ins == 'b')
        {
            int data;
            cin >> data;
            l.Pushback(data);
        }
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
        if (ins == 'r')
        {
            l.Reverse();
        }
    }

    return 0;
}

void List::Print()
{
    if (head == NULL)
    {
        cout << "Empty\n";
    }
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
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
}
void List::Insert(int data, int n)
{
    Node *Newnode = new Node(data);
    if (n == 1)
    {
        Newnode->next = head;
        head = Newnode;
        return;
    }
    Node *temp = head;
    for (int i = 0; i < n - 2; i++)
    {
        temp = temp->next;
    }
    Newnode->next = temp->next;
    temp->next = Newnode;
}
void List::Delete(int n)
{
    Node *temp = head;
    for (int i = 0; i < n - 2; i++)
    {
        temp = temp->next;
    }
    Node *temp2 = temp->next;
    temp->next = temp2->next;
    delete temp2;
}
void List::Reverse()
{
    Node *current = head;
    Node *previous = NULL;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}