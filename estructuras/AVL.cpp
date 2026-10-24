//
// Created by ignac on 24/10/2026.
//

#include "AVL.h"
#include <iostream>

AVL::AVL() {
    this->raiz = nullptr;
}

AVL::~AVL() {
    destruirRecursivo(this->raiz);
}

int AVL::altura(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }

    return nodo->getAltura();
}

int AVL::balance(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }

    return altura(nodo->getIzquierdo())
         - altura(nodo->getDerecho());
}

void AVL::actualizarAltura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    int izquierda = altura(nodo->getIzquierdo());
    int derecha = altura(nodo->getDerecho());

    if (izquierda > derecha) {
        nodo->setAltura(izquierda + 1);
    } else {
        nodo->setAltura(derecha + 1);
    }
}

NodoAVL* AVL::rotarDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getIzquierdo();
    NodoAVL* ramaIntermedia = nuevaRaiz->getDerecho();

    nuevaRaiz->setDerecho(nodo);
    nodo->setIzquierdo(ramaIntermedia);

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

NodoAVL* AVL::rotarIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getDerecho();
    NodoAVL* ramaIntermedia = nuevaRaiz->getIzquierdo();

    nuevaRaiz->setIzquierdo(nodo);
    nodo->setDerecho(ramaIntermedia);

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

NodoAVL* AVL::balancear(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    actualizarAltura(nodo);

    int factor = balance(nodo);

    if (factor > 1) {
        if (balance(nodo->getIzquierdo()) < 0) {
            nodo->setIzquierdo(
                rotarIzquierda(nodo->getIzquierdo())
            );
        }

        return rotarDerecha(nodo);
    }

    if (factor < -1) {
        if (balance(nodo->getDerecho()) > 0) {
            nodo->setDerecho(
                rotarDerecha(nodo->getDerecho())
            );
        }

        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* AVL::insertarRecursivo(
    NodoAVL* nodo,
    Paciente* paciente
) {
    if (nodo == nullptr) {
        return new NodoAVL(paciente);
    }

    const std::string id = paciente->getId();
    const std::string idActual = nodo->getPaciente()->getId();

    if (id < idActual) {
        nodo->setIzquierdo(
            insertarRecursivo(nodo->getIzquierdo(), paciente)
        );
    } else if (id > idActual) {
        nodo->setDerecho(
            insertarRecursivo(nodo->getDerecho(), paciente)
        );
    } else {
        return nodo;
    }

    return balancear(nodo);
}

bool AVL::insertar(Paciente* paciente) {
    if (paciente == nullptr) {
        return false;
    }

    if (buscarID(paciente->getId()) != nullptr) {
        return false;
    }

    this->raiz = insertarRecursivo(this->raiz, paciente);
    return true;
}

NodoAVL* AVL::minimo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    while (nodo->getIzquierdo() != nullptr) {
        nodo = nodo->getIzquierdo();
    }

    return nodo;
}

NodoAVL* AVL::eliminarRecursivo(
    NodoAVL* nodo,
    const std::string& id
) {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string idActual = nodo->getPaciente()->getId();

    if (id < idActual) {
        nodo->setIzquierdo(
            eliminarRecursivo(nodo->getIzquierdo(), id)
        );
    } else if (id > idActual) {
        nodo->setDerecho(
            eliminarRecursivo(nodo->getDerecho(), id)
        );
    } else {
        if (nodo->getIzquierdo() == nullptr) {
            NodoAVL* hijo = nodo->getDerecho();

            delete nodo->getPaciente();
            delete nodo;

            return hijo;
        }

        if (nodo->getDerecho() == nullptr) {
            NodoAVL* hijo = nodo->getIzquierdo();

            delete nodo->getPaciente();
            delete nodo;

            return hijo;
        }

        NodoAVL* sucesor = minimo(nodo->getDerecho());

        Paciente* pacienteEliminar = nodo->getPaciente();

        nodo->setPaciente(sucesor->getPaciente());
        sucesor->setPaciente(pacienteEliminar);

        nodo->setDerecho(
            eliminarRecursivo(nodo->getDerecho(), idActual)
        );
    }

    return balancear(nodo);
}

bool AVL::eliminar(const std::string& id) {
    const std::string idBuscado = id;

    if (buscarID(idBuscado) == nullptr) {
        return false;
    }

    this->raiz = eliminarRecursivo(this->raiz, idBuscado);
    return true;
}

Paciente* AVL::buscarIDRecursivo(
    NodoAVL* nodo,
    const std::string& id
) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string idActual = nodo->getPaciente()->getId();

    if (id == idActual) {
        return nodo->getPaciente();
    }

    if (id < idActual) {
        return buscarIDRecursivo(nodo->getIzquierdo(), id);
    }

    return buscarIDRecursivo(nodo->getDerecho(), id);
}

Paciente* AVL::buscarID(const std::string& id) const {
    return buscarIDRecursivo(this->raiz, id);
}

void AVL::buscarNombreRecursivo(
    NodoAVL* nodo,
    const std::string& nombre,
    bool& encontrado
) const {
    if (nodo == nullptr) {
        return;
    }

    buscarNombreRecursivo(
        nodo->getIzquierdo(), nombre, encontrado
    );

    if (nodo->getPaciente()->getNombre() == nombre) {
        nodo->getPaciente()->mostrarResumenBusqueda();
        encontrado = true;
    }

    buscarNombreRecursivo(
        nodo->getDerecho(), nombre, encontrado
    );
}

bool AVL::buscarNombre(const std::string& nombre) const {
    bool encontrado = false;

    buscarNombreRecursivo(this->raiz, nombre, encontrado);

    return encontrado;
}

bool AVL::isEmpty() const {
    return this->raiz == nullptr;
}

int AVL::getAltura() const {
    return altura(this->raiz);
}

void AVL::inordenRecursivo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    inordenRecursivo(nodo->getIzquierdo());

    std::cout << nodo->getPaciente()->getId() << " - "
              << nodo->getPaciente()->getNombre() << "\n";

    inordenRecursivo(nodo->getDerecho());
}

void AVL::preordenRecursivo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    std::cout << nodo->getPaciente()->getId() << " - "
              << nodo->getPaciente()->getNombre() << "\n";

    preordenRecursivo(nodo->getIzquierdo());
    preordenRecursivo(nodo->getDerecho());
}

void AVL::postordenRecursivo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    postordenRecursivo(nodo->getIzquierdo());
    postordenRecursivo(nodo->getDerecho());

    std::cout << nodo->getPaciente()->getId() << " - "
              << nodo->getPaciente()->getNombre() << "\n";
}

void AVL::mostrarInorden() const {
    inordenRecursivo(this->raiz);
}

void AVL::mostrarPreorden() const {
    preordenRecursivo(this->raiz);
}

void AVL::mostrarPostorden() const {
    postordenRecursivo(this->raiz);
}

void AVL::mostrarBalancesRecursivo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    mostrarBalancesRecursivo(nodo->getIzquierdo());

    std::cout << "ID: " << nodo->getPaciente()->getId()
              << " | Altura: " << nodo->getAltura()
              << " | Balance: " << balance(nodo) << "\n";

    mostrarBalancesRecursivo(nodo->getDerecho());
}

void AVL::mostrarBalances() const {
    mostrarBalancesRecursivo(this->raiz);
}

void AVL::destruirRecursivo(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    destruirRecursivo(nodo->getIzquierdo());
    destruirRecursivo(nodo->getDerecho());

    delete nodo->getPaciente();
    delete nodo;
}
