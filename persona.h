#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
#include <cstring>

const int MAX_PERSONAS = 100;

struct _persona {
    char nombre[50];
    char ci[8];
    _persona *sig;
    _persona *ant;
};
typedef _persona* Persona;

// Funciones específicas de Persona
void inicializarPersona(Persona persona, const char* nombre, const char* ci);
Persona buscarCargo(Persona node, const char* cargo);
void listarPersonasRec(Persona node, const char* cargo);
void eliminarOrganigramaRec(Persona node);
bool eliminarPersonaRec(Persona node, const char* ci);

#endif
