#ifndef TALLER_1_IM_HISTORIAL_H
#define TALLER_1_IM_HISTORIAL_H

#include "Paciente.h"
#include "../estructuras/Stack.h"

class Historial {

    private:
    Stack<Paciente*>* pilaAtenciones;

public:
    Historial();

    void registrarAtencion(Paciente* paciente);
    void mostrarHistorial();
    bool isEmpty();

    ~Historial();
};


#endif //TALLER_1_IM_HISTORIAL_H
