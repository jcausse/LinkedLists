//
// Created by Juan Ignacio Causse on 07/06/2021.
//

#ifndef NODE_H
#define NODE_H

#include <iostream>

template <typename T> class Node {
public:
    Node() : nextNode(NULL) {                               //Default constructor.
        this->data = new T;
    }
    Node(T data_, Node* nextNode_) {                        //Constructor.
        if (!nextNode_) { std::cout << "NULL parameter received!" << std::endl; }
        else {
            this->data = new T;
            *data = data_;
            nextNode = nextNode_;
        }
    };
    ~Node() { delete data; };                               //Destructor.

    void setNext(Node* next){ this->nextNode = next; };    //Next node setter.
    Node* getNext(){return this->nextNode; };              //Next node getter.
    void setData(T data_){ *data = data_; };               //Node data setter.
    T* getData(){ return this->data; };                    //Node data getter.

private:
    T* data;                                               //Node data. Default = NULL.
    Node* nextNode;                                        //Next node. Default = NULL.
};

#endif //NODE_H