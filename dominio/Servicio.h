//
// Created by Matías Collao on 16-09-2026.
//

#ifndef TALLER_1_IM_SERVICIO_H
#define TALLER_1_IM_SERVICIO_H

#include "Paciente.h"
#include "../estructuras/Lista.h"


class Servicio {
private:
    std::string nombre;
    Lista<Paciente*>* listaPacientes;

public:
    Servicio(const std::string& nombre);
    ~Servicio();

    std::string getNombre() const;
    Lista<Paciente*>* getListaPacientes();
    void agregarPaciente(Paciente* p);
};


#endif //TALLER_1_IM_SERVICIO_H
