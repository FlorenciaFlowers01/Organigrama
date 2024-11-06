#include "organigrama3.h"
#include <iostream>
#include <cstring>
using namespace std;

// Función para inicializar una persona
void inicializarPersona(Persona persona, const char* nombre, const char* ci) {
    // Copiar nombre y cédula de identidad a la persona
    strcpy(persona->nombre, nombre);
    strcpy(persona->ci, ci);
    // Inicializar punteros de la lista doblemente encadenada
    persona->sig = nullptr;
    persona->ant = nullptr;
}

// Comprobar si una persona ya está asignada a algún cargo
bool personaYaAsignada(Empresa &e, const char* ci) {
    if (e->organigrama == nullptr) {
        return false; // La empresa está vacía
    }
    return eliminarPersonaRec(e->organigrama, ci);
}

// Asignar persona a un cargo en el organigrama
TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci) {
    // Buscar el cargo en el organigrama
    Persona cargoPersona = buscarCargo(e->organigrama, cargo);
    if (cargoPersona == nullptr) {
        return ERROR; // El cargo no existe
    }
    
    // Comprobar si la persona ya está asignada a otro cargo
    if (personaYaAsignada(e, ci)) {
        return ERROR; // La persona ya está asignada a otro cargo
    }
    
    // Asignar la nueva persona
    Persona nuevaPersona = new _persona; 
    inicializarPersona(nuevaPersona, nom, ci);
    
    // Enlazar la nueva persona en la lista doblemente encadenada
    nuevaPersona->sig = cargoPersona->sig;
    if (cargoPersona->sig != nullptr) {
        cargoPersona->sig->ant = nuevaPersona;
    }
    cargoPersona->sig = nuevaPersona;
    nuevaPersona->ant = cargoPersona;
    
    return OK;
}

// Eliminar una persona de un cargo en el organigrama
bool eliminarPersonaRec(Persona node, const char* ci) {
    if (node == nullptr) {
        return false;
    }

    Persona current = node;
    while (current != nullptr) {
        if (strcmp(current->ci, ci) == 0) {
            // Desenlazar la persona de la lista
            if (current->ant != nullptr) {
                current->ant->sig = current->sig;
            }
            if (current->sig != nullptr) {
                current->sig->ant = current->ant;
            }
            delete current;
            return true;
        }
        current = current->sig;
    }
    return false;
}

// Eliminar una persona de la empresa
TipoRet EliminarPersona(Empresa &e, Cadena ci) {
    if (e->organigrama == nullptr) {
        return ERROR; // La empresa está vacía
    }
    if (eliminarPersonaRec(e->organigrama, ci)) {
        return OK;
    }
    return ERROR; // La persona no existe
}

// Listar personas en un cargo
void listarPersonasRec(Persona node, const char* cargo) {
    if (node == nullptr) {
        return;
    }
    if (strcmp(node->nombre, cargo) == 0) {
        cout << "Listado de personas asignadas a " << cargo << ":\n-------------------------------------------------------" << endl;
        // Solo imprime personas directamente asignadas a este cargo
        Persona current = node->sig;
        while (current != nullptr) {
            if (strlen(current->ci) > 0) { // Verificar que la persona tenga cédula asignada
                cout << current->ci << " - " << current->nombre << endl;
            }
            current = current->sig;
        }
        return;
    }
    // Llamar recursivamente para todos los subordinados
    Persona current = node->sig;
    while (current != nullptr) {
        listarPersonasRec(current, cargo);
        current = current->sig;
    }
}

// Listar las personas en un cargo específico de la empresa
TipoRet ListarPersonas(Empresa e, Cadena cargo) {
    if (e->organigrama == nullptr) {
        return ERROR; // La empresa está vacía
    }
    listarPersonasRec(e->organigrama, cargo);
    return OK;
}
