#include <iostream>
#include <string>
#include <vector>
#include "DGT.h"
using namespace std;


bool comparador(par p1, par p2) { return p1.second > p2.second; }

void mostrar(int p, vector<par> & v) {
	sort(v.begin(), v.end(), comparador); //ordenamos los dnis según han alcanzado los P puntos (primero el último que los haya alcanzado)

	cout << "Tienen " + to_string(p) + " puntos: ";
	for (par p : v) {
		cout << p.first << " ";
	}
	cout << "\n";
}

bool resuelveCaso() {
	string orden;
	
	cin >> orden;
	if (!std::cin) return false;

	carnet_puntos cp;
	string DNI;
	puntos pts;
	while (orden != "FIN") {
		try {
			if (orden == "nuevo") {
				cin >> DNI;
				cp.nuevo(DNI);
			}
			else if (orden == "recuperar") {
				cin >> DNI >> pts;
				cp.recuperar(DNI, pts);
			}
			else if (orden == "quitar") {
				cin >> DNI >> pts;
				cp.quitar(DNI, pts);
			}
			else if (orden == "consultar") {
				cin >> DNI;
				int p = cp.consultar(DNI);
				cout << "Puntos de " + DNI + ": " + to_string(p) << "\n";
			}
			else if (orden == "cuantos_con_puntos") {
				cin >> pts;
				int x = cp.cuantos_con_puntos(pts);
				cout << "Con " + to_string(pts) + " puntos hay " + to_string(x) << "\n";
			}
			else if (orden == "lista_por_puntos") {
				cin >> pts;
				vector<par> l = cp.lista_por_puntos(pts);
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
	while (resuelveCaso()){}
	return 0;
}