//
// Created by Matías Collao on 16-09-2026.
//

#include "Servicio.h"

Servicio::Servicio(const std::string& nombre) {
    this->nombre = nombre;
    this->arbolPacientes = new AVL();
}

Servicio::~Servicio() {
    delete this->arbolPacientes;
}

std::string Servicio::getNombre() const {
    return this->nombre;
}

AVL* Servicio::getArbolPacientes() {
    return this->arbolPacientes;
}

bool Servicio::agregarPaciente(Paciente* p) {
    return this->arbolPacientes->insertar(p);
}