
#pragma once

#include "Nodo.h"
template <class T>

class Stack {

    private:
    Nodo<T>* start;
    int sizeStack;


    public:
    //Constructor
    Stack() {
        this->start = nullptr;
        this->sizeStack = 0;
    }

    //Insertar al inicio de la pila
    void push(T value) {
        Nodo<T>* nuevo = new Nodo<T>(value);

        nuevo->setNext(this->start);
        this->start = nuevo;

        this->sizeStack++;
    }

    //Eliminar el elemento superior
    void pop() {
        if (this->start == nullptr) {
            throw 0;
        }
        Nodo<T>* eliminar = this->start;
        this->start = this->start->getNext();

        delete eliminar;
        this->sizeStack--;
    }

    T top() {
        if (this->start == nullptr) {
            throw 0;
        }
        return this->start->getValor();
    }

    //Comprobar si está vacía
    bool isEmpty() {
        return this->start == nullptr;
    }

    //Obtener cantidad de elementos
    int size() {
        return this->sizeStack;
    }



    Nodo<T>* getHead() {
        return this->start;
    }

    //Destructor
    ~Stack() {
        while (this->start != nullptr) {
            Nodo<T>* eliminar = this->start;

            this->start = this->start->getNext();
            delete eliminar;
        }
        this->sizeStack = 0;
    }

};