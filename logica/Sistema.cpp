//
// Created by Matías Collao on 14-09-2026.
//

#include "Sistema.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../estructuras/Nodo.h"
#include "../dominio/Paciente.h"
#include "../dominio/Servicio.h"

#include <cmath>
#include <stdexcept>
#include <exception>
using namespace std;

void Sistema::iniciar() {
    colaEspera = new Cola<Paciente*>();
    this->historial = new Historial();

    inicializarServicios();
    leer();
    menu();
}

void Sistema::inicializarServicios() {
    this->listaServicios = new Lista<Servicio*>();

    const std::string serviciosBase[8] = {
        "Urgencias", "Medicina General", "Cardiologia", "Neurologia",
        "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"
    };

    const std::string* ptr = serviciosBase;
    for (int i = 0; i < 8; ++i) {
        this->listaServicios->agregarFinal(new Servicio(*(ptr + i)));
    }
}




bool Sistema::esServicioValido(std::string servicio) {
    Nodo<Servicio*>* actual = this->listaServicios->getCabeza();
    while (actual != nullptr) {
        if (actual->getValor()->getNombre() == servicio) {
            return true;
        }
        actual = actual->getNext();
    }
    return false;
}

Servicio* Sistema::buscarServicio(std::string nombre) {

    Nodo<Servicio*>* actual = this->listaServicios->getCabeza();

    while (actual != nullptr) {

        Servicio*  servicio = actual->getValor();

        if (servicio->getNombre() == nombre) {
            return servicio;
        }
        actual = actual->getNext();
    }
    return nullptr;
}

bool Sistema::existePaciente(std::string id) {
    Nodo<Paciente*>* actual = this->colaEspera->getInicio();
    while (actual != nullptr) {
        Paciente* p = actual->getValor();
        if (p != nullptr && p->getId() == id) {
            return true;
        }
        actual = actual->getNext();
    }

    return false;
}

void Sistema::leer() {
    ifstream archivo("pacientes.txt");

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo pacientes.txt" << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string id, nombre, stringEdad;
        string stringTemperatura, stringPresion, stringDolor;
        string tipoDolor, stringTrauma, stringSintomas;
        string stringCirugia, stringDias;

        if (getline(ss, id, ';') &&
            getline(ss, nombre, ';') &&
            getline(ss, stringEdad, ';') &&
            getline(ss, stringTemperatura, ';') &&
            getline(ss, stringPresion, ';') &&
            getline(ss, stringDolor, ';') &&
            getline(ss, tipoDolor, ';') &&
            getline(ss, stringTrauma, ';') &&
            getline(ss, stringSintomas, ';') &&
            getline(ss, stringCirugia, ';') &&
            getline(ss, stringDias)) {

            try {
                int edad = stoi(stringEdad);
                double temperatura = stod(stringTemperatura);
                int presion = stoi(stringPresion);
                int dolor = stoi(stringDolor);
                int trauma = stoi(stringTrauma);
                int sintomas = stoi(stringSintomas);
                int cirugia = stoi(stringCirugia);
                int dias = stoi(stringDias);

                if (existePaciente(id)) {
                    cerr << "Error: Paciente con ID duplicado ("
                         << id << ")" << endl;
                    continue;
                }

                Paciente* nuevo = new Paciente(
                    id,
                    nombre,
                    edad,
                    temperatura,
                    presion,
                    dolor,
                    tipoDolor,
                    trauma == 1,
                    sintomas == 1,
                    cirugia == 1,
                    dias
                );

                colaEspera->push(nuevo);

            } catch (const std::exception& e) {
                cerr << "Error: Dato numerico invalido o fuera de rango"
                     << endl;
            }

        } else {
            cerr << "Error: Formato de linea invalido" << endl;
        }
    }

    archivo.close();
}

void Sistema::revisarHistorial() {
    this->historial->mostrarHistorial();
}

