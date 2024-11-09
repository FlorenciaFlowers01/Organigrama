#include "empresa.h"
#include "persona.h"
#include <iostream>
#include <cstring>
using namespace std;

// Crear el organigrama
TipoRet CrearOrg(Empresa &e, Cadena nombreEmpresa, Cadena cargo) {
    if (e->organigrama != nullptr) {
        return ERROR; // La empresa ya tiene un organigrama
    }
    strcpy(e->nombre, nombreEmpresa);
    e->organigrama = new persona;
    e->organigrama->subordinados = 0; // Inicializar subordinados
    strcpy(e->organigrama->nombre, cargo); // Cargo inicial
    strcpy(e->organigrama->ci, ""); // Inicializar ci
    e->organigrama->sig = nullptr;
    e->organigrama->ant = nullptr;
    return OK;
}

// Eliminar recursivamente el organigrama
void eliminarOrganigramaRec(Persona node) {
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < node->subordinados; ++i) {
        eliminarOrganigramaRec(node->subordinados[i]);
    }
    delete node;
}

// Eliminar el organigrama de la empresa
TipoRet EliminarOrg(Empresa &e) {
    if (e->organigrama == nullptr) {
        return ERROR; // La empresa está vacía
    }
    eliminarOrganigramaRec(e->organigrama);
    e->organigrama = nullptr;
    return OK;
}

// Buscar cargo específico en el organigrama
Persona buscarCargo(Persona node, Cadena cargo) {
    if (node == nullptr) {
        return nullptr;
    }
    if (strcmp(node->nombre, cargo) == 0) {
        return node;
    }
    for (int i = 0; i < node->subordinados; ++i) {
        Persona found = buscarCargo(node->subordinados[i], cargo);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

// Agregar un nuevo cargo bajo un cargo existente
TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo) {
    Persona padre = buscarCargo(e->organigrama, cargoPadre);
    if (padre == nullptr) {
        return ERROR; // El cargo padre no existe
    }
    if (buscarCargo(e->organigrama, nuevoCargo) != nullptr) {
        return ERROR; // El nuevo cargo ya existe
    }

    if (padre->subordinados < MAX_PERSONAS) {
        Persona nuevo = new persona;
        inicializarPersona(nuevo, nuevoCargo, "");
        padre->subordinados[padre->subordinados++] = nuevo;
        nuevo->ant = padre;
        if (padre->sig != nullptr) {
            padre->sig->ant = nuevo;
        }
        nuevo->sig = padre->sig;
        padre->sig = nuevo;
        return OK;
    }
    return ERROR; // No se pueden agregar más subordinados
}

// Listar jerarquía del organigrama
void listarJerarquiaRec(Persona node, int nivel) {
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < nivel; ++i) {
        cout << "  ";
    }
    cout << node->nombre << endl;
    for (int i = 0; i < node->subordinados; ++i) {
        listarJerarquiaRec(node->subordinados[i], nivel + 1);
    }
}

// Listar toda la jerarquía del organigrama de la empresa
TipoRet ListarJerarquia(Empresa e) {
    if (e->organigrama == nullptr) {
        return ERROR; // La empresa está vacía
    }
    listarJerarquiaRec(e->organigrama, 0);
    return OK;
}
