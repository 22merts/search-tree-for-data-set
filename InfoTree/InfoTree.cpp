#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <list>
#include <map>
using namespace std;
struct PhoneBook
{
    string name, p_num, b_day;
    int MoneyAccount;
};

ostream& operator<<(ostream& stream, PhoneBook obj)
{
    stream << "Name : " << left << setw(13) << obj.name << " Phone number : " << left << setw(13) << obj.p_num << " Date of birth : " << left << setw(12) << obj.b_day << " money = " << obj.MoneyAccount << endl;
    return stream;
}
istream& operator>>(istream& stream, vector<PhoneBook>& obj)
{
    cout << "Enter name, phone number, date of birth and money ";
    PhoneBook a;
    stream >> a.name >> a.p_num >> a.b_day >> a.MoneyAccount;
    obj.push_back(a);
    return stream;
}
const int operator+(const int& left, const PhoneBook& right)
{
    return left + right.MoneyAccount;
}
bool operator==(const PhoneBook& obj, string month)
{
    if (obj.b_day.substr(3, 2) == month)
        return 1;
    return 0;
}
struct Node
{
    PhoneBook data;
    Node* left, * right;
};
void show(Node*& Tree)
{
    cout << Tree->data;
    if (Tree->left)
        show(Tree->left);
    if (Tree->right)
        show(Tree->right);
}
void showReverse(Node*& Tree)
{
    if (Tree->left)
        showReverse(Tree->left);
    if (Tree->right)
        showReverse(Tree->right);
    cout << Tree->data;
}
void showInner(Node*& Tree)
{
    if (Tree != NULL)
    {
        if (Tree->left)
            showInner(Tree->left);
        cout << Tree->data;
        if (Tree->right)
            showInner(Tree->right);
    }
}
void showVirt(Node*& Tree, int h)
{
    if (Tree)
    {
        showVirt(Tree->left, h + 1);
        for (int i = 0; i < h; i++)
        {
            cout << "_";
        }
        cout << Tree->data << endl;
        showVirt(Tree->right, h + 1);
    }
}
void add_node(PhoneBook newRecord, Node*& Tree)
{
    if (NULL == Tree)
    {
        Tree = new Node;
        Tree->data = newRecord;
        Tree->left = Tree->right = NULL;
    }

    if (newRecord.p_num < Tree->data.p_num)
    {
        if (Tree->left != NULL)
            add_node(newRecord, Tree->left);
        else
        {
            Tree->left = new Node;
            Tree->left->left = Tree->left->right = NULL;
            Tree->left->data = newRecord;
        }
    }

    if (newRecord.p_num > Tree->data.p_num)
    {
        if (Tree->right != NULL)
            add_node(newRecord, Tree->right);
        else
        {
            Tree->right = new Node;
            Tree->right->left = Tree->right->right = NULL;
            Tree->right->data = newRecord;
        }
    }
}
void DelTree(Node*& Tree)
{
    if (Tree)
    {
        DelTree(Tree->left);
        DelTree(Tree->right);
        delete Tree;
        Tree = NULL;
    }
}
Node* minValueNode(Node* Tree)
{
    Node* temp = Tree;
    while (temp && temp->left != NULL)
        temp = temp->left;
    return temp;
}
Node* deleteNode(Node*& Tree, string p_num)
{
    if (Tree == NULL)
        return Tree;
    if (p_num < Tree->data.p_num)
        Tree->left = deleteNode(Tree->left, p_num);
    else if (p_num > Tree->data.p_num)
        Tree->right = deleteNode(Tree->right, p_num);
    else
    {
        if (Tree->left == NULL)
        {
            Node* temp = Tree->right;
            free(Tree);
            return temp;
        }
        else if (Tree->right == NULL)
        {
            Node* temp = Tree->left;
            free(Tree);
            return temp;
        }
        Node* temp = minValueNode(Tree->right);
        Tree->data.p_num = temp->data.p_num;
        Tree->right = deleteNode(Tree->right, temp->data.p_num);
    }
    return Tree;
}
PhoneBook TreeFindNode(Node*& Tree, string p_num, int& count)
{
    if (Tree)
    {
        count++;
        if (p_num == Tree->data.p_num)
            return Tree->data;
        if (p_num > Tree->data.p_num)
            return TreeFindNode(Tree->right, p_num, count);
        else
            return TreeFindNode(Tree->left, p_num, count);
    }
    cout << " NotFound" << endl;
    PhoneBook a;
    return a;
}

void InputFromFile(fstream& stream, Node*& MyTree)
{
    while (!stream.eof())
    {
        PhoneBook a;
        stream >> a.name >> a.p_num >> a.b_day >> a.MoneyAccount;
        add_node(a, MyTree);
    }
}
void InputFromFile(list<PhoneBook>& obj, fstream& stream)
{
    while (!stream.eof())
    {
        PhoneBook a;
        stream >> a.name >> a.p_num >> a.b_day >> a.MoneyAccount;
        obj.push_back(a);
    }
}


int main()
{
    cout << "Enter\n1. Show tree\n2. ReverseShow tree\n3. InnerShow tree \n4. Show tree by Virt\n5. Delete tree node by phone number\n6. Delete tree \n7. Find tree node by phone number\nAction : ";

    int action, TreeComplexity = 0, ListComplexity = 0;
    cin >> action;
    string temp;
    Node* rootPhoneBook = NULL;
    fstream fin("a1.txt");
    list<PhoneBook> Kyiv;
    InputFromFile(fin, rootPhoneBook);
    fin.close();
    fin.open("a1.txt");
    InputFromFile(Kyiv, fin);
    switch (action)
    {
    case 1:
        show(rootPhoneBook);
        break;
    case 2:
        showReverse(rootPhoneBook);
        break;
    case 3:
        showInner(rootPhoneBook);
        break;
    case 4:
        showVirt(rootPhoneBook, 0);
        break;
    case 5:
        cout << "Enter phone number : ";
        cin >> temp;
        rootPhoneBook = deleteNode(rootPhoneBook, temp);
        show(rootPhoneBook);
        break;
    case 6:
        DelTree(rootPhoneBook);
        break;
    case 7:
        cout << "Enter phone number : ";
        cin >> temp;
        cout << TreeFindNode(rootPhoneBook, temp, TreeComplexity);
        for (auto record : Kyiv)
        {
            ListComplexity++;
            if (record.p_num == temp)
                break;
        }
        break;
    default:
        break;
    }
    cout << endl;
    cout << "Number of tree search checks : " << TreeComplexity << endl;
    cout << "Number of linear search checks : " << ListComplexity;

    return 0;
}


