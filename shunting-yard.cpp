//Michael Wang
//5/9/2021
//The shunting yard allows conversion of infix to postfix notation. This program also allows the user to create expressions with prefix notation and creates a binary expression tree.
#include <iostream>
#include <ctype.h>
#include <cstring>
#include "node.h"
#include "stack.h" // As mentioned in .h/cpp files, stack is capable of being used both as a stack and a queue.

using namespace std;

//prototypes

int precedence(char op);
node* buildBinaryTree(stack* temp, stack* stack);
void printBinaryTree(node* root, int level);
void reverseStack(stack* secStack, stack* stack);
void printStack(stack* stack);

int main(){
    while(1){

        //take user input
        cout << "Enter mathematical expression - Please enter all parts of the expression without spaces. Enter [Q] to quit" << endl;
        char* input = new char[50];
        for(int i = 0; i < 50; i++){
            input[i] = 'n';
        }
        cin.clear();
        cin.getline(input, 50);
        if(input[0] == 'Q'){
            break;
        }

        //output queue and operator stack
        stack* output = new stack();
        stack* op = new stack();
        int i = 0;

        //implement the shunting yard algorithm
        while(input[i] != 'n'){
            char temp = input[i];
            if(temp != 'n'){
                if(isdigit(temp)){
                    cout << temp << " is a digit" << endl;
                    node* newNode = new node(temp);
                    output->push(newNode);
                }
                else if(temp == '+' || temp == '-' || temp == '*' || temp == 'x' || temp == '/' || temp == '^'){
                    cout << temp << " is an operator" << endl;
                    while(op->peek() != NULL 
                    && ((precedence(op->peek()->getValue()) > precedence(temp))
                    || (precedence(op->peek()->getValue()) == precedence(temp) && temp != '^')) 
                    && op->peek()->getValue() != '('){
                        node* n = new node(op->pop()->getValue());
                        output->push(n);
                    }
                    node* newNode = new node(temp);
                    op->push(newNode);
                }
                else if(temp == '('){
                    cout << temp << " is a left parenthesis" << endl;
                    node* newNode = new node(temp);
                    op->push(newNode);
                }
                else if(temp == ')'){
                    cout << temp << " is a right parenthesis" << endl;
                    while(op->peek()->getValue() != '('){
                        if(op->peek()->getValue() != '('){
                            node* n = new node(op->pop()->getValue());
                            output->push(n);
                        }
                    }
                    if(op->peek()->getValue() == '('){
                        op->pop();
                    }
                }
            }
            i++;
        }
        //Push all remaining operators to output.
        while(op->peek() != NULL){
            node* n = new node(op->pop()->getValue());
            output->push(n);
        }

        //ask the user to choose notation
        cout << "choose a notation for output: postfix, prefix, infix" << endl;
        stack* output2 = new stack();
        stack* tempstack = new stack();
        char* input2 = new char[10];
        cin.clear();
        cin.getline(input2, 10);

        //Processing algorithms for postfix, prefix, and infix respectively.
        if(strcmp(input2, "postfix") == 0){
            reverseStack(output2, output);
            cout << "\nPOSTFIX NOTATION: " << endl;
            printStack(output2);
            node* root = buildBinaryTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinaryTree(root, 0);
        }
        else if(strcmp(input2, "prefix") == 0){
            cout << "\nPREFIX NOTATION: " << endl;
            printStack(output);
            reverseStack(output2, output);
            node* root = buildBinaryTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinaryTree(root, 0);
        }
        else if(strcmp(input2, "infix") == 0){
            cout << "\nINFIX NOTATION: " << endl;
            cout << input << endl;
            reverseStack(output2, output);
            node* root = buildBinaryTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinaryTree(root, 0);
        }
    }
    return 0;
}

//Evaluates precedence based on order of operations and returns an integer value. The higher the number, the higher the precedence.
int precedence(char op){
    if(op == '^'){
        return 4;
    }
    else if(op == 'x' || op == '*' || op == '/'){
        return 3;
    }
    else if(op == '+' || op == '-'){
        return 2;
    }
    else{
        return 0;
    }
}

//Function that reverses the order of elements in a stack/queue.
void reverseStack(stack* secStack, stack* stack){
    while (stack->getSize() != 0){
        secStack->push(stack->pop());
    }
}

//Create a binary tree.
node* buildBinaryTree(stack* temp, stack* stack){
    node* read = stack->peek();
    node* root;
    int size = stack->getSize();
    while(size != 0){
        while(isdigit(read->getValue())){
            node* n = new node(read->getValue());
            temp->push(n);
            read = read->getNext();
            size--;
        }
        if(read->getValue() == '+', '-', '*', 'x', '/'){
            node* treenode = new node(read->getValue());
            cout << "treenode: " << read->getValue() << endl;
            treenode->setLeft(temp->pop());
            cout << "treenode left:" << treenode->getLeft()->getValue() << endl;
            treenode->setRight(temp->pop());
            cout << "treenode right:" << treenode->getRight()->getValue() << '\n' << endl;
            temp->push(treenode);
            read = read->getNext();
            size--;
            root = treenode;
        }
    }
    cout << "ROOT: " << root->getValue() << '\n' << endl;
    return root;
}

//Print binary tree. Tree comes out sideways.
void printBinaryTree(node* root, int spacing){
    if(root == NULL){
        return;
    }
    spacing += 10;
    printBinaryTree(root->getRight(), spacing);
    cout << endl;
    for(int i = 10; i < spacing; i++){
        cout << " ";
    }
    cout << root->getValue() << '\n';
    printBinaryTree(root->getLeft(), spacing);
}

//Prints a stack.
void printStack(stack* stack){
    node* temp = stack->peek();
    while(temp != NULL){
        cout << temp->getValue();
        temp = temp->getNext();
    }
    cout << '\n' << endl;
}