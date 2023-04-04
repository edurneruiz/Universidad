#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	bool zurdo; //si es zurdo o no
	int minAltura; // altura minima del arbol
} tArbol;


tArbol arbolZurdo(int estamosEnProfundidad, bintree<char> & a) {
	if (a.empty())
		return { true, 0 };
	else {
		bintree<char> iz = a.left(), d = a.right();

		if (iz.empty() && d.empty())
			return { true, estamosEnProfundidad };
		else if (iz.empty())
			return arbolZurdo(estamosEnProfundidad + 1, d);
		else if (d.empty())
			return arbolZurdo(estamosEnProfundidad + 1, iz);
		else {
			tArbol ziz = arbolZurdo(estamosEnProfundidad + 1, iz);
			tArbol zd = arbolZurdo(estamosEnProfundidad + 1, d);

			return { ziz.zurdo && zd.zurdo && (ziz.minAltura >= zd.minAltura),
					(ziz.minAltura < zd.minAltura) ? ziz.minAltura : zd.minAltura };
		}
	}
}

bool esZurdo(bintree<char> & a) {
	return arbolZurdo(1, a).zurdo;
}

bool resuelveCaso() {
	bintree<char> arbol = leerArbol('.');
	if (!std::cin) return false;

	if (esZurdo(arbol)) cout << "El arbol es zurdo";
	else cout << "El arbol no es zurdo";
	cout << "\n---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*

***..*..*..
***...**..*.*..
.
*..


*/