#include <iostream>
#include <string>
#include <vector>
#include "DGT2.h"
using namespace std;


void mostrar(int p, vector<DNI> & v) {

	cout << "Tienen " + to_string(p) + " puntos: ";
	for (int i = v.size() - 1; i >= 0; --i) {
		cout << v[i] << " ";
	}
	cout << "\n";
}

bool resuelveCaso() {
	string orden;

	cin >> orden;
	if (!std::cin) return false;

	carnet_puntos cp;
	DNI dni;
	puntos pts;
	while (orden != "FIN") {
		try {
			if (orden == "nuevo") {
				cin >> dni;
				cp.nuevo(dni);
			}
			else if (orden == "recuperar") {
				cin >> dni >> pts;
				cp.recuperar(dni, pts);
			}
			else if (orden == "quitar") {
				cin >> dni >> pts;
				cp.quitar(dni, pts);
			}
			else if (orden == "consultar") {
				cin >> dni;
				int p = cp.consultar(dni);
				cout << "Puntos de " + dni + ": " + to_string(p) << "\n";
			}
			else if (orden == "cuantos_con_puntos") {
				cin >> pts;
				int x = cp.cuantos_con_puntos(pts);
				cout << "Con " + to_string(pts) + " puntos hay " + to_string(x) << "\n";
			}
			else if (orden == "lista_por_puntos") {
				cin >> pts;
				vector<DNI> l = cp.lista_por_puntos(pts);
				mostrar(pts, l);
			}
		}
		catch (std::domain_error e) {
			std::cout << "ERROR: " << e.what() << '\n';
		}
		cin >> orden;
	}
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}