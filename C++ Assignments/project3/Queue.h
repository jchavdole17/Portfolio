#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include "Node.h"
using namespace std;


class Queue
{
    private:
        Node* top;

    public:
        Queue();
        ~Queue();
        Node* peek();
        void dequeue();
        void enqueue(string, int);
        int length();
};

#endif 