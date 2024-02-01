#include <string>
#include "Queue.h"
using namespace std;


//***********************************************************
// Written By: Juan Chavarria
// peek(): returns the top value of the queue
//
// returns: Node object pointer. Need to save before calling dequeue
//***********************************************************
Node* Queue::peek()
    {return top;}

//***********************************************************
// Written By: Juan Chavarria
// length(): counts the number of Nodes in the queue
//
// returns: integer showing the number of objects in the queue
//***********************************************************
int Queue::length()
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

//***********************************************************
// Written By: Juan Chavarria
// enqueue(): adds a new value to the end of the queue
// s: string with the group name
// n: integer with group size
// returns: void/nothing (memory deallocated propery)
//***********************************************************
void Queue::enqueue(string s, int n)
{
    Node* newNode = new Node(s, n);

    if (top == nullptr)
    {
        top = newNode;
        return;
    }

    Node* curr = top;

    while (curr->next != nullptr)
        curr = curr->next;

    curr->next = newNode;
    return;
}

//***********************************************************
// Written By: Juan Chavarria
// dequeue(): removes the top value of the queue
//
// returns: void/nothing (memory deallocated propery)
//***********************************************************
void Queue::dequeue()
{
    if (top == nullptr)
        return;

    Node* topD = top;

    top = top->next;
    delete topD;
    topD = nullptr;
    return;
}

//***********************************************************
// Written By: Juan Chavarria
// Queue(): sets top pointer to nullptr
//
// returns: void/nothing 
//***********************************************************
Queue::Queue()
{top = nullptr;}

//***********************************************************
// Written By: Juan Chavarria
// ~Queue(): destroys and deallocates memory
//
// returns: void/nothing (memory deallocated properly)
//***********************************************************
Queue::~Queue()
{
    Node* curr = top;

    while (top != nullptr)
    {
        curr = top;
        top = top->next;
        delete curr;
    }
}