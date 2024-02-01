#ifndef STACK_H
#define STACK_H
#include <string>
#include "Node.h"
using namespace std;

class Stack
{
    private:
        Node* top;
    public:
        Stack();
        ~Stack();
        void push(string, int);
        void pop();
        Node* peek();
        int length();
};
#endif