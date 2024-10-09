#ifndef ORGANIGRAMA3_H
#define ORGANIGRAMA3_H
#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
using namespace std;

const int MAX_PERSONAS = 100;

// Definición de la estructura Persona
struct _persona {
	char nombre[50];
	char ci[8];
	int numSubordinados;
	_persona* subordinados[MAX_PERSONAS]; // Arreglo de subordinados
};
typedef _persona* Persona; // Alias para puntero a _persona

// Definición de la estructura Empresa
struct _empresa {
	Persona organigrama; // Puntero al organigrama
};
typedef _empresa* Empresa; // Alias para puntero a _empresa

// Funciones para manejar el organigrama
enum _retorno { 
	OK, ERROR, NO_IMPLEMENTADA 
};
typedef enum _retorno TipoRet; // Alias para el tipo de retorno

typedef char* Cadena; // Alias para cadenas de caracteres

// Prototipos de funciones
TipoRet CrearOrg(Empresa &e, Cadena cargo);
TipoRet EliminarOrg(Empresa &e);
TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci);
TipoRet EliminarPersona(Empresa &e, Cadena ci);
TipoRet ListarPersonas(Empresa e, Cadena cargo);

void inicializarPersona(Persona persona, const char* nombre, const char* ci); // Cambiar a Persona en vez de Persona*
Persona buscarCargo(Persona node, const char* cargo); // Cambiar a Persona en vez de Persona*
void listarPersonasRec(Persona node, const char* cargo); // Cambiar a Persona en vez de Persona*
void eliminarOrganigramaRec(Persona node); // Cambiar a Persona en vez de Persona*
bool eliminarPersonaRec(Persona node, const char* ci); // Cambiar a Persona en vez de Persona*

#endif // ORGANIGRAMA3_H

