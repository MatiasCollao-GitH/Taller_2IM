//
// Created by Matías Collao on 16-09-2026.
//

#include "Servicio.h"

Servicio::Servicio(const std::string& nombre) {
    this->nombre = nombre;
    this->listaPacientes = new Lista<Paciente*>();
}

Servicio::~Servicio() {
    if (this->listaPacientes != nullptr) {
        Nodo<Paciente*>* actual = this->listaPacientes->getCabeza();
        while (actual != nullptr) {
            delete actual->getValor();
            actual = actual->getNext();
        }
        delete this->listaPacientes;
    }
}

std::string Servicio::getNombre() const {
    return this->nombre;
}

Lista<Paciente*>* Servicio::getListaPacientes() {
    return this->listaPacientes;
}

void Servicio::agregarPaciente(Paciente* p) {
    this->listaPacientes->agregarFinal(p);
}