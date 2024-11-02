#include "organigrama3.h"
#include <iostream>
#include <cstring>
using namespace std;


// Crear el organigrama
TipoRet CrearOrg(Empresa &e, Cadena nombreEmpresa, Cadena cargo) {
	 // Verificar si ya existe un organigrama
	if (e->organigrama != nullptr) {
		return ERROR; // La empresa ya tiene un organigrama
	}
	// Almacenar el nombre de la empresa
	strcpy(e->nombre, nombreEmpresa); 
	e->organigrama = new _persona; 
	// Inicializar cada elemento a nullptr
	for (int i = 0; i < 100; i++) {
		e->organigrama->subordinados[i] = nullptr; 
	}
	// Inicializar los valores del organigrama
	e->organigrama->numSubordinados = 0;
	strcpy(e->organigrama->nombre, cargo); // Cargo inicial
	strcpy(e->organigrama->ci, ""); // Inicializar ci
	return OK;
}
// Eliminar recursivamente el organigrama
void eliminarOrganigramaRec(Persona node) {
	if (node == nullptr) {
		return;
	}
	// Eliminar recursivamente los subordinados
	for (int i = 0; i < node->numSubordinados; ++i) {
		eliminarOrganigramaRec(node->subordinados[i]);
	}
	 // Eliminar el nodo actual
	delete node;
}

// Eliminar el organigrama de la empresa
TipoRet EliminarOrg(Empresa &e) {
	if (e->organigrama == nullptr) {
		return ERROR; // La empresa está vacía
	}
	 // Llamar a la función recursiva para eliminar el organigrama
	eliminarOrganigramaRec(e->organigrama);
	e->organigrama = nullptr;
	return OK;
}

// Buscar cargo específico en el organigrama
Persona buscarCargo(Persona node, const char* cargo) {
	if (node == nullptr) {
		return nullptr;
	}
	// Verificar si el cargo actual es el buscado
	if (strcmp(node->nombre, cargo) == 0) {
		return node;
	}
	// Buscar recursivamente en los subordinados
	for (int i = 0; i < node->numSubordinados; ++i) {
		Persona found = buscarCargo(node->subordinados[i], cargo);
		if (found != nullptr) {
			return found;
		}
	}
	return nullptr;
}

// Agregar un nuevo cargo bajo un cargo existente
TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo) {
	 // Buscar el cargo padre en el organigrama
	Persona padre = buscarCargo(e->organigrama, cargoPadre);
	if (padre == nullptr) {
		return ERROR; // El cargo padre no existe
	}
	// Comprobar si el nuevo cargo ya existe
	if (buscarCargo(e->organigrama, nuevoCargo) != nullptr) {
		return ERROR; // El nuevo cargo ya existe
	}

	// Asignar el nuevo cargo como subordinado del cargo padre
	if (padre->numSubordinados < MAX_PERSONAS) {
		Persona nuevo = new _persona;
		inicializarPersona(nuevo, nuevoCargo, "");
		padre->subordinados[padre->numSubordinados++] = nuevo;
		return OK;
	}
	return ERROR; // No se pueden agregar más subordinados
}

// Listar jerarquía del organigrama
void listarJerarquiaRec(Persona node, int nivel) {
	if (node == nullptr) {
		return;
	}
	// Indentación para mostrar el nivel
	for (int i = 0; i < nivel; ++i) {
		cout << "  "; 
	}
	cout << node->nombre << endl;
	  // Llamar recursivamente para todos los subordinados
	for (int i = 0; i < node->numSubordinados; ++i) {
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