void Sistema::atenderPacientes() {
    if (this->colaEspera->size() == 0) {
        cout << "No hay pacientes en espera." << endl;
        return;
    }
    int cantidad;

    this->colaEspera->imprimir();

    cout << "Cantidad de pacientes a atender: ";
    cin >> cantidad;
    cout << endl;

    //Validar cantidad
    if (cin.fail() || cantidad <= 0) {
        cout << "Cantidad invalida" << endl;

        cin.clear();
        cin.ignore(10000, '\n');

        return;
    }
    for (int i = 0; i < cantidad; i++) {

        //Si se acabaron los pacientes antes de llegar a la cantidad
        if (this->colaEspera->size() == 0) {
            cout << "No quedan más pacientes en espera" << endl;
            break;
        }
        //Obtenemos el paciente del frente de la cola
        Paciente* paciente = this->colaEspera->front();

        //Buscamos el servicio que corresponda
        Servicio* servicio = buscarServicio(paciente->getServicio());

        if (servicio == nullptr) {
            cout << "Error: No se encontró el servicio del paciente." << endl;
            break;
        }

        cout << "=== ATENDIENDO PACIENTES ===" << endl;

        //Enviamos al paciente al servicio
        servicio->agregarPaciente(paciente);

        //Registramos atención en el hospital
        this->historial->registrarAtencion(paciente);

        //Lo eliminamos de la cola de espera
        this->colaEspera->pop();

        cout << "ID: " << paciente->getId() << "\nNombre: " << paciente->getNombre() << "\nEdad: " <<
            paciente->getEdad() << "\nServicio: " << paciente->getServicio() << "\n" << endl;

        cout << "Paciente enviado a " << paciente->getServicio() << ".\n" << endl;
    }
}

void Sistema::verDepartamento() {

    cout << "=== DEPARTAMENTOS/SERVICIOS ===" << endl;

    Nodo<Servicio*>* actual = this->listaServicios->getCabeza();

    int numero = 1;

    while (actual != nullptr) {
        cout << numero << ". "
             << actual->getValor()->getNombre()
             << endl;

        actual = actual->getNext();
        numero++;
    }
    int opcion;

    cout << "\nSeleccione departamento: ";
    cin >> opcion;

    if (cin.fail()) {
        cout << "Opcion invalida" << endl;

        cin.clear();
        cin.ignore(10000, '\n');

        return;
    }

    //Ver si existe el departamento
    if (opcion < 1 || opcion > this->listaServicios->getTamano()) {
        cout << "Departamento invalido" << endl;
        return;
    }

    actual = this->listaServicios->getCabeza();

    //Avanzamos hasta el departamento elegido
    for (int i = 1; i < opcion; i++) {
        actual = actual->getNext();
    }
    Servicio* servicio = actual->getValor();

    cout << "\n=== ESTADO " << servicio->getNombre() << " ===" << endl;

    Lista<Paciente*>* pacientes = servicio->getListaPacientes();

    //Ver si el departamento tiene pacientes
    if (pacientes->isEmpty()) {
        cout << "No hay pacientes en este departamento" << endl;
        return;
    }
    cout << "Pacientes en el departamento de " << servicio->getNombre() << " : " << servicio->getListaPacientes()->getTamano() << endl;


    Nodo<Paciente*>* pacienteActual = pacientes->getCabeza();

    while (pacienteActual != nullptr) {
        Paciente* paciente = pacienteActual->getValor();

        if (paciente != nullptr) {
            cout << paciente->getNombre() << "(" << paciente->getEdad() << ")" << endl;
        }
        pacienteActual = pacienteActual->getNext();

    }
    cout << endl;


}

void Sistema::menu() {

    int opcion = 0;

    while (true) {
        cout << "=== HOSPITAL MARMAJA ===\n"
                "1. Atender pacientes\n"
                "2. Ver departamento\n"
                "3. Revisar historial de atencion\n"
                "4. Salir\n"
                "\nSeleccionar opcion: " << endl;
        cin >> opcion;
    if (cin.fail()) {
        cout << "Error: Opcion desconocida, intente nuevamente: " << endl;
        opcion = 0;
        cin.clear();
        cin.ignore(10000, '\n');
        }else if (opcion == 1) {
            atenderPacientes();
        } else if (opcion == 2) {
            verDepartamento();
        } else if (opcion == 3) {
            revisarHistorial();
        } else if (opcion == 4) {
            cout << "Hasta luego :D." << endl;
            break;
        }
    }

}
Sistema::~Sistema() {
    if (this->colaEspera != nullptr) {
        while (!this->colaEspera->isEmpty()) {
            Paciente* p = this->colaEspera->front();
            this->colaEspera->pop();
            delete p;
        }
        delete this->colaEspera;
    }
    delete this->historial;

    if (this->listaServicios != nullptr) {
        Nodo<Servicio*>* actual = this->listaServicios->getCabeza();
        while (actual != nullptr) {
            delete actual->getValor();
            actual = actual->getNext();
        }
        delete this->listaServicios;
    }
}







