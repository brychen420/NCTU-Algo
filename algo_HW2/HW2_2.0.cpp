#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

class MList;
class Matrix;
class Node
{
private:
    int row;
    int col;
    int data;
    Node *next;

public:
    Node(int row, int col, int data)
    {
        this->row = row;
        this->col = col;
        this->data = data;
        next = NULL;
    }
    friend class Matrix;
    friend class MList;
};
class Matrix
{
private:
    string name;
    int rows;
    int cols;
    Node *head;
    Matrix *next;

public:
    Matrix(string name, int rows, int cols)
    {
        this->name = name;
        this->rows = rows;
        this->cols = cols;
        head = NULL;
        next = NULL;
    }
    void Print();
    void Insert(int row, int col, int data);
    void Clear();

    friend MList;
};
class MList
{
private:
    Matrix *Mhead;

public:
    MList() : Mhead(NULL){};
    void MPushback(string name, int rows, int cols);
    void MDelete(string name);

    void Assign(string name, int row, int col, int data);
    void Add(string name1, string name2, string name3);
    void Mult(string name1, string name2, string name3);
    void MPrint(string name);
};

int main()
{
    MList ML;
    string func;
    while (input >> func)
    {
        if (func == "Init")
        {
            string name;
            int rows;
            int cols;
            input >> name >> rows >> cols;
            ML.MPushback(name, rows, cols);
        }
        else if (func == "Assign")
        {
            string name;
            int row;
            int col;
            int data;
            input >> name >> row >> col >> data;
            ML.Assign(name, row, col, data);
        }
        else if (func == "Add")
        {
            string name1;
            string name2;
            string name3;
            input >> name1 >> name2 >> name3;
            ML.Add(name1, name2, name3);
        }
        else if (func == "Mult")
        {
            string name1;
            string name2;
            string name3;
            input >> name1 >> name2 >> name3;
            ML.Mult(name1, name2, name3);
        }
        else if (func == "Print")
        {
            string name;
            input >> name;
            ML.MPrint(name);
        }
        else if (func == "Delete")
        {
            string name;
            input >> name;
            ML.MDelete(name);
        }
    }
    output.close();
    return 0;
}

void Matrix::Print()
{
    Node *temp = head;
    while (temp != NULL)
    {   
        if(temp->data != 0){
            output << "(" << temp->row << " ";
            output << temp->col << " ";
            output << temp->data << ") "; 
        }
        temp = temp->next;
    }
    output << "\n";
}
void MList::MPrint(string name)
{
    Matrix *Mtemp = Mhead;
    while (Mtemp->name != name)
        Mtemp = Mtemp->next;
    Mtemp->Print();
}
void MList::MPushback(string name, int rows, int cols)
{
    Matrix *NewMatix = new Matrix(name, rows, cols);
    if (Mhead == NULL)
    {
        Mhead = NewMatix;
        return;
    }
    Matrix *temp = Mhead;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = NewMatix;
}
void Matrix::Insert(int row, int col, int data)
{   
    // check if the position is occupied or not
    Node *check = head;
    while (check != NULL)
    {
        if (check->row == row and check->col == col)
        {   
            check->data += data;
            return;
        }
        check = check->next;
    }
    Node *Newnode = new Node(row, col, data);
    // if matrix is empty
    if (head == NULL)
    {
        head = Newnode;
        return;
    }
    // if the newnode should be insert at first
    Node *temp = head;
    if (temp->row > Newnode->row or (temp->row == Newnode->row and temp->col > Newnode->col))
    {
        Newnode->next = head;
        head = Newnode;
        return;
    }
    while (temp->next != NULL)
    {   
        if (temp->row < Newnode->row or (temp->row == Newnode->row and temp->col < Newnode->col))
        {
            if (temp->next->row > Newnode->row or (temp->next->row == Newnode->row and temp->next->col > Newnode->col))
            {
                break;
            }
        }
        temp = temp->next;
    }
    Newnode->next = temp->next;
    temp->next = Newnode;
}
void MList::Assign(string name, int row, int col, int data)
{
    Matrix *Mtemp = Mhead;
    while (Mtemp->name != name)
        Mtemp = Mtemp->next;
    Mtemp->Insert(row, col, data);
}
void MList::Add(string name1, string name2, string name3)
{
    Matrix *Mtemp1 = Mhead;
    while (Mtemp1->name != name1)
        Mtemp1 = Mtemp1->next;
    Matrix *Mtemp2 = Mhead;
    while (Mtemp2->name != name2)
        Mtemp2 = Mtemp2->next;
    Matrix *Mtemp3 = Mhead;
    while (Mtemp3->name != name3)
        Mtemp3 = Mtemp3->next;

    Node *temp1 = Mtemp1->head;
    Node *temp2 = Mtemp2->head;

    while (temp1 != NULL)
    {
        Mtemp3->Insert(temp1->row, temp1->col, temp1->data);
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        Mtemp3->Insert(temp2->row, temp2->col, temp2->data);
        temp2 = temp2->next;
    }
}
void MList::Mult(string name1, string name2, string name3)
{
    Matrix *Mtemp1 = Mhead;
    while (Mtemp1->name != name1)
        Mtemp1 = Mtemp1->next;
    Matrix *Mtemp2 = Mhead;
    while (Mtemp2->name != name2)
        Mtemp2 = Mtemp2->next;
    Matrix *Mtemp3 = Mhead;
    while (Mtemp3->name != name3)
        Mtemp3 = Mtemp3->next;

    Node *temp1 = Mtemp1->head;
    while (temp1 != NULL)
    {
        Node *temp2 = Mtemp2->head;
        while (temp2 != NULL)
        {
            if (temp1->col == temp2->row)
            {   
                Mtemp3->Insert(temp1->row, temp2->col, (temp1->data) * (temp2->data));
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}
void Matrix::Clear()
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
void MList::MDelete(string name)
{
    Matrix *Mtemp = Mhead;
    if (Mtemp->name == name)
    {
        Mhead = Mtemp->next;
        Mtemp->Clear();
        delete Mtemp;
        return;
    }
    while (Mtemp->next->name != name)
    {
        Mtemp = Mtemp->next;
    }
    Matrix *Mtemp2 = Mtemp->next;
    Mtemp2->Clear();
    Mtemp->next = Mtemp2->next;
    delete Mtemp2;
}