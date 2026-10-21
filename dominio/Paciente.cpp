#include "Paciente.h"
#include <iostream>
#include <iomanip>

Paciente::Paciente(std::string id, std::string nombre, int edad, double temperatura,
                   int presionArterial, int dolor, std::string tipoDolor,
                   bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
                   int diasHospitalizacion)
    : Persona(nombre, edad),
      id(id),
      temperatura(temperatura),
      presionArterial(presionArterial),
      dolor(dolor),
      tipoDolor(tipoDolor),
      trauma(trauma),
      sintomasNeurologicos(sintomasNeurologicos),
      requiereCirugia(requiereCirugia),
      diasHospitalizacion(diasHospitalizacion),
      servicio("Sin asignar") {
}

Paciente::~Paciente() {
}

std::string Paciente::getId() const {
    return this->id;
}

int Paciente::getIdNumerico() const {
    try {
        return std::stoi(this->id);
    } catch (...) {
        return 0;
    }
}

double Paciente::getTemperatura() const {
    return this->temperatura;
}

int Paciente::getPresionArterial() const {
    return this->presionArterial;
}

int Paciente::getDolor() const {
    return this->dolor;
}

std::string Paciente::getTipoDolor() const {
    return this->tipoDolor;
}

bool Paciente::getTrauma() const {
    return this->trauma;
}

bool Paciente::getSintomasNeurologicos() const {
    return this->sintomasNeurologicos;
}

bool Paciente::getRequiereCirugia() const {
    return this->requiereCirugia;
}

int Paciente::getDiasHospitalizacion() const {
    return this->diasHospitalizacion;
}

std::string Paciente::getServicio() const {
    return this->servicio;
}

void Paciente::setServicio(const std::string& servicio) {
    this->servicio = servicio;
}

// Para opcion 1
void Paciente::datos() {
    std::cout << "ID: " << this->id << "\n"
              << "Nombre: " << this->nombre << "\n"
              << "Edad: " << this->edad << "\n"
              << "Temperatura: " << std::fixed << std::setprecision(1) << this->temperatura << "\n"
              << "PresionArterial: " << this->presionArterial << "\n"
              << "Dolor: " << this->dolor << "\n"
              << "TipoDolor: " << this->tipoDolor << "\n"
              << "Trauma: " << (this->trauma ? 1 : 0) << "\n"
              << "SintomasNeurologicos: " << (this->sintomasNeurologicos ? 1 : 0) << "\n"
              << "RequiereCirugia: " << (this->requiereCirugia ? 1 : 0) << "\n"
              << "DiasHospitalizacion: " << this->diasHospitalizacion << std::endl;
}

//Para opción 2 (Igual, era mejor hacer una entrega por consola más simple, fuck std)
void Paciente::mostrarResumenBusqueda() const {
    std::cout << "-------\n"
              << "ID: " << this->id << "\n"
              << "Nombre: " << this->nombre << "\n"
              << "Edad: " << this->edad << "\n"
              << "Departamento: " << this->servicio << "\n"
              << "T: " << std::fixed << std::setprecision(1) << this->temperatura << "°"
              << " | PA: " << this->presionArterial
              << " | D: " << this->dolor
              << " | TD: " << this->tipoDolor
              << " | T: " << (this->trauma ? "Si" : "No")
              << " | SN: " << (this->sintomasNeurologicos ? "Si" : "No")
              << " | RC: " << (this->requiereCirugia ? "Si" : "No")
              << " | DH: " << (this->diasHospitalizacion > 0 ? std::to_string(this->diasHospitalizacion) : "Ninguno") << "\n"
              << "-------" << std::endl;
}