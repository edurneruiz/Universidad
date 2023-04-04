#include <iostream>
#include<string>
#include <fstream>
#include "almacen.h"
using namespace std;


bool resuelveCaso() {
	ifstream archivo;
	archivo.open("almacen.txt");

	if (!archivo.is_open())
		return false;
	else {
		almacen a;
		string orden, cliente, producto; fecha f; int n;

		archivo >> orden;
		while (orden != "FIN") {
			if (orden == "vender") {
				archivo >> producto >> cliente;
				std::pair<bool, fecha> p = a.vender(producto, cliente);
				if (p.first)
					cout << "VENDIDO " << p.second;
				else
					cout << "EN ESPERA";
			}
			else if (orden == "adquirir") {
				archivo >> producto >> f >> n;
				vector<string> v = a.adquirir(producto, f, n);
				cout << "PRODUCTO ADQUIRIDO ";
				for (int i = 0; i < v.size(); ++i) {
					cout << v[i] << " ";
				}
			}
			else if (orden == "cuantos") {
				archivo >> producto;
				cout << a.cuantos(producto);
			}
			else if (orden == "hay_esperando") {
				archivo >> producto;
				if (a.hay_esperando(producto))
					cout << "SI";
				else
					cout << "NO";
			}
			cout << '\n';
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