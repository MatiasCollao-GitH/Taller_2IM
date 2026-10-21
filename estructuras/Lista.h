//
// Created by Matías Collao on 16-09-2026.
//

#ifndef TALLER_1_IM_LISTA_H
#define TALLER_1_IM_LISTA_H
#pragma once
#include "Nodo.h"

template <class T>
class Lista {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    Lista() : cabeza(nullptr), tamano(0) {}

    ~Lista() {
        Nodo<T>* actual = this->cabeza;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->getNext();
            delete temp;
        }
    }

    Nodo<T>* getCabeza() const { return this->cabeza; }
    int getTamano() const { return this->tamano; }
    bool isEmpty() const { return this->cabeza == nullptr; }

    void agregarFinal(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (this->cabeza == nullptr) {
            this->cabeza = nuevo;
        } else {
            Nodo<T>* actual = this->cabeza;
            while (actual->getNext() != nullptr) {
                actual = actual->getNext();
            }
            actual->setNext(nuevo);
        }
        this->tamano++;
    }
};
#endif //TALLER_1_IM_LISTA_H
