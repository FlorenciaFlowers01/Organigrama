#ifndef ORGANIGRAMA_H
#define ORGANIGRAMA_H
#include <iostream>
#include <stdio.h>
using namespace std;

const int MAX_PERSONAS = 100;

// Definición de la estructura Persona
struct Persona {
	char nombre[50];
	Persona* subordinados[MAX_PERSONAS];
	int numSubordinados;
};

// Funciones para manejar el organigrama
void inicializarPersona(Persona* persona, const char* nombre);
void crearOrg(Persona*& organigrama, const char* nombre);
void asignarPersona(Persona* organigrama, const char* jefe, const char* nombre);
void listarPersonas(Persona* organigrama);
void eliminarOrganigrama(Persona*& organigrama);
bool eliminarPersona(Persona* organigrama, const char* nombre);

Persona* buscarPersona(Persona* node, const char* nombre);
void listarPersonasRec(Persona* node, int nivel);
void eliminarOrganigramaRec(Persona* node);
bool eliminarPersonaRec(Persona* node, const char* nombre);

#endif // ORGANIGRAMA_H


