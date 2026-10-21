//
// Created by Matías Collao on 14-09-2026.
//

#ifndef TALLER_1_IM_PERSONA_H
#define TALLER_1_IM_PERSONA_H
#include <string>
#pragma once

class Persona {
protected:
    std::string nombre;
    int edad;
public:
    Persona(std::string nombre, int edad);
    virtual ~Persona();

    void setNombre(std::string nombre);
    void setEdad(int edad);
    std::string getNombre();
    int getEdad();
    virtual void datos();

};



#endif //TALLER_1_IM_PERSONA_H
