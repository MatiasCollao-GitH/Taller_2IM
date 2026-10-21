//
// Created by Matías Collao on 14-09-2026.
//

#include "Persona.h"

#include <iostream>

Persona::Persona(std::string nombre, int edad) {
    this->nombre = nombre;
    this->edad = edad;
}

int Persona::getEdad() {
    return this->edad;
}

std::string Persona::getNombre() {
    return this->nombre;
}

void Persona::setEdad(int edad) {
    this->edad = edad;
}

void Persona::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Persona::datos() {
    std::cout << "Nombre: " << this->nombre
        << " Edad: " << this->edad << std::endl;
}

Persona::~Persona() {
}

