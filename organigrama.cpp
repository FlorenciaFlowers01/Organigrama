#include "organigrama3.h"
#include <iostream>
#include <cstring>
using namespace std;

// Función para inicializar una persona
void inicializarPersona(Persona persona, const char* nombre, const char* ci) {
	strcpy(persona->nombre, nombre);
	strcpy(persona->ci, ci);
	persona->numSubordinados = 0;
}

// Crear el organigrama
TipoRet EliminarOrg(Empresa &e) {
    if (e->organigrama == nullptr) {
        return ERROR; // La empresa está vacía
    }
    for (int i = 0; i < e->organigrama->numSubordinados; i++) {
        delete e->organigrama->subordinados[i]; // Liberar la memoria de cada subordinado
    }
    delete[] e->organigrama->subordinados; // Liberar la memoria de subordinados
    delete e->organigrama; // Liberar la memoria del organigrama
    e->organigrama = nullptr;
    return OK;
}
// Eliminar el organigrama
void eliminarOrganigramaRec(Persona node) {
	if (node == nullptr) {
		return;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		eliminarOrganigramaRec(node->subordinados[i]);
	}
	delete node;
}

TipoRet EliminarOrg(Empresa &e) {
	if (e->organigrama == nullptr) {
		return ERROR; // La empresa está vacía
	}
	eliminarOrganigramaRec(e->organigrama);
	e->organigrama = nullptr;
	return OK;
}

// Buscar cargo
Persona buscarCargo(Persona node, const char* cargo) {
	if (node == nullptr) {
		return nullptr;
	}
	if (strcmp(node->nombre, cargo) == 0) {
		return node;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		Persona found = buscarCargo(node->subordinados[i], cargo);
		if (found != nullptr) {
			return found;
		}
	}
	return nullptr;
}

// Comprobar si una persona ya está asignada a algún cargo
bool personaYaAsignada(Empresa &e, const char* ci) {
	if (e->organigrama == nullptr) {
		return false; // La empresa está vacía
	}
	return eliminarPersonaRec(e->organigrama, ci);
}

// Asignar persona a un cargo
TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci) {
	Persona cargoPersona = buscarCargo(e->organigrama, cargo);
	if (cargoPersona == nullptr) {
		return ERROR; // El cargo no existe
	}
	
	// Comprobar si la persona ya está asignada a otro cargo
	if (personaYaAsignada(e, ci)) {
		return ERROR; // La persona ya está asignada a otro cargo
	}
	
	// Asignar la nueva persona
	if (cargoPersona->numSubordinados < MAX_PERSONAS) {
		Persona nuevaPersona = new _persona; 
		inicializarPersona(nuevaPersona, nom, ci);
		cargoPersona->subordinados[cargoPersona->numSubordinados] = nuevaPersona;
		cargoPersona->numSubordinados++;
		return OK;
	}
	
	return ERROR; // No se pueden agregar más subordinados
}

// Eliminar una persona de un cargo
bool eliminarPersonaRec(Persona node, const char* ci) {
	if (node == nullptr) {
		return false;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		if (strcmp(node->subordinados[i]->ci, ci) == 0) {
			delete node->subordinados[i];
			for (int j = i; j < node->numSubordinados - 1; ++j) {
				node->subordinados[j] = node->subordinados[j + 1];
			}
			node->numSubordinados--;
			return true;
		}
		if (eliminarPersonaRec(node->subordinados[i], ci)) {
			return true;
		}
	}
	return false;
}

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
		for (int i = 0; i < node->numSubordinados; ++i) {
			cout << node->subordinados[i]->ci << " - " << node->subordinados[i]->nombre << endl;
		}
		return;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		listarPersonasRec(node->subordinados[i], cargo);
	}
}

TipoRet ListarPersonas(Empresa e, Cadena cargo) {
	if (e->organigrama == nullptr) {
		return ERROR; // La empresa está vacía
	}
	listarPersonasRec(e->organigrama, cargo);
	return OK;
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
	
	if (padre->numSubordinados < MAX_PERSONAS) {
		Persona nuevo = new _persona;
		inicializarPersona(nuevo, nuevoCargo, "");
		padre->subordinados[padre->numSubordinados++] = nuevo;
		return OK;
	}
	return ERROR; // No se pueden agregar más subordinados
}

// Listar jerarquía
void listarJerarquiaRec(Persona node, int nivel) {
	if (node == nullptr) {
		return;
	}
	for (int i = 0; i < nivel; ++i) {
		cout << "  "; // Indentación para mostrar el nivel
	}
	cout << node->nombre << endl;
	for (int i = 0; i < node->numSubordinados; ++i) {
		listarJerarquiaRec(node->subordinados[i], nivel + 1);
	}
}

TipoRet ListarJerarquia(Empresa e) {
	if (e->organigrama == nullptr) {
		return ERROR; // La empresa está vacía
	}
	listarJerarquiaRec(e->organigrama, 0);
	return OK;
}
