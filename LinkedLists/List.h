//
// Created by Juan Ignacio Causse on 07/06/2021.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Node.h"

template <typename T> class List{
public:
    //CONSTRUCTORS AND DESTRUCTORS
    List() : listSize(0), position(0){
        header = new Node<T>;
        header->setNext(NULL);
        header->setData(dummy);
        this->returnedDummy = false;
    };
    ~List(){
        clear();
        delete header;
    };

    //POSITION CONTROL
    bool setPosition(int position_){
        if ((position_ < 0) || (position_ > (listSize -1))){ return false; }
        else { position = position_; return true; }
    };
    int getPosition(){
        if (isEmpty()){ return -1; }
        return position;
    };
    bool next(){
        if (position < (listSize - 1)) { position++; return true; }
        else{ return false; }
    };
    bool previous(){
        if (position > 0){ position--; return true; }
        else { return false; }
    };
    int getMaxPosition(){ return listSize - 1; }

    //DATA CONTROL
    bool setData(T data_){
        if (isEmpty()) { return false;}
        Node<T>* aux = header;
        for (unsigned int i = 0; i <= position; i++) {aux = aux->getNext(); }
        aux->setData(data_);
        return true;
    }
    T getData(){
        if (isEmpty()) {returnedDummy = true; return dummy; }
        else { returnedDummy = false; }
        Node<T>* aux = header;
        for (unsigned int i = 0; i <= position; i++) {aux = aux->getNext(); }
        return (*(aux->getData()));
    }

    //NODE CONTROL
    void append(T data_){
        Node<T>* aux = header;                      //Pointer to header
        Node<T>* aux2 = new Node<T>;                //Node to append
        while (aux->getNext()){ aux = aux->getNext(); }  //Make aux point to the last node. O(n)
        aux->setNext(aux2);                         //Set the new node as the next of the last one
        aux2->setData(data_);                       //Set the data of the new node
        aux2->setNext(NULL);                        //Set the next og the new node as null, as it becomes the last node
        listSize++;
    };
    void insert(T data_){
        Node<T>* aux = new Node<T>;                 //Node to insert
        Node<T>* aux2 = header;                     //Pointer to the header
        for (unsigned int i = 0; i <= position; i++){ //Make aux2 point to the current node
            if (aux2->getNext())
                aux2 = aux2->getNext();
        }
        aux->setNext(aux2->getNext());              //Set new node's next node as the next node of the current one
        aux2->setNext(aux);                         //Set the new node as the next node of the current one
        aux->setData(data_);                        //Set new node's data
        listSize++;
    };
    bool remove(){
        if (isEmpty()) { return false; }            //Protection against removing elements from empty lists
        Node<T>* nodeToRemove = header;             //Node that will be removed
        Node<T>* previousNode = NULL;               //The previous node of the one to be removed
        Node<T>* nextNode = header->getNext();      //The next node of the one to be removed
        for (unsigned int i = 0; i <= position; i++){   //As nodeToRemove starts pointing to the header, we use <=
            previousNode = nodeToRemove;            //Previous -> current
            nodeToRemove = nextNode;                //Current -> next
            nextNode = nextNode->getNext();         //Next -> nextNode's next node
        }
        previousNode->setNext(nextNode);            //The previous node's next node is the current's node next node
        delete nodeToRemove;                        //Remove the current node
        if (position > 0) { position--; }           //Always point to the previous node of the one that has been
        listSize--;                                 //removed. If the one removed was the node 0, point to the next one
        return true;
    };

    //MISCELLANEOUS
    bool isEmpty(){ return (header->getNext() == NULL); }      //Returns true if the list is empty

    bool didIGetADummy(){
        return returnedDummy;
    }

    bool clear(){
        if (isEmpty()){ return false; }             //Can't clear an empty list
        position = 0;                               //If the list isn't empty, set position to 0
        while (header->getNext())                   //Clear the list
            remove();                               //If position = 0 when remove() is called, it is left "as is"
        listSize = 0;
        return true;
    }

    void print(){
        Node<T>* aux = header;
        std::cout << "|Header|";
        if (!isEmpty()){ std::cout << " => "; }
        for (unsigned int i = 0; i < listSize; i++){
            aux = aux->getNext();
            std::cout << *(aux->getData());
            if (i < (listSize - 1)) { std::cout << " => "; }
        }
        std::cout << std::endl;
    }

    int getSize(){ return listSize; }
    int getByteSize(){ return (listSize + 1) * sizeof(T); }

    bool contains(T value){
        if (isEmpty()) { return false; }
        Node<T>* aux = header;
        while (aux->getNext()){
            if (*(aux->getData()) == value){
                return true;
            }
            aux = aux->getNext();
        }
        if (*(aux->getData()) == value) {return true; }
        return false;
    }

private:
    bool returnedDummy;
    int position;
    int listSize;
    Node<T>* header;
    T dummy;
};
#endif //LIST_H