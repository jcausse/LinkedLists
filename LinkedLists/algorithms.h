//
// Created by Juan Ignacio Causse on 08/06/2021.
//

#ifndef LINKEDLISTS_ALGORITHMS_H
#define LINKEDLISTS_ALGORITHMS_H

#include <iostream>
#include "SimpleNode.h"
#include "List.h"

void iterationAlgorithm(SimpleNode* header, int* startElement, int* nextElement, int* comparationsMade, int* sizeOfAuxList);
void tortoiseHareAlgorithm(SimpleNode* header, int* comparationsMade);

#endif //LINKEDLISTS_ALGORITHMS_H