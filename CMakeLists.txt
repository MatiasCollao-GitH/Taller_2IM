cmake_minimum_required(VERSION 4.2)
project(Taller_2IM)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller_2IM main.cpp
        estructuras/Stack.h
        logica/Sistema.cpp
        logica/Sistema.h
        estructuras/Nodo.h
        estructuras/Cola.h
        dominio/Persona.cpp
        dominio/Persona.h
        dominio/Paciente.cpp
        dominio/Paciente.h
        dominio/Servicio.cpp
        dominio/Servicio.h
        estructuras/Lista.h
        dominio/Historial.cpp
        dominio/Historial.h
)
