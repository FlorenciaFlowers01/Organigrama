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
	char nombre[100];
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
TipoRet CrearOrg(Empresa &e, Cadena nombreEmpresa, Cadena cargo);
TipoRet EliminarOrg(Empresa &e);
TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci);
TipoRet EliminarPersona(Empresa &e, Cadena ci);
TipoRet ListarPersonas(Empresa e, Cadena cargo);
TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo);
TipoRet ListarJerarquia(Empresa e);

void inicializarPersona(Persona persona, const char* nombre, const char* ci); 
Persona buscarCargo(Persona node, const char* cargo); 
void listarPersonasRec(Persona node, const char* cargo); 
void eliminarOrganigramaRec(Persona node); 
bool eliminarPersonaRec(Persona node, const char* ci); 

#endif // ORGANIGRAMA3_H
