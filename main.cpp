#include <iostream>
#include <cstring>
#include "organigrama3.h"

using namespace std;

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
	Empresa empresa = new _empresa; // Inicializar empresa
	empresa->organigrama = nullptr;
	int opcion;
	char nombre[50];
	char cargo[50];
	char ci[12];
	
	do {
		mostrarMenu();
		cin >> opcion;
		cin.ignore(); // Limpiar el buffer de entrada
		switch (opcion) {
		case 1:
			cout << "\nIngrese el nombre del cargo inicial: ";
			cin.getline(cargo, 50);
			if (CrearOrg(empresa, cargo) == OK) {
				cout << "\nOrganigrama creado con éxito." << endl;
			} else {
				cout << "\nError al crear el organigrama." << endl;
			}
			break;
		case 2:
			cout << "\nIngrese el nombre del cargo: ";
			cin.getline(cargo, 50);
			cout << "\nIngrese el nombre de la persona: ";
			cin.getline(nombre, 50);
			cout << "\nIngrese la cédula de identidad de la persona: ";
			cin.getline(ci, 12);  // Asegúrate de que sea lo suficientemente largo
			if (AsignarPersona(empresa, cargo, nombre, ci) == OK) {
				cout << "\nPersona asignada con éxito." << endl;
			} else {
				cout << "\nError al asignar la persona." << endl;
			}
			break;
		case 3:
			cout << "\nIngrese el nombre del cargo para listar personas: ";
			cin.getline(cargo, 50);
			if (ListarPersonas(empresa, cargo) == ERROR) {
				cout << "\nError al listar las personas." << endl;
			}
			break;
		case 4:
			if (EliminarOrg(empresa) == OK) {
				cout << "\nOrganigrama eliminado correctamente." << endl;
			} else {
				cout << "\nError al eliminar el organigrama." << endl;
			}
			break;
		case 5:
			cout << "\nIngrese la cédula de identidad de la persona a eliminar: ";
			cin.getline(ci, 12);
			if (EliminarPersona(empresa, ci) == OK) {
				cout << "\nPersona eliminada con éxito." << endl;
			} else {
				cout << "\nError al eliminar la persona." << endl;
			}
			break;
		case 6:
			cout << "\nSaliendo..." << endl;
			break;
		default:
			cout << "\nOpción no válida." << endl;
			break;
		}
	} while (opcion != 6);
	
	delete empresa; // Liberar la memoria de la empresa
	return 0;
}
