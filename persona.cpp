#include "organigrama3.h"
#include <iostream>
#include <cstring>
using namespace std;

// Función para inicializar una persona
void inicializarPersona(Persona persona, const char* nombre, const char* ci) {
	 // Copiar nombre y cédula de identidad a la persona
	strcpy(persona->nombre, nombre);
	strcpy(persona->ci, ci);
	// Inicializar el número de subordinados a 0
	persona->sig = null;
	persona->ant = null;
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
	if (cargoPersona->numSubordinados < MAX_PERSONAS) {
		Persona nuevaPersona = new _persona; 
		inicializarPersona(nuevaPersona, nom, ci);
		cargoPersona->subordinados[cargoPersona->numSubordinados] = nuevaPersona;
		cargoPersona->numSubordinados++;
		return OK;
	}
	
	return ERROR; // No se pueden agregar más subordinados
}

// Eliminar una persona de un cargo en el organigrama
bool eliminarPersonaRec(Persona node, const char* ci) {
	if (node == nullptr) {
		return false;
	}
	// Buscar recursivamente la persona a eliminar
	for (int i = 0; i < node->numSubordinados; ++i) {
		if (strcmp(node->subordinados[i]->ci, ci) == 0) {
			// Eliminar la persona y reordenar el array de subordinados
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
		for (int i = 0; i < node->numSubordinados; ++i) {
			// Solo imprime personas directamente asignadas, no recursivamente
			if (strlen(node->subordinados[i]->ci) > 0) { // Verificar que la persona tenga cédula asignada
			cout << node->subordinados[i]->ci << " - " << node->subordinados[i]->nombre << endl;
			}
		}
		return;
	}
	 // Llamar recursivamente para todos los subordinados
	for (int i = 0; i < node->numSubordinados; ++i) {
		listarPersonasRec(node->subordinados[i], cargo);
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
