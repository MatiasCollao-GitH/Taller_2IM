//
// Created by Matías Collao on 14-09-2026.
//

#ifndef TALLER_1_IM_NODO_H
#define TALLER_1_IM_NODO_H

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


template<class T>
T Nodo<T>::getValor() {
    return this->valor;
}

template<class T>
Nodo<T> *Nodo<T>::getNext() {
    return this->next;
}

template<class T>
void Nodo<T>::setNext(Nodo<T> *next) {
    this->next = next;
}

template<class T>
void Nodo<T>::setValor(T valor) {
    this->valor = valor;
}

template<class T>
Nodo<T>::~Nodo() {
}

#endif //TALLER_1_IM_NODO_H
