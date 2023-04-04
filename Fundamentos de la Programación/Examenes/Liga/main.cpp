#include <iostream>
#include <fstream>
#include <string>
#include "listaJugadores.h"
#include "listaEquipos.h"
#include "liga.h"
using namespace std;


//prototipos
int menu();
void opcion1(tLiga & liga);



int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int opc, num = 0;
	tListaEquipos equipos;
	tLiga liga;

	if (!cargar(equipos, num)) { cout << "No se ha podido cargar el archivo!" << endl; }
	else {
		inicializarLiga(liga, equipos, num);
		opc = menu();
		while (opc != 0) {
			switch (opc) {
			case 1: {	opcion1(liga);	}
					break;
			case 2: { }
					break;
			case 3: {mostrar(liga); }
					break;
			default: { cout << "Opcion no valida" << endl; }
			}
			opc = menu();
		}

	}

	liberar(liga);

	return 0;
}

int menu() {
	int opc;
	
	cout << endl;
	cout << "1- Transferir jugador" << endl;
	cout << "2- Jugar un partido" << endl;
	cout << "3- Mostrar clasificacion" << endl;
	cout << "0- Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void opcion1(tLiga & liga) {
	int pos_jugador, pos_c, pos_v;
	string comprador, vendedor;
	mostrarDinero(liga);

	cout << "Comprador: ";
	cin >> comprador;
	pos_c = buscar(liga, comprador);
	cout << "Vendedor: ";
	cin >> vendedor;
	pos_v = buscar(liga, vendedor);

	pos_jugador = elegir(liga.equipos[pos_v]);
	transferir(pos_jugador, liga.equipos[pos_c], liga.equipos[pos_v]);
}