#include <iostream>
#include "bintree_eda.h"
using namespace std;


bool ramasSimetricas(bintree<char> & l, bintree<char> & r) {

	if (l.empty() && r.empty()) //si ambos árboles que comparamos son vacíos, son simétricos
		return true;
	else if (l.empty() || r.empty())  //si uno es vacío y el otro no, no son simétricos
		return false;
	else {
		bintree<char> l_iz = l.left(), l_d = l.right(), r_iz = r.left(), r_d = r.right();
		bool exteriorSimetrico = ramasSimetricas(l_iz, r_d); //averiguamos si las ramas externas son simétricas
		bool interiorSimetrico = ramasSimetricas(l_d, r_iz); //averiguamos si las ramas internas son simétricas

		return exteriorSimetrico && interiorSimetrico; //si tanto las ramas internas como externas son simétricas, el árbol es simétrico
	}
}

bool simetrico(bintree<char> & a) {
	if (a.empty())
		return true;
	else {
		bintree<char> iz = a.left(), d = a.right();
		return ramasSimetricas(iz, d);
	}
}

void resuelveCaso() {
	bintree<char> a = leerArbol('.');
	if (simetrico(a)) cout << "SI \n";
	else cout << "NO \n";
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos--) {
		resuelveCaso();
	}
	return 0;
}