#ifndef NODE_H
#define NODE_H

class node
{
private:
    char value;
    node* next;
    node* left;
    node* right;
public:
    node(char newValue);
    char getValue();
    void setValue(char data);
    node* getNext();
    void setNext(node* newNext);
    node* getLeft();
    node* getRight();
    void setLeft(node* n);
    void setRight(node* n);
    ~node();
};

#endif