#include "Node.h"
#include "Stack.h"
using namespace std;

//***********************************************************
// Written By: Juan Chavarria
// Stack(): sets top pointer to nullptr
//
// returns: void/nothing 
//***********************************************************
Stack::Stack()
{top = nullptr;}

//***********************************************************
// Written By: Juan Chavarria
// ~Stack(): destroys and deallocates memory
//
// returns: void/nothing (memory deallocated properly)
//***********************************************************
Stack::~Stack()
{
    Node* curr = top;

    while (top != nullptr)
    {
        curr = top;
        top = top->next;
        delete curr;
    }
}

//***********************************************************
// Written By: Juan Chavarria
// push(): adds a new value to the end of the stack
// s: string with the group name
// n: integer with group size
// returns: void/nothing (memory deallocated propery)
//***********************************************************
void Stack::push(string s, int n)
{
    Node* newNode = new Node(s, n);

    if (top == nullptr)
    {
        top = newNode;
        return;
    }

    newNode->next = top; 
    top = newNode;
}

//***********************************************************
// Written By: Juan Chavarria
// pop(): removes the top value of the stack
//
// returns: void/nothing (memory deallocated propery)
//***********************************************************
void Stack::pop()
{
    if (top == nullptr)
        return;

    Node* temp = top;
    top = top->next;
    delete temp;
    temp = nullptr;
    return;
}

//***********************************************************
// Written By: Juan Chavarria
// peek(): returns the top value of the stack
//
// returns: Node object pointer. Need to save before calling pop()
//***********************************************************
Node* Stack::peek()
{return top;}

//***********************************************************
// Written By: Juan Chavarria
// length(): counts the number of Nodes in the stack
//
// returns: integer showing the number of objects in the stack
//***********************************************************
int Stack::length()
{
    int count = 0;
    Node* curr = top;

    while (curr != nullptr)
    {
        count += 1;
        curr = curr->next;
    }

    return count;
}