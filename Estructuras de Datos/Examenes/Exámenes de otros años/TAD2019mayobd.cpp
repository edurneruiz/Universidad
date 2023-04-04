#include <iostream>
#include<string>
#include <fstream>
#include "ventas.h"
using namespace std;

void mostrar(vector<pair<string, int>> & v) {
	cout << "En total, se han vendido: ";
	for (pair<string, int> p : v) {
		cout << "    " << p.second + " unidades de " + p.first << '\n';
	}
	cout << '\n';
}

bool resuelveCaso() {
	ifstream archivo;
	archivo.open("ventas.txt");

	if (!archivo.is_open())
		return false;
	else {
		ventas a;
		string orden, producto, cliente; int num_unidades;

		archivo >> orden;
		while (orden != "FIN") {
			try {
				if (orden == "annadir_oferta") {
					archivo >> producto >> num_unidades;
					a.annadir_oferta(producto, num_unidades);
				}
				else if (orden == "poner_en_espera") {
					archivo >> producto >> cliente;
					a.poner_en_espera(cliente, producto);
				}
				else if (orden == "num_en_espera") {
					archivo >> producto;
					int n = a.num_en_espera(producto);
					cout << "Hay " + to_string(n) + " disponibles del producto " + producto << '\n';
				}
				else if (orden == "vender") {
					archivo >> producto >> num_unidades;
					a.vender(producto, num_unidades);
				}
				else if (orden == "primero_en_espera") {
					archivo >> producto;
					string c = a.primero_en_espera(producto);
					cout << "El primero en la espera por el producto " + producto + " es " + c << '\n';
				}
				else if (orden == "lista_ventas") {
					vector<pair<string, int>> v = a.lista_ventas();
					mostrar(v);
				}
			}
			catch (domain_error e) {
				cout << e.what() << '\n';
			}
			archivo >> orden;
		}
	}
	cout << "---\n";
	archivo.close();
	return true;
}


int main() {
	resuelveCaso();
	system("pause");
	//while (resuelveCaso()){}
	return 0;
}