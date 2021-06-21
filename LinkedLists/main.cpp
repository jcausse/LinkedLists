#include <iostream>
#include "List.h"
#include "SimpleNode.h"
#include "algorithms.h"

#define SIMPLE_LIST_SIZE 7
#define MAX_ITERATIONS 20

using namespace std;

void ack(){
    getchar();
}
void advancedListUsage(){
    List<int> list;
    list.insert(0);
    list.insert(1);
    list.next();
    list.insert(2);
    list.append(3);
    list.append(4);
    list.print();

    if (list.contains(4)) { cout << "Nodo 4 encontrado" << endl; }
    else{ cout << "Nodo 4 no encontrado" << endl; }
    if (list.contains(5)) { cout << "Nodo 5 encontrado" << endl; }
    else{ cout << "Nodo 5 no encontrado" << endl; }

    list.remove();
    list.print();

    list.previous();
    list.remove();
    list.print();

    list.remove();
    list.print();

    list.clear();
    list.print();
}
bool createSimpleList(SimpleNode* header, int N){
    if (N < 1) { return false; }
    header->data = -1;
    SimpleNode* nodeArray[N];
    for (int i = 0; i < N; i++){
        nodeArray[i] = new SimpleNode;
        nodeArray[i]->data = i;
    }
    header->next = nodeArray[0];
    for (int i = 0; i < N - 1; i++){
        nodeArray[i]->next = nodeArray[i + 1];
    }
    nodeArray[N - 1] ->next = nullptr;
    return true;
}
void destroySimpleList(SimpleNode* header){
    SimpleNode* aux = header;
    SimpleNode* aux2 = header->next;
    SimpleNode* deletedNodes [SIMPLE_LIST_SIZE];
    unsigned short i = 0;
    do{
        for (unsigned short j = 0;  j < i; j++){
            if(deletedNodes[j] == aux)
                throw runtime_error("main.cpp: destroySimpleList: Se intento destruir un elemento ya destruido.");
        }
        delete aux;
        deletedNodes[i++] = aux;
        aux = aux2;
        aux2 = aux->next;
    }
    while (aux2);
    delete aux;
}
void printSimpleList(SimpleNode* header, int maxIterations){
    SimpleNode* aux = header->next;
    int iterations = 0;
    cout << "|Header| => ";
    while (aux && (iterations != maxIterations)){
        cout << aux->data;
        aux = aux->next;
        iterations++;
        if (aux && (iterations != maxIterations)){
            cout << " => ";
        }
    }
    cout << endl;
}
void createLoop(SimpleNode* header, int loopEndElement){
    SimpleNode* aux = header->next;
    SimpleNode* aux2;
    while (aux->next){
        if (aux->data == loopEndElement){ aux2 = aux; }
        aux = aux->next;
    }
    if (aux->data == loopEndElement){ aux2 = aux; }
    aux->next = aux2;
}

