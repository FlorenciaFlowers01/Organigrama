#include <iostream>
#include <cstring>
#include "persona.h"
#include "persona.cpp"
#include "empresa.h"
#include "empresa.cpp"

using namespace std;

void mostrarMenu() {
	cout << "\n-----------------Menú-----------------" << endl;
	cout << "\nOpciones:" << endl;
	cout << "1. Crear organigrama" << endl;
	cout << "2. Asignar persona" << endl;
	cout << "3. Listar personas" << endl;
	cout << "4. Eliminar organigrama" << endl;
	cout << "5. Eliminar persona" << endl;
	cout << "6. Añadir nuevo cargo" << endl;
	cout << "7. Listar jerarquía" << endl;
	cout << "8. Listar cargos alfabeticamente" << endl;
	cout << "9. Eliminar cargo" << endl;
	cout << "10. Reasignar Persona" << endl;
	cout << "11. Listar super cargos" << endl;
	cout << "12. Salir" << endl;
	cout << "Seleccione una opción: \n";
}

int main(int argc, char *argv[]) {
	Empresa empresa = new _empresa; // Inicializar empresa
	empresa->organigrama = nullptr;
	int opcion;
	char nombreEmpresa[100];
	char nombre[50];
	char cargo[50];
	char ci[12];
	char cargoPadre[50];
	char nuevoCargo[50];
	
	do {
		mostrarMenu();
		cin >> opcion;
		cin.ignore(); // Limpiar el buffer de entrada
		switch (opcion) {
		case 1:{
			cout << "\nIngrese el nombre de la empresa: ";
			cin.getline(nombreEmpresa, 100);
			cout << "\nIngrese el nombre del cargo inicial: ";
			cin.getline(cargo, 50);
			if (CrearOrg(empresa, nombreEmpresa, cargo) == OK) {
				cout << "\nOrganigrama creado con éxito." << endl;
			} else {
				cout << "\nError al crear el organigrama." << endl;
			}
			break;
		}
		case 2:{
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
		}
		case 3:{
			cout << "\nIngrese el nombre del cargo para listar personas: ";
			cin.getline(cargo, 50);
			if (ListarPersonas(empresa, cargo) == ERROR) {
				cout << "\nError al listar las personas." << endl;
			}
			break;
			}
		case 4:{
			if (EliminarOrg(empresa) == OK) {
				cout << "\nOrganigrama eliminado correctamente." << endl;
			} else {
				cout << "\nError al eliminar el organigrama." << endl;
			}
			break;
			}
		case 5:{
			cout << "\nIngrese la cédula de identidad de la persona a eliminar: ";
			cin.getline(ci, 12);
			if (EliminarPersona(empresa, ci) == OK) {
				cout << "\nPersona eliminada con éxito." << endl;
			} else {
				cout << "\nError al eliminar la persona." << endl;
			}
			break;
			}
		case 6:{
				cout << "\nIngrese el nombre del cargo padre: ";
				cin.getline(cargoPadre, 50);
				cout << "\nIngrese el nombre del nuevo cargo: ";
				cin.getline(nuevoCargo, 50);
				if (NuevoCargo(empresa, cargoPadre, nuevoCargo) == OK) {
					cout << "\nNuevo cargo añadido con éxito." << endl;
				} else {
					cout << "\nError al añadir el nuevo cargo." << endl;
				}
				break;
			}
		case 7:{
					if (ListarJerarquia(empresa) == ERROR) {
						cout << "\nError al listar la jerarquía." << endl;
					}
					break;
				}
		case 8:{cout << "\nNo implementada."<< endl;}
			break;
		case 9: {cout << "\nNo implementada."<< endl;}
			break;
		case 10: {cout << "\nNo implementada."<< endl;}
			break;
		case 11: {cout << "\nNo implementada."<< endl;}
			break;
			
		case 12:{
			cout << "\nSaliendo..." << endl;
			break;
		default:
			cout << "\nOpción no válida." << endl;
			break;
		}
}
	} while (opcion != 12);
	
	delete empresa; // Liberar la memoria de la empresa
	return 0;
}

