//
// Created by Matías Collao on 21-10-2026.
//

#ifndef TALLER_2IM_NODODECISION_H
#define TALLER_2IM_NODODECISION_H
#pragma once
#include <string>

class NodoDecision {
private:
    int idRegla;
    std::string descripcion;
    std::string textoSi;
    std::string textoNo;
    bool esHoja;
    NodoDecision* si;
    NodoDecision* no;

public:
    //Nodo
    NodoDecision(int idRegla, const std::string& descripcion, const std::string& textoSi, const std::string& textoNo)
        : idRegla(idRegla), descripcion(descripcion), textoSi(textoSi), textoNo(textoNo), esHoja(false), si(nullptr), no(nullptr) {}

    //Nodo hoja
    NodoDecision(const std::string& nombreServicio)
        : idRegla(0), descripcion(nombreServicio), textoSi(""), textoNo(""), esHoja(true), si(nullptr), no(nullptr) {}

    ~NodoDecision() {}

    int getIdRegla() const { return idRegla; }
    std::string getDescripcion() const { return descripcion; }
    std::string getTextoSi() const { return textoSi; }
    std::string getTextoNo() const { return textoNo; }
    bool getEsHoja() const { return esHoja; }

    NodoDecision* getSi() const { return si; }
    NodoDecision* getNo() const { return no; }

    void setSi(NodoDecision* nodo) { this->si = nodo; }
    void setNo(NodoDecision* nodo) { this->no = nodo; }
};
#endif //TALLER_2IM_NODODECISION_H
