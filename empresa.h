#ifndef EMPRESA_H
#define EMPRESA_H
#include "persona.h"

struct _empresa {
    char nombre[100];
    Persona organigrama;
};
typedef _empresa* Empresa;

enum _retorno { 
    OK, ERROR, NO_IMPLEMENTADA 
};
typedef enum _retorno TipoRet;
typedef char* Cadena;

// Funciones específicas de Empresa
TipoRet CrearOrg(Empresa &e, Cadena nombreEmpresa, Cadena cargo);
TipoRet EliminarOrg(Empresa &e);
TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci);
TipoRet EliminarPersona(Empresa &e, Cadena ci);
TipoRet ListarPersonas(Empresa e, Cadena cargo);
TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo);
TipoRet ListarJerarquia(Empresa e);

#endif
