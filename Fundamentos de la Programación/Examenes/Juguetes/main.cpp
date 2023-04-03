#include <iostream>
#include <fstream>
#include <iomanip>
#include "juguete.h"
#include "listaJuguetes.h"
#include "coleccion.h"
#include "checkML.h"
using namespace std;

//prototipos
int menu();
void opcion2(tListaJuguetes & j);

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int opc;
	tListaJuguetes j;

	if (!cargar(j)) { cout << "No se ha podido cargar el inventario!" << endl; }
	else {
		opc = menu();
		while (opc != 0) {
			switch (opc) {
			case 1: { mostrar(j); }
					break;
			case 2: { opcion2(j); }
					break;
			default: { cout << "Opcion no valida!" << endl; }
			}
			cout << endl;
			opc = menu();
		}
	}

	liberar(j);

	system("pause");
	return 0;
}

int menu() {
	int opc;

	cout << "----------------------" << endl;
	cout << "1- Visualizar inventario de juguetes" << endl;
	cout << "2- Crear y mostrar coleccion" << endl;
	cout << "0- Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << "----------------------" << endl;

	return opc;
}

void opcion2(tListaJuguetes & j) {
	int d;
	float precio;
	tColeccion c;
	cout << "Decada (50, 60, 70 u 80): ";
	cin >> d;
	cout << "Precio max: ";
	cin >> precio;
	c = crearColeccion(j, precio, escDecada(d));
	cout << left << setw(20) << "IDENTIFICADOR" << setw(10) << "DECADA" << setw(14) << "UNIDADES" << setw(20) << "Precio venta: " << "Precio base: " << endl;
	mostrar(c, 0);
	borrar(c);
}