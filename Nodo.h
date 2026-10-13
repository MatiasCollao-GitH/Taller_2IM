//
// Created by ignac on 12/10/2026.
//

#ifndef TALLER_2IM_NODO_H
#define TALLER_2IM_NODO_H


#pragma once
template <class T>

class Nodo {
private:
    T valor;
    Nodo<T>* next;
public:
    Nodo(T valor) {
        this->valor = valor;
        this->next = nullptr;
    }
    T getValor();
    Nodo<T>* getNext();

    void setValor(T valor);
    void setNext(Nodo<T>* next);

    ~Nodo();
};



#endif //TALLER_2IM_NODO_H
