//
// Created by Matías Collao on 14-09-2026.
//

#ifndef TALLER_1_IM_SISTEMA_H
#define TALLER_1_IM_SISTEMA_H
#include <string>

#include "../estructuras/Cola.h"
#include "../estructuras/Lista.h"
#include "../dominio/Paciente.h"
#include "../dominio/Servicio.h"
#include "../dominio/Historial.h"

class Sistema {
private:
    Cola<Paciente*>* colaEspera;
    Lista<Servicio*>* listaServicios;
    Historial* historial;
public:
    void iniciar();

    void imprimirColaSINEliminar(Nodo<Paciente *> *cola);

    void leer();
    void menu();

    void revisarHistorial();
    void verDepartamento();
    void atenderPacientes();

    Servicio* buscarServicio(std::string nombre);

    ~Sistema();

    void inicializarServicios();

    //Terminar
    bool esServicioValido(std::string(servicio));
    //------------------------------

    //tambien terminar
    bool existePaciente(std::string(id));



};



#endif //TALLER_1_IM_SISTEMA_H
