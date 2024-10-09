#include<iostream>
using namespace std;
#include <cstring>
#include "organigrama.h"
	
	void mostrarMenu() {
		cout << "\nOpciones:" << endl;
		cout << "1. Crear organigrama" << endl;
		cout << "2. Asignar persona" << endl;
		cout << "3. Listar personas" << endl;
		cout << "4. Eliminar organigrama" << endl;
		cout << "5. Eliminar persona" << endl;
		cout << "6. Salir" << endl;
		cout << "Seleccione una opción: \n";
	}
	int main(int argc, char *argv[]) {
		Persona* organigrama = nullptr;
		int opcion;
		char nombre[50];
		char jefe[50];
		do {
			mostrarMenu();
			cin >> opcion;
			cin.ignore(); // Limpiar el buffer de entrada
			switch (opcion) {
			case 1:
				cout << "\nIngrese el nombre del organigrama: ";
				cin.getline(nombre, 50);
				crearOrg(organigrama, nombre);
				break;
			case 2:
				cout << "\nIngrese el nombre del jefe: ";
				cin.getline(jefe, 50);
				cout << "\nIngrese el nombre de la persona: ";
				cin.getline(nombre, 50);
				asignarPersona(organigrama, jefe, nombre);
				break;
			case 3:
				listarPersonas(organigrama);
				break;
			case 4:
				
				eliminarOrganigrama(organigrama);
				cout << "\nOrganigrama eliminado." << endl;
				break;
			case 5:
				cout << "\nIngrese el nombre de la persona a eliminar: ";
				cin.getline(nombre, 50);
				eliminarPersona(organigrama, nombre);
				break;
			case 6:
				cout << "\nSaliendo..." << endl;
				break;
			default:
				cout << "\nOpción no válida." << endl;
				break;
				
			}
		} while (opcion != 6);
		return 0;
	}

