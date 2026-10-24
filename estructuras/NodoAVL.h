//
// Created by ignac on 24/10/2026.
//

#ifndef TALLER_2IM_NODOAVL_H
#define TALLER_2IM_NODOAVL_H

#pragma once

#include "../dominio/Paciente.h"

class NodoAVL {
    private:
    Paciente* paciente;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;


    public:
    NodoAVL(Paciente* paciente) {
        this->paciente = paciente;
        this->izquierdo = nullptr;
        this->derecho = nullptr;
        this->altura = 1;
    }

    Paciente* getPaciente() const {
        return this->paciente;
    }
    NodoAVL* getIzquierdo() const {
        return this->izquierdo;
    }
    NodoAVL* getDerecho() const {
        return this->derecho;
    }
    int getAltura() const {
        return this->altura;
    }
    void setPaciente(Paciente* paciente) {
        this->paciente = paciente;
    }
    void setIzquierdo(NodoAVL* izquierdo) {
        this->izquierdo = izquierdo;
    }
    void setDerecho(NodoAVL* derecho) {
        this->derecho = derecho;
    }
    void setAltura(int altura) {
        this->altura = altura;
    }
};


#endif //TALLER_2IM_NODOAVL_H
