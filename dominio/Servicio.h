//
// Created by Matías Collao on 16-09-2026.
//

#ifndef TALLER_1_IM_SERVICIO_H
#define TALLER_1_IM_SERVICIO_H

#include "Paciente.h"
#include "../estructuras/AVL.h"

class Servicio {
private:
    std::string nombre;
    AVL* arbolPacientes;

public:
    Servicio(const std::string& nombre);
    ~Servicio();

    std::string getNombre() const;
    AVL* getArbolPacientes();
    bool agregarPaciente(Paciente* p);
};


#endif //TALLER_1_IM_SERVICIO_H
