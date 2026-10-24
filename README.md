# Taller 02: Estructura de Datos – Hospital Marmaja

Sistema en C++ para clasificar automáticamente pacientes mediante un árbol de decisión y almacenarlos en árboles AVL según el servicio asignado.

El proyecto extiende el Taller 1, conservando la cola de espera, la lista enlazada de servicios, el historial de atenciones, la programación orientada a objetos y la gestión dinámica de memoria. Las estructuras de datos se implementan manualmente mediante nodos y punteros, sin utilizar contenedores de la STL para reemplazarlas.

---

## Integrantes

* **Nombre:** Matías Collao | **RUT:** 22.060.152-8 | **Usuario GitHub:** [MatiasCollao-GitH](https://github.com/MatiasCollao-GitH) | **Carrera:** Ingeniería Civil en Computación e Informática | **Paralelo:** C2
* **Nombre:** Ignacio Pastén | **RUT:** 22.067.577-7 | **Usuario GitHub:** [Tallarin51](https://github.com/Tallarin51) | **Carrera:** Ingeniería Civil en Computación e Informática | **Paralelo:** C2

---

## Flujo General

1. Se leen y validan los registros de `pacientes.txt`.
2. Los pacientes válidos ingresan a la cola en el orden del archivo.
3. Al atenderlos, el árbol de decisión determina su servicio.
4. Cada paciente se incorpora al AVL del servicio correspondiente.
5. Se registra una copia independiente en el historial.
6. Se retira al paciente de la cola y se informa la ruta de clasificación y el servicio asignado.

La atención respeta el orden FIFO de la cola.

---

## Estructuras de Datos y Decisiones Técnicas

El proyecto no utiliza `std::vector`, `std::list`, `std::queue`, `std::stack` ni otros contenedores para reemplazar las estructuras solicitadas. Sí utiliza herramientas de la biblioteca estándar, como `std::string`, flujos de entrada y salida y conversiones numéricas.

### 1. Cola de Espera (`Cola<T>`)

* Implementación enlazada manual con comportamiento FIFO.
* Conserva el orden de llegada de los pacientes.
* Permite insertar al final mediante `push`, consultar el frente mediante `front` y retirar el primer nodo mediante `pop`.
* Los pacientes permanecen en espera hasta que se complete su derivación al servicio.

### 2. Lista Enlazada de Servicios (`Lista<T>`)

* Mantiene los ocho servicios fijos del hospital.
* Cada nodo contiene un puntero a un objeto `Servicio`.
* Cada servicio administra su propio AVL de pacientes, reemplazando las sublistas utilizadas en el Taller 1.

Servicios disponibles:

* Urgencias.
* Medicina General.
* Cardiología.
* Neurología.
* Traumatología.
* Cirugía.
* Pediatría.
* Hospitalización.

En el código, los nombres de los servicios se almacenan sin tildes para mantener consistencia entre la clasificación y la búsqueda del servicio.

### 3. Árbol de Decisión (`ArbolDecision`)

* Árbol binario implementado manualmente mediante `NodoDecision`.
* Los nodos internos contienen reglas sobre los atributos del paciente.
* Cada regla tiene una rama Sí y una rama No.
* Las hojas contienen el nombre del servicio resultante.
* La evaluación acumula los textos de las ramas recorridas para mostrar la ruta tomada.
* Permite recorridos preorden, inorden y postorden, considerando Sí como rama izquierda y No como rama derecha.
* Antes de reconstruir el árbol, se libera la estructura anterior.

### 4. Árbol AVL por Servicio (`AVL`)

* Cada servicio tiene una instancia independiente de `AVL`.
* Cada nodo almacena un paciente, sus hijos y su altura.
* El ID es la clave de ordenamiento.
* Los IDs se comparan como cadenas de texto. Por ejemplo, `001`, `002` y `010` mantienen el orden esperado cuando tienen la misma longitud.
* Se rechazan IDs duplicados dentro del árbol.
* Implementa rotaciones simples a izquierda y derecha y rotaciones dobles izquierda-derecha y derecha-izquierda.
* El factor de balance se calcula como altura izquierda menos altura derecha.
* La inserción y eliminación actualizan las alturas y restauran el balance.

Operaciones disponibles:

* Insertar pacientes.
* Buscar por ID.
* Buscar por nombre exacto, mostrando todas las coincidencias.
* Eliminar por ID.
* Mostrar recorridos inorden, preorden y postorden.
* Consultar la altura del árbol.
* Mostrar la altura y el factor de balance de cada nodo.

La búsqueda por nombre distingue mayúsculas y minúsculas y recorre el árbol completo, porque su ordenamiento se basa en el ID.

### 5. Historial de Atenciones (`Stack<T>`)

* Pila enlazada manual con comportamiento LIFO.
* Muestra las atenciones desde la más reciente hasta la más antigua.
* Cada atención almacena una copia independiente del paciente y del servicio asignado.
* Eliminar al paciente de su AVL no elimina su registro histórico.
* El historial libera sus copias al destruirse.

### 6. Programación Orientada a Objetos

* `Persona` contiene los atributos comunes `nombre` y `edad`.
* `Paciente` hereda de `Persona` e incorpora el ID, los atributos utilizados en la clasificación y el servicio asignado.
* El método virtual `datos()` permite mostrar la información del paciente mediante polimorfismo.
* `Sistema` coordina la lectura, atención, clasificación y consultas.
* `Servicio` administra el AVL de su departamento.
* `Historial` administra las copias de las atenciones registradas.

### 7. Aritmética de Punteros

Se utiliza en `Sistema::inicializarServicios()` para recorrer el arreglo de nombres e inicializar los ocho servicios mediante un puntero `const std::string*` y expresiones como `*(ptr + i)`.

---

## Criterios del Árbol de Decisión

Los criterios corresponden a una simplificación académica y no constituyen un protocolo clínico.

Las reglas se evalúan en el siguiente orden. Cuando se alcanza un servicio, termina la clasificación.

| Orden | Condición | Resultado |
|---|---|---|
| 1 | Edad menor de 14 años | Pediatría |
| 2 | Tiene trauma y requiere cirugía | Cirugía |
| 3 | Tiene trauma y no requiere cirugía | Traumatología |
| 4 | Sin trauma y con síntomas neurológicos | Neurología |
| 5 | Supera las reglas anteriores y presenta dolor de pecho o presión arterial mayor o igual a 140 | Cardiología |
| 6 | Supera las reglas anteriores y presenta temperatura mayor o igual a 38,5, dolor mayor o igual a 8 o requiere cirugía | Urgencias |
| 7 | Supera las reglas anteriores y tiene al menos 2 días estimados de hospitalización | Hospitalización |
| 8 | No cumple ninguna condición anterior | Medicina General |

### Justificación y Prioridades

* **Pediatría:** la edad se utiliza primero para separar la atención de menores de 14 años.
* **Cirugía y Traumatología:** el trauma conduce a una evaluación específica sobre la necesidad de cirugía.
* **Neurología:** los síntomas neurológicos determinan la derivación cuando no existe trauma y el paciente no fue enviado a Pediatría.
* **Cardiología:** se consideran el dolor de pecho y el umbral de presión arterial definido por el grupo.
* **Urgencias:** se agrupan fiebre, dolor intenso o necesidad de cirugía en pacientes que no fueron clasificados por reglas anteriores.
* **Hospitalización:** se consideran los días estimados cuando ninguna regla anterior determina otro servicio.
* **Medicina General:** actúa como servicio general para pacientes válidos que no cumplen los criterios anteriores.

Si un paciente cumple varias condiciones, tiene prioridad la primera que alcanza según la estructura del árbol. Por ejemplo, un menor de 14 años con trauma se clasifica en Pediatría.

La presión arterial se representa mediante un único valor entero. El grupo utiliza 140 como umbral de la regla de Cardiología.

### Datos Inválidos o Insuficientes

Los registros inválidos o incompletos se rechazan durante la lectura y no ingresan a la cola.

Como comportamiento defensivo interno, `evaluarPaciente()` devuelve `Medicina General` si recibe un puntero nulo, el árbol no está construido o el recorrido no alcanza una hoja. Este retorno no implica que los datos sean válidos; el flujo normal evalúa pacientes previamente validados y un árbol construido al iniciar.

---

## Formato del Archivo de Entrada

El archivo debe llamarse exactamente `pacientes.txt`. Cada línea contiene once campos separados por punto y coma:

```text
ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
```

Ejemplo de registro, sin incluir una fila de encabezados:

```text
001;Miles Morales;25;37.0;120;3;otro;0;0;0;0
```

El servicio no se indica en el archivo: se determina mediante el árbol de decisión.

### Validaciones Aplicadas

| Campo | Valores admitidos |
|---|---|
| ID | Texto no vacío y único entre pacientes actualmente en cola o servicios |
| Nombre | Texto no vacío |
| Edad | Entero entre 0 y 130 |
| Temperatura | Número finito entre 25 y 45, usando punto decimal |
| Presión arterial | Entero entre 1 y 300 |
| Dolor | Entero entre 0 y 10 |
| Tipo de dolor | `pecho`, `cabeza`, `abdomen`, `extremidad` u `otro` |
| Trauma | Entero 0 o 1 |
| Síntomas neurológicos | Entero 0 o 1 |
| Requiere cirugía | Entero 0 o 1 |
| Días de hospitalización | Entero no negativo |

Los límites de edad, temperatura y presión son decisiones de validación del grupo.

Se eliminan los espacios y tabulaciones de los extremos de cada campo. Las líneas vacías se omiten. Las conversiones comprueban el campo completo, por lo que valores como `25abc` se rechazan.

---

## Organización del Repositorio

| Ubicación | Contenido |
|---|---|
| `main.cpp` | Creación e inicio del sistema |
| `CMakeLists.txt` | Configuración de compilación |
| `pacientes.txt` | Registros de entrada |
| `logica/Sistema.h` y `Sistema.cpp` | Coordinación del flujo y menús |
| `dominio/Persona.h` y `Persona.cpp` | Clase base |
| `dominio/Paciente.h` y `Paciente.cpp` | Datos y presentación del paciente |
| `dominio/Servicio.h` y `Servicio.cpp` | Administración del AVL por servicio |
| `dominio/Historial.h` y `Historial.cpp` | Registro de atenciones |
| `estructuras/Nodo.h` | Nodo genérico enlazado |
| `estructuras/Cola.h` | Cola de espera |
| `estructuras/Lista.h` | Lista de servicios |
| `estructuras/Stack.h` | Pila del historial |
| `estructuras/NodoDecision.h` | Nodo del árbol de decisión |
| `estructuras/ArbolDecision.h` y `ArbolDecision.cpp` | Clasificación y recorridos |
| `estructuras/NodoAVL.h` | Nodo del AVL |
| `estructuras/AVL.h` y `AVL.cpp` | Operaciones, balanceo y recorridos del AVL |

Las estructuras genéricas mantienen sus implementaciones en los encabezados.

---

## Requisitos del Entorno

* Compilador con soporte para **C++20**.
* Para compilación manual: `g++` o un compilador equivalente.
* Para utilizar el `CMakeLists.txt` actual: **CMake 4.2 o superior**.
* Terminal para interactuar con los menús.

La compilación manual no requiere CMake.

---

## Instrucciones de Compilación y Ejecución

> `pacientes.txt` se busca en el directorio de trabajo desde el que se inicia el programa, no necesariamente en la carpeta del ejecutable. Los comandos siguientes se ejecutan desde la raíz del proyecto, donde está el TXT.

### Opción 1: Compilación Manual con G++

Desde la raíz del proyecto:

```bash
g++ -std=c++20 -Wall -Wextra main.cpp logica/Sistema.cpp dominio/Persona.cpp dominio/Paciente.cpp dominio/Servicio.cpp dominio/Historial.cpp estructuras/ArbolDecision.cpp estructuras/AVL.cpp -o hospital
```

En Linux o GitHub Codespaces:

```bash
./hospital
```

En Windows con MinGW:

```powershell
g++ -std=c++20 -Wall -Wextra main.cpp logica/Sistema.cpp dominio/Persona.cpp dominio/Paciente.cpp dominio/Servicio.cpp dominio/Historial.cpp estructuras/ArbolDecision.cpp estructuras/AVL.cpp -o hospital.exe
.\hospital.exe
```

### Opción 2: Compilación con CMake

Comprobar que la versión instalada cumpla el requisito del proyecto:

```bash
cmake --version
```

Configurar y compilar desde la raíz:

```bash
cmake -S . -B build
cmake --build build
```

Ejecutar en Linux o Codespaces, conservando la raíz como directorio de trabajo:

```bash
./build/Taller_2IM
```

En Windows, la ubicación depende del generador utilizado. Por ejemplo:

```powershell
.\build\Taller_2IM.exe
```

Con un generador de varias configuraciones:

```powershell
.\build\Debug\Taller_2IM.exe
```

### Ejecución en CLion

Configurar **Run → Edit Configurations → Working directory** con la carpeta que contiene `pacientes.txt`.

Si el TXT está en la raíz del proyecto:

```text
$ProjectFileDir$
```

---

## Opciones del Programa

El menú principal contiene:

```text
1. Atender pacientes
2. Ver departamento
3. Revisar historial de atencion
4. Buscar paciente
5. Eliminar paciente por ID
6. Ver recorridos del arbol de decision
7. Salir
```

* **Atender pacientes:** muestra la cola, solicita una cantidad y procesa pacientes respetando FIFO.
* **Ver departamento:** permite seleccionar un servicio y consultar inorden, preorden, postorden, altura y balances de su AVL.
* **Revisar historial:** muestra las atenciones registradas, comenzando por la más reciente.
* **Buscar paciente:** busca por ID o nombre exacto entre los pacientes almacenados en los servicios.
* **Eliminar paciente:** elimina por ID del AVL correspondiente y conserva su atención histórica.
* **Recorridos del árbol de decisión:** muestra preorden, inorden y postorden de las reglas y servicios.
* **Salir:** finaliza el programa y ejecuta los destructores.

Las operaciones modifican las estructuras en memoria. No reescriben `pacientes.txt` ni guardan el historial entre ejecuciones.

---

## Manejo de Casos Borde y Memoria

* **Archivo inexistente:** se informa el error y se mantiene disponible el menú.
* **Registros inválidos:** se indica el número de línea y el motivo del rechazo; continúa la lectura de los demás registros.
* **Duplicados:** se comprueba el ID en la cola y en los AVL de los servicios.
* **Cola vacía:** se informa que no hay pacientes pendientes.
* **Cantidad superior a los pacientes disponibles:** se atienden los existentes y se informa cuando la cola se vacía.
* **Servicio vacío:** se informa que no contiene pacientes.
* **Búsqueda o eliminación fallida:** se muestra un mensaje sin modificar los demás registros.
* **Entrada del menú:** se controlan fallos de conversión y opciones fuera de rango. Las lecturas con `cin >>` pueden interpretar el prefijo numérico de una entrada como `1abc`; los caracteres restantes pueden producir un error en la siguiente lectura.
* **Propiedad de pacientes:** la cola mantiene los pacientes pendientes; cada AVL se hace responsable de los pacientes insertados correctamente.
* **Inserción rechazada:** el AVL no elimina el paciente recibido cuando devuelve `false`.
* **Historial independiente:** conserva copias de los pacientes y libera esas copias al destruirse.
* **Destrucción de árboles:** se liberan recursivamente los nodos; el AVL también libera sus pacientes.
* **Estructuras enlazadas:** sus destructores liberan los nodos mediante recorridos iterativos.

---

## Pruebas Realizadas

* Clasificación de casos representativos hacia los ocho servicios.
* Conservación del orden FIFO de atención.
* Búsqueda por ID y nombre y consultas sin coincidencias.
* Eliminación de pacientes y conservación de su historial.
* Consulta de recorridos, alturas y balances.
* Rechazo de campos vacíos, valores fuera de rango, números incompletos y valores booleanos inválidos.
* Manejo de archivos ausentes, vacíos, registros duplicados y cantidades incorrectas de campos.
* Prueba de 5.000 operaciones combinadas sobre el AVL, comprobando orden, alturas, balance y búsquedas después de cada operación.