int main() {
    cout << "Juan Ignacio Causse - Trabajo Teorico 2 - Algoritmos y Estructuras de Datos - 8/6/21" << endl;
    ack();

    cout << "Lista \"avanzada\" creada con una clase, con metodos que controlan el uso de punteros:" <<endl;
    advancedListUsage();
    ack();

    cout << "Lista creada de manera simple, utilizando structs como nodos, sin proteccion:" <<endl;
    SimpleNode* header = new SimpleNode;                         //Crear una lista enlazada e imprimirla
    createSimpleList(header, SIMPLE_LIST_SIZE);
    printSimpleList(header, SIMPLE_LIST_SIZE);
    ack();

    cout << "Introducimos un loop en la lista. Esto es posible debido a que no hay proteccion:" <<endl;
    createLoop(header, 3);                                         //Crear un loop (emular el problema) e imprimir la lista
    printSimpleList(header, MAX_ITERATIONS);
    ack();

    cout << "Intentamos destruir la lista (try/throw/catch). La lista se destruye y se detiene al encontrar el problema:" <<endl;
    try { destroySimpleList(header); }                          //Intentar destruir la lista con el loop creado
    catch(runtime_error  & error){
        cout << error.what() << endl;
    }
    ack();

    int startElement, nextElement, comparationsMade = 0, sizeOfAuxList = 0;

    cout << "Creamos una nueva lista simple para utilizar con los algoritmos, y le generamos un loop:" <<endl;
    SimpleNode* header2 = new SimpleNode;                         //Crear una lista enlazada e imprimirla
    createSimpleList(header2, SIMPLE_LIST_SIZE);
    printSimpleList(header2, SIMPLE_LIST_SIZE);
    createLoop(header2,3);                                         //Crear un loop (emular el problema) e imprimir la lista
    printSimpleList(header2, MAX_ITERATIONS);
    ack();

    cout << "Utilizamos un algoritmo que itera la lista y encuentra el loop:" << endl;
    iterationAlgorithm(header2, &startElement, &nextElement, &comparationsMade, &sizeOfAuxList);
    cout << "Elemento que inicia el loop: " << startElement << endl;
    cout << "Elemento al que \"vuelve\" el loop: " << nextElement << endl;
    cout << "Comparaciones realizadas: " << comparationsMade << endl;
    cout << "Memoria utilizada: " << sizeOfAuxList*sizeof(Node<int>) + sizeof(List<int>) << " bytes" << endl;
    comparationsMade = 0; sizeOfAuxList = 0;
    ack();

    cout << "Con el mismo algoritmo, si el loop esta unicamente en el ultimo elemento:" << endl;
    SimpleNode* header3 = new SimpleNode;                         //Crear una lista enlazada e imprimirla
    createSimpleList(header3, SIMPLE_LIST_SIZE);
    printSimpleList(header3, SIMPLE_LIST_SIZE);
    createLoop(header3, SIMPLE_LIST_SIZE - 1);                                         //Crear un loop (emular el problema) e imprimir la lista
    printSimpleList(header3, MAX_ITERATIONS);
    iterationAlgorithm(header3, &startElement, &nextElement, &comparationsMade, &sizeOfAuxList);
    cout << "Elemento que inicia el loop: " << startElement << endl;
    cout << "Elemento al que \"vuelve\" el loop: " << nextElement << endl;
    cout << "Comparaciones realizadas: " << comparationsMade << endl;
    cout << "Memoria utilizada: " << sizeOfAuxList*sizeof(Node<int>) + sizeof(List<int>) << " bytes" << endl;
    comparationsMade = 0; sizeOfAuxList = 0;
    ack();

    cout << "Ahora utilizamos el algoritmo Tortoise - Hare para encontrar el loop:" << endl;
    SimpleNode* header4 = new SimpleNode;                         //Crear una lista enlazada e imprimirla
    createSimpleList(header4, SIMPLE_LIST_SIZE);
    printSimpleList(header4, SIMPLE_LIST_SIZE);
    createLoop(header4, 3);                                         //Crear un loop (emular el problema) e imprimir la lista
    printSimpleList(header4, MAX_ITERATIONS);
    tortoiseHareAlgorithm(header4, &comparationsMade);
    cout << "Comparaciones realizadas: " << comparationsMade << endl;
    cout << "Memoria utilizada: " << 2*sizeof(int*) << " bytes" << endl;
    comparationsMade = 0; sizeOfAuxList = 0;
    ack();

    cout << "Una vez mas, si el loop esta unicamente en el ultimo elemento:" << endl;
    SimpleNode* header5 = new SimpleNode;                         //Crear una lista enlazada e imprimirla
    createSimpleList(header5, SIMPLE_LIST_SIZE);
    printSimpleList(header5, SIMPLE_LIST_SIZE);
    createLoop(header5, SIMPLE_LIST_SIZE - 1);                                         //Crear un loop (emular el problema) e imprimir la lista
    printSimpleList(header5, MAX_ITERATIONS);
    tortoiseHareAlgorithm(header5, &comparationsMade);
    cout << "Comparaciones realizadas: " << comparationsMade << endl;
    cout << "Memoria utilizada: " << 2*sizeof(int*) << " bytes" << endl;
    comparationsMade = 0; sizeOfAuxList = 0;
    ack();

    return 0;
}