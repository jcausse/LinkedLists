//
// Created by Juan Ignacio Causse on 08/06/2021.
//

#include "algorithms.h"

void iterationAlgorithm(SimpleNode* header, int* startElement, 
int* nextElement, int* comparationsMade, int* sizeOfAuxList){
    SimpleNode* aux = header->next;
    int auxInt;
    List<int> list;
    list.append(aux->data);
    while (aux->next){
        auxInt = aux->data;
        aux = aux->next;
        if (list.contains(aux->data)){
            *startElement = auxInt;
            *nextElement = aux->data;
            *comparationsMade += (*nextElement + 1);
            return;
        }
        *comparationsMade += list.getSize();
        list.append(aux->data);
        (*sizeOfAuxList)++;
    }
}

void tortoiseHareAlgorithm(SimpleNode* header, int* comparationsMade){
    bool loopFound = true;
    SimpleNode* tortoise = header->next;
    SimpleNode* hare = header->next;
    do{
        *comparationsMade += 1;
        std::cout << "Tortoise: " << tortoise->data;
        std::cout << ", Hare: " << hare->data << std::endl;
        if ((hare->next->next) == NULL){
            loopFound = false;
            break;
        }
        tortoise = tortoise->next;
        hare = hare->next->next;
    }
    while ((tortoise->data) != (hare->data));
    if (loopFound){
        std::cout << "Loop encontrado:" << std::endl;
        std::cout << "Tortoise: " << tortoise->data;
        std::cout << ", Hare: " << hare->data << std::endl;
    }
    else
        std::cout << "La lista no contiene ciclos." << std::endl;
    *comparationsMade += 1;
}