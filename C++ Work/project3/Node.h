#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node
{
    
    public:
        string name;
        int size;
        Node* next;
        Node()
        {
            name = "";
            size = -1;
            next = nullptr;
        }

        Node(string s, int n)
        {
            name = s;
            size = n;
            next = nullptr;
        }
        ~Node() 
            {next = nullptr;}      
};

#endif