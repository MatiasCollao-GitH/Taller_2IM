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
    this->arbolDecision = new ArbolDecision();

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
        Paciente* paciente = actual->getValor();

        if (paciente != nullptr && paciente->getId() == id) {
            return true;
        }

        actual = actual->getNext();
    }

    Nodo<Servicio*>* servicioActual =
        this->listaServicios->getCabeza();

    while (servicioActual != nullptr) {
        Servicio* servicio = servicioActual->getValor();

        if (servicio->getArbolPacientes()->buscarID(id) != nullptr) {
            return true;
        }

        servicioActual = servicioActual->getNext();
    }

    return false;
}

void Sistema::leer() {
    ifstream archivo("pacientes.txt");

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir pacientes.txt" << endl;
        return;
    }

    auto limpiar = [](string texto) -> string {
        size_t inicio = texto.find_first_not_of(" \t\r\n");

        if (inicio == string::npos) {
            return "";
        }

        size_t fin = texto.find_last_not_of(" \t\r\n");
        return texto.substr(inicio, fin - inicio + 1);
    };

    auto convertirEntero = [](const string& texto) -> int {
        size_t posicion;
        int valor = stoi(texto, &posicion);

        if (posicion != texto.size()) {
            throw invalid_argument("Numero entero incompleto");
        }

        return valor;
    };

    auto convertirDecimal = [](const string& texto) -> double {
        size_t posicion;
        double valor = stod(texto, &posicion);

        if (posicion != texto.size() || !std::isfinite(valor)) {
            throw invalid_argument("Numero decimal invalido");
        }

        return valor;
    };

    string linea;
    int numeroLinea = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (limpiar(linea).empty()) {
            continue;
        }

        try {
            int separadores = 0;

            for (char caracter : linea) {
                if (caracter == ';') {
                    separadores++;
                }
            }

            if (separadores != 10) {
                throw invalid_argument(
                    "Se requieren exactamente 11 campos"
                );
            }

            string campos[11];
            stringstream ss(linea);

            for (int i = 0; i < 11; i++) {
                if (!getline(ss, campos[i], ';')) {
                    throw invalid_argument("Faltan campos");
                }

                campos[i] = limpiar(campos[i]);

                if (campos[i].empty()) {
                    throw invalid_argument("Hay campos vacios");
                }
            }

            string id = campos[0];
            string nombre = campos[1];
            int edad = convertirEntero(campos[2]);
            double temperatura = convertirDecimal(campos[3]);
            int presion = convertirEntero(campos[4]);
            int dolor = convertirEntero(campos[5]);
            string tipoDolor = campos[6];
            int trauma = convertirEntero(campos[7]);
            int sintomas = convertirEntero(campos[8]);
            int cirugia = convertirEntero(campos[9]);
            int dias = convertirEntero(campos[10]);

            if (edad < 0 || edad > 130) {
                throw invalid_argument("Edad fuera de rango");
            }

            if (temperatura < 25 || temperatura > 45) {
                throw invalid_argument("Temperatura fuera de rango");
            }

            if (presion <= 0 || presion > 300) {
                throw invalid_argument("Presion fuera de rango");
            }

            if (dolor < 0 || dolor > 10) {
                throw invalid_argument("Dolor debe estar entre 0 y 10");
            }

            if ((trauma != 0 && trauma != 1) ||
                (sintomas != 0 && sintomas != 1) ||
                (cirugia != 0 && cirugia != 1)) {
                throw invalid_argument(
                    "Trauma, sintomas y cirugia deben ser 0 o 1"
                );
            }

            if (dias < 0) {
                throw invalid_argument(
                    "Dias de hospitalizacion no puede ser negativo"
                );
            }

            if (tipoDolor != "pecho" &&
                tipoDolor != "cabeza" &&
                tipoDolor != "abdomen" &&
                tipoDolor != "extremidad" &&
                tipoDolor != "otro") {
                throw invalid_argument("Tipo de dolor invalido");
            }

            if (existePaciente(id)) {
                throw invalid_argument("ID duplicado: " + id);
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

            try {
                this->colaEspera->push(nuevo);
            } catch (...) {
                delete nuevo;
                throw;
            }

        } catch (const std::exception& e) {
            cerr << "Error en linea " << numeroLinea
                 << ": " << e.what() << endl;
        }
    }
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
        string ruta;
        string servicioAsignado =
            this->arbolDecision->evaluarPaciente(paciente, ruta);

        Servicio* servicio = buscarServicio(servicioAsignado);

        if (servicio == nullptr) {
            cout << "Error: No se encontró el servicio del paciente." << endl;
            break;
        }

        paciente->setServicio(servicioAsignado);

        cout << "=== ATENDIENDO PACIENTES ===" << endl;

        //Enviamos al paciente al servicio
        if (!servicio->agregarPaciente(paciente)) {
            cout << "Error: No se pudo insertar el paciente en el servicio."
                 << endl;
            break;
        }

        //Registramos atención en el hospital
        this->historial->registrarAtencion(paciente);

        //Lo eliminamos de la cola de espera
        this->colaEspera->pop();

        cout << "Ruta: " << ruta << endl;

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

    if (opcion < 1 || opcion > this->listaServicios->getTamano()) {
        cout << "Departamento invalido" << endl;
        return;
    }

    actual = this->listaServicios->getCabeza();

    for (int i = 1; i < opcion; i++) {
        actual = actual->getNext();
    }

    Servicio* servicio = actual->getValor();
    AVL* pacientes = servicio->getArbolPacientes();

    cout << "\n=== ESTADO " << servicio->getNombre()
         << " ===" << endl;

    if (pacientes->isEmpty()) {
        cout << "No hay pacientes en este departamento" << endl;
        return;
    }

    int consulta;

    while (true) {
        cout << "\n=== CONSULTAS DEL AVL ===\n"
                "1. Mostrar inorden\n"
                "2. Mostrar preorden\n"
                "3. Mostrar postorden\n"
                "4. Mostrar altura\n"
                "5. Mostrar alturas y balances por nodo\n"
                "6. Volver al menu principal\n"
                "Seleccione opcion: ";

        cin >> consulta;

        if (cin.eof()) {
            return;
        }

        if (cin.fail()) {
            cout << "Opcion invalida" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (consulta == 1) {
            cout << "\nInorden:\n";
            pacientes->mostrarInorden();
        } else if (consulta == 2) {
            cout << "\nPreorden:\n";
            pacientes->mostrarPreorden();
        } else if (consulta == 3) {
            cout << "\nPostorden:\n";
            pacientes->mostrarPostorden();
        } else if (consulta == 4) {
            cout << "Altura del AVL: "
                 << pacientes->getAltura() << endl;
        } else if (consulta == 5) {
            pacientes->mostrarBalances();
        } else if (consulta == 6) {
            return;
        } else {
            cout << "Opcion invalida" << endl;
        }
    }
}

