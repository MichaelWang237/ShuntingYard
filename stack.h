//Header file for Stack/Queue class.
#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <iostream>

class stack
{
private:
    node* head;
    int size = 0;
public:
    stack();
    node* pop();
    node* peek();
    void push(node* n);
    node* dequeue();
    int getSize();
    ~stack();
};

#endif