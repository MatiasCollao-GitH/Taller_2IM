#ifndef TALLER_1_IM_PACIENTE_H
#define TALLER_1_IM_PACIENTE_H

#pragma once
#include "Persona.h"
#include <string>

class Paciente : public Persona {
private:
    std::string id;
    double temperatura;
    int presionArterial;
    int dolor;
    std::string tipoDolor;
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;
    std::string servicio;

public:
    Paciente(std::string id, std::string nombre, int edad, double temperatura,
             int presionArterial, int dolor, std::string tipoDolor,
             bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
             int diasHospitalizacion);

    ~Paciente() override;

    std::string getId() const;
    int getIdNumerico() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    std::string getTipoDolor() const;

    bool getTrauma() const;
    bool getSintomasNeurologicos() const;

    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
    std::string getServicio() const;
    void setServicio(const std::string& servicio);

    // ver
    void datos() override;
    void mostrarResumenBusqueda() const;
};

#endif //TALLER_1_IM_PACIENTE_H
