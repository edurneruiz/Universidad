#include <iostream>
#include "bintree_eda.h"
using namespace std;


bool ramasSimetricas(bintree<char> & l, bintree<char> & r) {

	if (l.empty() && r.empty()) //si ambos �rboles que comparamos son vac�os, son sim�tricos
		return true;
	else if (l.empty() || r.empty())  //si uno es vac�o y el otro no, no son sim�tricos
		return false;
	else {
		bintree<char> l_iz = l.left(), l_d = l.right(), r_iz = r.left(), r_d = r.right();
		bool exteriorSimetrico = ramasSimetricas(l_iz, r_d); //averiguamos si las ramas externas son sim�tricas
		bool interiorSimetrico = ramasSimetricas(l_d, r_iz); //averiguamos si las ramas internas son sim�tricas

		return exteriorSimetrico && interiorSimetrico; //si tanto las ramas internas como externas son sim�tricas, el �rbol es sim�trico
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