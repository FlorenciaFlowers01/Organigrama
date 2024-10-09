#include "organigrama.h"
#include <iostream>
#include <stdio.h>
using namespace std;

// Implementación de las funciones

void inicializarPersona(Persona* persona, const char* nombre) {
	int i = 0;
	while (nombre[i] != '\0' && i < 49) {
		persona->nombre[i] = nombre[i];
		i++;
	}
	persona->nombre[i] = '\0';
	persona->numSubordinados = 0;
	for (int j = 0; j < MAX_PERSONAS; ++j) {
		persona->subordinados[j] = nullptr;
	}
}

void crearOrg(Persona*& organigrama, const char* nombre) {
	if (organigrama != nullptr) {
		cout << "El organigrama ya existe." << endl;
		return;
	}
	organigrama = new Persona;
	inicializarPersona(organigrama, nombre);
}

void asignarPersona(Persona* organigrama, const char* jefe, const char* nombre) {
	Persona* jefePersona = buscarPersona(organigrama, jefe);
	if (jefePersona == nullptr) {
		// Crear un nuevo jefe (jefe) si no se encuentra
		jefePersona = new Persona;
		inicializarPersona(jefePersona, jefe);
		organigrama->subordinados[organigrama->numSubordinados] = jefePersona;
		organigrama->numSubordinados++;
	}
	if (jefePersona->numSubordinados < MAX_PERSONAS) {
		jefePersona->subordinados[jefePersona->numSubordinados] = new Persona;
		inicializarPersona(jefePersona->subordinados[jefePersona->numSubordinados], nombre);
		jefePersona->numSubordinados++;
	} else {
		cout << "No se pueden agregar más subordinados a " << jefe << endl;
	}
}

void listarPersonas(Persona* organigrama) {
	listarPersonasRec(organigrama, 0);
}

void eliminarOrganigrama(Persona*& organigrama) {
	eliminarOrganigramaRec(organigrama);
	organigrama = nullptr;
}

bool eliminarPersona(Persona* organigrama, const char* nombre) {
	return eliminarPersonaRec(organigrama, nombre);
}

Persona* buscarPersona(Persona* node, const char* nombre) {
	if (node == nullptr) {
		return nullptr;
	}
	int i = 0;
	while (node->nombre[i] == nombre[i] && node->nombre[i] != '\0' && nombre[i] != '\0') {
		i++;
	}
	if (node->nombre[i] == '\0' && nombre[i] == '\0') {
		return node;
	}
	for (int j = 0; j < node->numSubordinados; ++j) {
		Persona* found = buscarPersona(node->subordinados[j], nombre);
		if (found != nullptr) {
			return found;
		}
	}
	return nullptr;
}

void listarPersonasRec(Persona* node, int nivel) {
	if (node == nullptr) {
		return;
	}
	for (int i = 0; i < nivel; ++i) {
		cout << "  ";
	}
	cout << node->nombre << endl;
	for (int j = 0; j < node->numSubordinados; ++j) {
		listarPersonasRec(node->subordinados[j], nivel + 1);
	}
}

void eliminarOrganigramaRec(Persona* node) {
	if (node == nullptr) {
		return;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		eliminarOrganigramaRec(node->subordinados[i]);
	}
	delete node;
}

bool eliminarPersonaRec(Persona* node, const char* nombre) {
	if (node == nullptr) {
		return false;
	}
	for (int i = 0; i < node->numSubordinados; ++i) {
		int j = 0;
		while (node->subordinados[i]->nombre[j] == nombre[j] && node->subordinados[i]->nombre[j] != '\0' && nombre[j] != '\0') {
			j++;
		}
		if (node->subordinados[i]->nombre[j] == '\0' && nombre[j] == '\0') {
			eliminarOrganigramaRec(node->subordinados[i]);
			for (int k = i; k < node->numSubordinados - 1; ++k) {
				node->subordinados[k] = node->subordinados[k + 1];
			}
			node->subordinados[--node->numSubordinados] = nullptr;
			return true;
		}
		if (eliminarPersonaRec(node->subordinados[i], nombre)) {
			return true;
		}
	}
	return false;
}
