//
// Created by Matías Collao on 14-09-2026.
//

#ifndef TALLER_1_IM_COLA_H
#define TALLER_1_IM_COLA_H
#include "Nodo.h"
#include <iostream>

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
    
    if (this->inicio == nullptr) {
        this->final = nullptr;
        this->vacio = true;
    }
    delete aEliminar;
    this->tamano--;
}

template<class T>
bool Cola<T>::isEmpty() {
    return this->inicio == nullptr;
}

template<class T>
void Cola<T>::imprimir() {
    Nodo<T>* actual = this->inicio;

    std::cout << "=== PACIENTES EN ESPERA ===" << std::endl;

    int cont = 1;
    while (actual != nullptr) {
        T paciente = actual->getValor();

        if (paciente != nullptr) {
            std::cout << cont << ". " << paciente->getId() << " - " << paciente->getNombre() << std::endl;
        }
        actual = actual->getNext();
        cont++;
    }
    std::cout << std::endl;
}

template<class T>
Nodo<T> *Cola<T>::getInicio() const {
    return this->inicio;
}


template<class T>
Cola<T>::~Cola() {
    while (!this->isEmpty()) {
        this->pop();
    }
}










#endif //TALLER_1_IM_COLA_H
