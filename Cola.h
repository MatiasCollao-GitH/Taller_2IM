//
// Created by ignac on 12/10/2026.
//

#ifndef TALLER_2IM_COLA_H
#define TALLER_2IM_COLA_H
#include "Nodo.h"


template <class T>
class Cola {
private:
    Nodo<T>* inicio;
    Nodo<T>* final;
    int tamano;
    bool vacio;

public:
    Cola();
    int size();
    void push(T valor);

    T front();
    T back();
    void pop();
    bool isEmpty();
    ~Cola();


    void imprimir();
    Nodo<T>* getInicio() const;
};



#endif //TALLER_2IM_COLA_H
