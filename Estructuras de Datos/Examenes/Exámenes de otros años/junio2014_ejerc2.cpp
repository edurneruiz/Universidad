#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	string nombre; //nombre de la puerta
	int drag; //nº de dragones que se encuentra antes de llegar a la puerta
} tPuerta;

const string vacio = "XXX";
const string amenaza = "Dragon";

tPuerta puertaMenosDragones(int dragonesEncontrados, bintree<string> & a) {
	if (a.empty())
		return { "", 0 };
	else {
		dragonesEncontrados = (a.root() == amenaza) ? ++dragonesEncontrados : dragonesEncontrados;
		bintree<string> iz = a.left(), d = a.right();

		if (iz.empty() && d.empty())
			return { a.root(), dragonesEncontrados };
		else if (iz.empty()) 
			return puertaMenosDragones(dragonesEncontrados, d);
		else if (d.empty()) 
			return puertaMenosDragones(dragonesEncontrados, iz);
		else {
			tPuerta piz = puertaMenosDragones(dragonesEncontrados, iz);
			tPuerta pd = puertaMenosDragones(dragonesEncontrados, d);

			return (piz.drag <= pd.drag) ? piz : pd;
		}
	}
}

string puertaFinal(bintree<string> & a) {
	return puertaMenosDragones(0, a).nombre;
}

bool resuelveCaso() {
	bintree<string> arbol = leerArbol(vacio);
	if (!std::cin) return false;

	cout << "El camino con menos dragones termina en la " << puertaFinal(arbol) << "\n---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
Tesoro ViaLibre Dragon Dragon XXX PuertaDelEste XXX XXX PuertaFalsa XXX XXX XXX Dragon XXX ViaLibre Dragon PuertaGrande XXX XXX PuertaVerde XXX XXX ViaLibre XXX PuertaDelOeste XXX XXX
Tesoro ViaLibre PuertaEdur XXX XXX Dragon PuertaNemo XXX XXX Dragon PuertaPingu XXX XXX PuertaTxili XXX XXX Dragon XXX ViaLibre XXX PuertaJose XXX XXX
Tesoro ViaLibre XXX Dragon XXX Dragon PuertaPingu XXX XXX PuertaTxili XXX XXX Dragon XXX ViaLibre XXX PuertaJose XXX XXX
Tesoro ViaLibre XXX Dragon XXX Dragon PuertaPingu XXX XXX PuertaTxili XXX XXX XXX

*/
