#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int mayorDeLosMenores;
	int menorDeLosMayores;
	bool deBusqueda;
} tInfo;

tInfo buscar(bintree<int> & a) {
	if (a.empty())
		return { INT_MIN, INT_MAX, true };
	else {
		bintree<int> iz = a.left(), d = a.right();

		if (iz.empty() && d.empty()) 
			return { a.root(), a.root(), true };
		else {
			tInfo i_iz = buscar(iz);
			tInfo i_d = buscar(d);
			bool hijosDeBusqueda = i_iz.deBusqueda && i_d.deBusqueda;

			if (iz.empty())
				return { a.root(), d.root(), hijosDeBusqueda && (a.root() < d.root()) };
			else if (d.empty())
				return { iz.root(), a.root(), hijosDeBusqueda && (iz.root() < a.root()) };
			else
				return { i_iz.menorDeLosMayores,
				i_d.mayorDeLosMenores,
				hijosDeBusqueda && (a.root() < i_d.menorDeLosMayores) && (i_iz.mayorDeLosMenores < a.root()) };
		}
	}
}

bool esDeBusqueda(bintree<int> & a) {
	tInfo f = buscar(a);
	return f.deBusqueda;
}

bool resuelveCaso() {

	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	if (esDeBusqueda(arbol)) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos--) {
		resuelveCaso();
	}
	system("pause");
	return 0;
}