void Sistema::buscarPaciente() {
    int opcion;

    cout << "\n=== BUSCAR PACIENTE ===\n";
    cout << "1. Buscar por ID\n";
    cout << "2. Buscar por nombre\n";
    cout << "Seleccione opcion: ";
    cin >> opcion;

    if (cin.fail() || opcion < 1 || opcion > 2) {
        cout << "Opcion invalida" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    cin.ignore(10000, '\n');

    string dato;
    cout << "Ingrese " << (opcion == 1 ? "ID: " : "nombre: ");
    getline(cin, dato);

    if (dato.find_first_not_of(" \t\r") == string::npos) {
        cout << "Debe ingresar un dato de busqueda." << endl;
        return;
    }

    bool encontrado = false;
    Nodo<Servicio*>* actual = this->listaServicios->getCabeza();

    while (actual != nullptr) {
        AVL* pacientes = actual->getValor()->getArbolPacientes();

        if (opcion == 1) {
            Paciente* paciente = pacientes->buscarID(dato);

            if (paciente != nullptr) {
                paciente->mostrarResumenBusqueda();
                encontrado = true;
                break;
            }
        } else {
            if (pacientes->buscarNombre(dato)) {
                encontrado = true;
            }
        }

        actual = actual->getNext();
    }

    if (!encontrado) {
        cout << "No se encontraron pacientes en los servicios."
             << endl;
    }
}

void Sistema::eliminarPaciente() {
    cin.ignore(10000, '\n');

    string id;

    cout << "\n=== ELIMINAR PACIENTE ===\n";
    cout << "Ingrese ID: ";
    getline(cin, id);

    if (id.find_first_not_of(" \t\r") == string::npos) {
        cout << "Debe ingresar un ID." << endl;
        return;
    }

    Nodo<Servicio*>* actual = this->listaServicios->getCabeza();

    while (actual != nullptr) {
        Servicio* servicio = actual->getValor();

        if (servicio->getArbolPacientes()->eliminar(id)) {
            cout << "Paciente " << id
                 << " eliminado de " << servicio->getNombre()
                 << "." << endl;
            return;
        }

        actual = actual->getNext();
    }

    cout << "No se encontro el paciente en los servicios." << endl;
}

void Sistema::verRecorridosDecision() {
    int opcion;

    while (true) {
        cout << "\n=== ARBOL DE DECISION ===\n"
                "1. Mostrar preorden\n"
                "2. Mostrar inorden\n"
                "3. Mostrar postorden\n"
                "4. Volver al menu principal\n"
                "Seleccione opcion: ";

        cin >> opcion;

        if (cin.eof()) {
            return;
        }

        if (cin.fail()) {
            cout << "Opcion invalida" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (opcion == 1) {
            this->arbolDecision->mostrarPreorden();
        } else if (opcion == 2) {
            this->arbolDecision->mostrarInorden();
        } else if (opcion == 3) {
            this->arbolDecision->mostrarPostorden();
        } else if (opcion == 4) {
            return;
        } else {
            cout << "Opcion invalida" << endl;
        }
    }
}

void Sistema::menu() {

    int opcion = 0;

    while (true) {
        cout << "=== HOSPITAL MARMAJA ===\n"
                "1. Atender pacientes\n"
                "2. Ver departamento\n"
                "3. Revisar historial de atencion\n"
                "4. Buscar paciente\n"
                "5. Eliminar paciente por ID\n"
                "6. Ver recorridos del arbol de decision\n"
                "7. Salir\n"
                "\nSeleccionar opcion: " << endl;
        cin >> opcion;
        if (cin.eof()) {
            break;
        }
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
            buscarPaciente();
        } else if (opcion == 5) {
            eliminarPaciente();
        } else if (opcion == 6) {
            verRecorridosDecision();
        } else if (opcion == 7) {
            cout << "Hasta luego :D." << endl;
            break;
        } else {
            cout << "Opcion invalida. Seleccione entre 1 y 7." << endl;
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
    delete this->arbolDecision;
}







