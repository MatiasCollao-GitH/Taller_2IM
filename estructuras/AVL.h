//
// Created by ignac on 24/10/2026.
//

#ifndef TALLER_2IM_AVL_H
#define TALLER_2IM_AVL_H

#pragma once

#include "NodoAVL.h"
#include <string>

class AVL {

private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo) const;
    int balance(NodoAVL* nodo) const;
    void actualizarAltura(NodoAVL* nodo);

    NodoAVL* rotarDerecha(NodoAVL* nodo);
    NodoAVL* rotarIzquierda(NodoAVL* nodo);
    NodoAVL* balancear(NodoAVL* nodo);

    NodoAVL* insertarRecursivo(
        NodoAVL* nodo,
        Paciente* paciente
    );

    NodoAVL* eliminarRecursivo(
        NodoAVL* nodo,
        const std::string& id
    );

    NodoAVL* minimo(NodoAVL* nodo) const;

    Paciente* buscarIDRecursivo(
        NodoAVL* nodo,
        const std::string& id
    ) const;

    void buscarNombreRecursivo(
        NodoAVL* nodo,
        const std::string& nombre,
        bool& encontrado
    ) const;

    void inordenRecursivo(NodoAVL* nodo) const;
    void preordenRecursivo(NodoAVL* nodo) const;
    void postordenRecursivo(NodoAVL* nodo) const;

    void mostrarBalancesRecursivo(NodoAVL* nodo) const;
    void destruirRecursivo(NodoAVL* nodo);

public:
    AVL();
    ~AVL();

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    bool insertar(Paciente* paciente);
    bool eliminar(const std::string& id);

    Paciente* buscarID(const std::string& id) const;
    bool buscarNombre(const std::string& nombre) const;

    bool isEmpty() const;
    int getAltura() const;

    void mostrarInorden() const;
    void mostrarPreorden() const;
    void mostrarPostorden() const;
    void mostrarBalances() const;

};


#endif //TALLER_2IM_AVL_H
