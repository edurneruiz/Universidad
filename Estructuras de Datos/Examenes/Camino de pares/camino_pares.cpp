
// EDURNE RUIZ Y AITOR ESTEBAN

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

//orden, el tamaño n es el número de nodos
//T(n) = k, si n<2
//T(n) = 2*T(n/2), si n >= 2
//Por el teorema de la división, el orden es lineal con n (nº de nodos)

typedef struct { //datos sobre un nodo
	int camino_max; //camino máximo con todos sus elementos pares que pasa por ese nodo
	int camino_act; //longitud de la rama más larga que pasa por ese nodo con todos sus elementos pares 
} tCamino;

bool esNodoPar(bintree<int>& iz, bintree<int>& dcho) { //devuelve true si tiene dos hijos cuyas raíces son pares
	return !iz.empty() && !dcho.empty() && iz.root() % 2 == 0 && dcho.root() % 2 == 0;
}

tCamino camino_pares(bintree<int>& a) {
	if (a.empty()) return { 0,0 };
	else {
		bintree<int> iz = a.left();
		bintree<int> dcho = a.right();
		tCamino c_iz = camino_pares(iz);
		tCamino c_d = camino_pares(dcho);
		tCamino c_a;

		if (a.root() % 2 == 0) { //si la raiz es par
			c_a.camino_act = fmax(c_iz.camino_act, c_d.camino_act) + 1; //calcular la longitud de la rama de pares que pasa por este nodo  
			if (esNodoPar(iz, dcho)) { //las raíces de sus dos hijos son pares
				int m = c_iz.camino_act + c_d.camino_act + 1; 
				c_a.camino_max = fmax(m, fmax(c_iz.camino_max, c_d.camino_max));
			}
			else { c_a.camino_max = fmax(c_a.camino_act, fmax(c_iz.camino_max, c_d.camino_max)); }
		}
		else { //si la raiz es impar
			c_a.camino_act = 0; //el camino de pares que pasa por este nodo tiene longitud 0
			c_a.camino_max = fmax(c_iz.camino_max, c_d.camino_max);
		}
		return c_a;
	}
}

void resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	cout << camino_pares(arbol).camino_max << '\n';
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) {
		resuelveCaso();
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}