#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Tree;
class Node
{
private:
    string key;
    string value;
    Node *parent;
    Node *left;
    Node *right;

public:
    Node(string key, string value)
    {
        this->key = key;
        this->value = value;
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    string getkey()
    {
        return key;
    }
    string getvalue()
    {
        return value;
    }
    friend Tree;
};
class Tree
{
private:
    Node *root;

public:
    Tree()
    {
        root = NULL;
    }
    void rotateLeft(Node *target);
    void rotateRight(Node *target);
    void splay(Node *target);
    bool Insert(string key, string value);
    Node *find(string target);
    Node *leftmost(Node *target);
    Node *rightmost(Node *target);
    Node *successor(Node *target);
    void erase(Node *target);
    bool Erase(string target);
    void Enum(string low, string high);
    void Clear();
};

ifstream input("input.txt");
ofstream output("output.txt");

int main()
{
    Tree t;
    string command;
    while (input >> command)
    {
        if (command == "INSERT")
        {
            string str = "";
            string key = "", value = "";
            input >> str;
            stringstream ss1(str);
            str = "";
            getline(ss1, str, ':');
            getline(ss1, key);
            input >> str;
            stringstream ss2(str);
            getline(ss2, str, ':');
            getline(ss2, value);
            if (t.Insert(key, value))
            {
                cout << "INSERT " << key << " SUCCESS!\n";
                output << "INSERT " << key << " SUCCESS!\n";
            }
            else
            {
                cout << "INSERT " << key << " FAIL!\n";
                output << "INSERT " << key << " FAIL!\n";
            }
        }
        else if (command == "FIND")
        {
            string str = "";
            string key = "";
            input >> str;
            stringstream ss(str);
            str = "";
            getline(ss, str, ':');
            getline(ss, key);
            Node *target = t.find(key);
            if (target != NULL)
            {
                cout << "FIND " << target->getkey() << ":" << target->getvalue() << "!\n";
                output << "FIND " << target->getkey() << ":" << target->getvalue() << "!\n";
            }
            else
            {
                cout << key << " NOT FOUND!\n";
                output << key << " NOT FOUND!\n";
            }
        }
        else if (command == "ERASE")
        {
            string str = "";
            string key = "";
            input >> str;
            stringstream ss(str);
            str = "";
            getline(ss, str, ':');
            getline(ss, key);
            if (t.Erase(key))
            {
                cout << "ERASE " << key << " SUCCESS!\n";
                output << "ERASE " << key << " SUCCESS!\n";
            }
            else
            {
                cout << "ERASE " << key << " FAIL!\n";
                output << "ERASE " << key << " FAIL!\n";
            }
        }
        else if (command == "ENUM")
        {
            string str = "";
            string low = "", high = "";
            input >> str;
            stringstream ss1(str);
            str = "";
            getline(ss1, str, ':');
            getline(ss1, low);
            input >> str;
            stringstream ss2(str);
            getline(ss2, str, ':');
            getline(ss2, high);
            t.Enum(low, high);
        }
        else if (command == "CLEAR")
        {
            t.Clear();
        }
    }
    output.close();
    return 0;
}
void Tree::rotateLeft(Node *target)
{   
    Node *temp = target->right;
    target->right = temp->left;

    if(temp->left != NULL){
        temp->left->parent = target;
    }
    temp->parent = target->parent;
    if(target->parent == NULL){
        root = temp;
    }
    else if(target == target->parent->left){
        target->parent->left = temp;
    }
    else{
        target->parent->right = temp;
    }
    temp->left = target;
    target->parent = temp;
}
void Tree::rotateRight(Node *target)
{
    Node *temp = target->left;
    target->left = temp->right;

    if(temp->right != NULL){
        temp->right->parent = target;
    }
    temp->parent = target->parent;
    if(target->parent == NULL){
        root = temp;
    }
    else if(target == target->parent->right){
        target->parent->right = temp;
    }
    else{
        target->parent->left = temp;
    }
    temp->right = target;
    target->parent = temp;
}
void Tree::splay(Node *target)
{
    while (target->parent != NULL)
    {
        if (target->parent->parent == NULL)
        {
            if (target->parent->left == target)
            {
                rotateRight(target->parent);
            }
            else
                rotateLeft(target->parent);
        }
        else if (target->parent->parent->right == target->parent)
        {
            if (target->parent->right == target)
            {
                rotateLeft(target->parent->parent);
                rotateLeft(target->parent);
            }
            else if (target->parent->left == target)
            {
                rotateRight(target->parent);
                rotateLeft(target->parent);
            }
        }
        else if (target->parent->parent->left == target->parent)
        {
            if (target->parent->left == target)
            {
                rotateRight(target->parent->parent);
                rotateRight(target->parent);
            }
            else if (target->parent->right == target)
            {
                rotateLeft(target->parent);
                rotateRight(target->parent);
            }
        }
    }
}
bool Tree::Insert(string key, string value)
{
    Node *NewNode = new Node(key, value);
    if (root == NULL)
    {
        root = NewNode;
        return true;
    }
    Node *temp = root;
    while (true)
    {
        if (NewNode->key == temp->key)
        {
            return false;
        }
        else if (NewNode->key > temp->key)
        {
            if (temp->right != NULL)
            {
                temp = temp->right;
            }
            else
            {
                NewNode->parent = temp;
                temp->right = NewNode;
                splay(NewNode);
                return true;
            }
        }
        else if (NewNode->key < temp->key)
        {
            if (temp->left != NULL)
            {
                temp = temp->left;
            }
            else
            {
                NewNode->parent = temp;
                temp->left = NewNode;
                splay(NewNode);
                return true;
            }
        }
    }
}
Node *Tree::find(string target)
{
    Node *temp = root;
    while (temp != NULL)
    {
        if (temp->key == target)
        {
            return temp;
        }
        else if (temp->key > target)
        {
            temp = temp->left;
        }
        else if (temp->key < target)
        {
            temp = temp->right;
        }
    }
    return temp;
}
void Tree::erase(Node *target)
{
    splay(target);
    if(target->left == NULL && target->right == NULL){
        delete target;
        root = NULL;
    }
    else if(target->left == NULL){
        target->right->parent = NULL;
        root = target->right;
        delete target;
    }
    else if(target->right == NULL){
        target->left->parent = NULL;
        root = target->left;
        delete target;
    }
    else{
        Node *temp = successor(target);
        root = temp;
        temp->right = target->right;
        temp->left = target->left;
        target->right->parent = temp;
        delete target;
    }
}
bool Tree::Erase(string target)
{
    if (find(target) != NULL)
    {
        erase(find(target));
        return true;
    }
    else
        return false;
}

Node *Tree::leftmost(Node *target)
{
    Node *temp = target;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}
Node *Tree::rightmost(Node *target)
{
    Node *temp = target;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}
Node *Tree::successor(Node *target)
{
    if (target == rightmost(root))
    {
        return NULL;
    }
    Node *temp = target;
    if (temp->right != NULL)
    {
        return leftmost(temp->right);
    }
    while (temp != root && temp == temp->parent->right)
    {
        temp = temp->parent;
    }
    return temp->parent;
}

void Tree::Enum(string low, string high)
{
    if (root == NULL)
    {
        return;
    }
    Node *temp = find(low);
    if (temp == NULL)
    {
        temp = leftmost(root);
    }
    Node *temp2 = find(high);
    if (temp2 == NULL)
    {
        temp2 = rightmost(root);
    }
    while (temp != NULL)
    {
        cout << "ENUM " << temp->key << ":" << temp->value << "\n";
        output << "ENUM " << temp->key << ":" << temp->value << "\n";
        if (temp == temp2)
            return;
        temp = successor(temp);
    }
}
void Tree::Clear()
{
    while (root != NULL)
    {   
        erase(root);
        Enum("i","k");
    }
}