#include <string>
#include "Node.h"
using namespace std;

// string Node::getName() const
// {return name;}

// int Node::getSize() const
// {return size;}

// Node* Node::getNext() const
// {return next}

Node::Node()
{
    name = "";
    size = -1;
    next = nullptr;
}

Node::Node(string s, int n)
{
    name = s;
    size = n;
    next = nullptr;
}


Node::~Node()
    {next = nullptr;}