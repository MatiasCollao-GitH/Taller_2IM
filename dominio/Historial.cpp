#include "Historial.h"

#include <iostream>

Historial::Historial() {
    this->pilaAtenciones = new Stack<Paciente*>();
}

void Historial::registrarAtencion(Paciente* paciente) {
    if (paciente == nullptr) {
        return;
    }

    Paciente* copia = new Paciente(
        paciente->getId(),
        paciente->getNombre(),
        paciente->getEdad(),
        paciente->getTemperatura(),
        paciente->getPresionArterial(),
        paciente->getDolor(),
        paciente->getTipoDolor(),
        paciente->getTrauma(),
        paciente->getSintomasNeurologicos(),
        paciente->getRequiereCirugia(),
        paciente->getDiasHospitalizacion()
    );

    copia->setServicio(paciente->getServicio());

    this->pilaAtenciones->push(copia);
}

bool Historial::isEmpty() {
    return this->pilaAtenciones->isEmpty();
}

void Historial::mostrarHistorial() {
    if (this->pilaAtenciones->isEmpty()) {
        std::cout << "No hay atenciones registradas." << std::endl;
        return;
    }
    Nodo<Paciente*>* nodo = this->pilaAtenciones->getHead();

    std::cout << "=== HISTORIAL DE ÚLTIMAS ATENCIONES DEL HOSPITAL ===" << std::endl;

    while (nodo != nullptr) {
        Paciente* paciente = nodo->getValor();

        if (paciente != nullptr) {
            std::cout << "Nombre: " << paciente->getNombre() << " | Edad: " << paciente->getEdad() <<
                " | Departamento: " << paciente->getServicio() << std::endl;
        }
        nodo = nodo->getNext();
    }
}

Historial::~Historial() {
    while (!this->pilaAtenciones->isEmpty()) {
        Paciente* copia = this->pilaAtenciones->getHead()->getValor();
        this->pilaAtenciones->pop();
        delete copia;
    }

    delete this->pilaAtenciones;
}