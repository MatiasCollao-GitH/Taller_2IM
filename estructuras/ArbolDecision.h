//
// Created by Matías Collao on 21-10-2026.
//

#ifndef TALLER_2IM_ARBOLDECISION_H
#define TALLER_2IM_ARBOLDECISION_H
#pragma once
#include "NodoDecision.h"
#include "../dominio/Paciente.h"
#include <string>

class ArbolDecision {
private:
    NodoDecision* raiz;

    bool evaluarRegla(int idRegla, Paciente* p) const;
    void destruirRecursivo(NodoDecision* nodo);
    void preordenRecursivo(NodoDecision* nodo) const;
    void inordenRecursivo(NodoDecision* nodo) const;
    void postordenRecursivo(NodoDecision* nodo) const;

public:
    ArbolDecision();
    ~ArbolDecision();

    void construirArbol();
    std::string evaluarPaciente(Paciente* p, std::string& rutaTomada) const;


    void mostrarPreorden() const;
    void mostrarInorden() const;
    void mostrarPostorden() const;
};
#endif //TALLER_2IM_ARBOLDECISION_H
