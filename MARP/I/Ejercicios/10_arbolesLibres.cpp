///EDURNE RUIZ DG33
/*

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Grafo.h"
using namespace std;

class ArbolLibre {
	Grafo g;
	int size;

public:
	ArbolLibre(Grafo _g, int _size) : g(_g), size(_size) {}

	bool esArbolLibre() {
		


	}

protected:
	bool libre(int act, int ant, vector<bool> & marcados) {
		marcados[act] = true;
		for (int v : g.ady(act)) {

		}
	}
};


void inicializarGrafo(int A, Grafo & g) {
	int v1, v2;
	while (A--) {
		cin >> v1 >> v2;
		g.ponArista(v1, v2);
	}
}

bool resuelveCaso() {
	int V, A;
	cin >> V >> A;

	if (!std::cin)
		return false;
	else {
		Grafo g(V);
		inicializarGrafo(A, g);

		

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}