//
// Created by ignac on 12/10/2026.
//

#include "Cola.h"

template<class T>
Cola<T>::Cola() {
    this->inicio = nullptr;
    this->final = nullptr;
    this->tamano = 0;
    this->vacio = true;
}

template<class T>
int Cola<T>::size() {
    return this->tamano;
}

template<class T>
void Cola<T>::push(T valor) {

    Nodo<T>* aAgregar = new Nodo<T>(valor);

    if (this->inicio == nullptr) {
        this->inicio = aAgregar;
        this->final = aAgregar;
        this->tamano = 1;
        this->vacio = false;
        return;
    }

    this->final->setNext(aAgregar);
    this->final = aAgregar;
    this->tamano++;
}

template<class T>
T Cola<T>::front() {
    if (this->inicio == nullptr) {
        return 0;
    }
    return this->inicio->getValor();
}

template<class T>
T Cola<T>::back() {
    if (this->final == nullptr) {
        return 0;
    }
    return this->final->getValor();
}

template<class T>
void Cola<T>::pop() {
    if (this->inicio == nullptr) {
        return;
    }
    Nodo<T>* aEliminar = this->inicio;
    this->inicio = this->inicio->getNext();
    delete aEliminar;
    this->tamano--;
}

template<class T>
bool Cola<T>::isEmpty() {
    return this->vacio;
}

template<class T>
void Cola<T>::imprimir() {
    Nodo<T>* actual = this->inicio;

    while (actual != nullptr) {
        T paciente = actual->getValor();

        if (paciente != nullptr) {
            paciente->datos();
        }
        actual = actual->getNext();
    }
}

template<class T>
Nodo<T> *Cola<T>::getInicio() const {
    return this->inicio;
}


template<class T>
Cola<T>::~Cola() {
}
