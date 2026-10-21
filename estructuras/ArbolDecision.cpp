//
// Created by Matías Collao on 21-10-2026.
//
#include "ArbolDecision.h"
#include <iostream>


ArbolDecision::ArbolDecision() : raiz(nullptr) {
    construirArbol();
}


ArbolDecision::~ArbolDecision() {
    destruirRecursivo(this->raiz);
}




void ArbolDecision::destruirRecursivo(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }
    destruirRecursivo(nodo->getSi());


    destruirRecursivo(nodo->getNo());

    delete nodo;
}

void ArbolDecision::construirArbol() {
    NodoDecision* n1_Edad = new NodoDecision(
        1, "¿Edad < 14?", "Edad < 14", "Edad >= 14");
    NodoDecision* n2_Trauma = new NodoDecision(
        2, "¿Trauma == 1?", "Trauma == 1", "Trauma == 0");

    NodoDecision* n3_Cirugia = new NodoDecision(
        3, "¿RequiereCirugia == 1?", "RequiereCirugia == 1", "RequiereCirugia == 0");
    NodoDecision* n4_Neuro = new NodoDecision(
        4, "¿SintomasNeurologicos == 1?", "SintomasNeurologicos == 1", "SintomasNeurologicos == 0");
    NodoDecision* n5_Cardio = new NodoDecision(
        5, "¿TipoDolor == pecho o Presion >= 140?", "TipoDolor == pecho / PA >= 140", "TipoDolor != pecho");
    NodoDecision* n6_Urgencias = new NodoDecision(
        6, "¿Temperatura >= 38.5 o Dolor >= 8?", "Temperatura >= 38.5 o Dolor >= 8", "Temperatura < 38.5 y Dolor < 8");
    NodoDecision* n7_Hosp = new NodoDecision(
        7, "¿DiasHospitalizacion >= 2?", "DiasHospitalizacion >= 2", "DiasHospitalizacion < 2");


    NodoDecision* h_Pediatria       = new NodoDecision("Pediatria");
    NodoDecision* h_Cirugia         = new NodoDecision("Cirugia");
    NodoDecision* h_Traumatologia   = new NodoDecision("Traumatologia");
    NodoDecision* h_Neurologia      = new NodoDecision("Neurologia");
    NodoDecision* h_Cardiologia     = new NodoDecision("Cardiologia");
    NodoDecision* h_Urgencias       = new NodoDecision("Urgencias");
    NodoDecision* h_Hospitalizacion = new NodoDecision("Hospitalizacion");
    NodoDecision* h_MedGeneral      = new NodoDecision("Medicina General");


    this->raiz = n1_Edad;
    n1_Edad->setSi(h_Pediatria);
    n1_Edad->setNo(n2_Trauma);
    n2_Trauma->setSi(n3_Cirugia);
    n2_Trauma->setNo(n4_Neuro);
    n3_Cirugia->setSi(h_Cirugia);
    n3_Cirugia->setNo(h_Traumatologia);
    n4_Neuro->setSi(h_Neurologia);
    n4_Neuro->setNo(n5_Cardio);
    n5_Cardio->setSi(h_Cardiologia);
    n5_Cardio->setNo(n6_Urgencias);
    n6_Urgencias->setSi(h_Urgencias);
    n6_Urgencias->setNo(n7_Hosp);
    n7_Hosp->setSi(h_Hospitalizacion);
    n7_Hosp->setNo(h_MedGeneral);
}

bool ArbolDecision::evaluarRegla(int idRegla, Paciente* p) const {
    switch (idRegla) {
        case 1: // Pediat
            return p->getEdad() < 14;
        case 2: //  trauma
            return p->getTrauma();
        case 3: // quirúrgica
            return p->getRequiereCirugia();
        case 4: // caeza
            return p->getSintomasNeurologicos();
        case 5: // pecho o presión (dado que no se especific cualquier wea >= 140 entre igual)
            return (p->getTipoDolor() == "pecho" || p->getPresionArterial() >= 140);
        case 6: // fierbre o dolor
            return (p->getTemperatura() >= 38.5 || p->getDolor() >= 8 || p->getRequiereCirugia());
        case 7: // internacion de 2 o mas días
            return p->getDiasHospitalizacion() >= 2;
        default:
            return false;
    }
}

std::string ArbolDecision::evaluarPaciente(Paciente* p, std::string& rutaTomada) const {
    rutaTomada = "";
    if (p == nullptr || this->raiz == nullptr) {
        return "Medicina General";
    }
    NodoDecision* actual = this->raiz;
    bool primero = true;

    while (actual != nullptr && !actual->getEsHoja()) {
        bool cumple = evaluarRegla(actual->getIdRegla(), p);

        if (!primero) {
            rutaTomada += " -> ";
        }
        primero = false;
        if (cumple) {
            rutaTomada += actual->getTextoSi();
            actual = actual->getSi();
        } else {
            rutaTomada += actual->getTextoNo();
            actual = actual->getNo();
        }
    }

    if (actual != nullptr && actual->getEsHoja()) {
        return actual->getDescripcion();
    }

    return "Medicina General";
}


void ArbolDecision::preordenRecursivo(NodoDecision* nodo) const {
    if (nodo == nullptr) return;

    std::cout << (nodo->getEsHoja() ? "[Servicio: " : "[Regla: ")
    << nodo->getDescripcion() << "] ";

    preordenRecursivo(nodo->getSi());
    preordenRecursivo(nodo->getNo());
}

void ArbolDecision::inordenRecursivo(NodoDecision* nodo) const {
    if (nodo == nullptr) return;

    inordenRecursivo(nodo->getSi());
    std::cout << (nodo->getEsHoja() ? "[Servicio: " : "[Regla: ")
              << nodo->getDescripcion() << "] ";
    inordenRecursivo(nodo->getNo());
}

void ArbolDecision::postordenRecursivo(NodoDecision* nodo) const {
    if (nodo == nullptr) return;

    postordenRecursivo(nodo->getSi());
    postordenRecursivo(nodo->getNo());
    std::cout << (nodo->getEsHoja() ? "[Servicio: " : "[Regla: ")
    << nodo->getDescripcion() << "] ";
}




void ArbolDecision::mostrarPreorden() const {
    std::cout << "Preorden Arbol de Decision:\n";
    preordenRecursivo(this->raiz);
    std::cout << "\n" << std::endl;
}

void ArbolDecision::mostrarInorden() const {
    std::cout << "Inorden Arbol de Decision:\n";
    inordenRecursivo(this->raiz);
    std::cout << "\n" << std::endl;
}

void ArbolDecision::mostrarPostorden() const {
    std::cout << "Postorden Arbol de Decision:\n";
    postordenRecursivo(this->raiz);
    std::cout << "\n" << std::endl;
}