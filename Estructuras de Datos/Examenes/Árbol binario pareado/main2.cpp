// EDURNE RUIZ HUGUET, DG28

/*
La soluci�n consiste en una llamada recursiva a cada nodo del �rbol, en la cual tratamos a cada nodo como un �rbol en si mismo.
Si el �rbol es vac�o, es pareado por defecto, pero en el caso de que no lo sea, hacemos llamada recursiva con sus hijos (izquierdo
y derecho). Si ambos hijos son pareados, y la diferencia de n� pares entre ellos es 0 o 1, entonces nuestro �rbol tambi�n ser� pareado.

Como recorremos todos los nodos del arbol, el programa tiene un coste O(n), donde n es el n� de nodos. 
*/


#include <iostream>                                                            
#include <fstream>               
#include <algorithm>
#include <cmath>
#include "bintree_eda.h"
using namespace std;


typedef struct {
	int numPares; 
	bool pareado;
} tArbol;

//devuelve el n� de pares que hay en el �rbol y si es pareado o no
tArbol esPareado(bintree<int> & a) {
	if (a.empty()) //si es vac�o, no tiene pares y es pareado por defecto
		return { 0, true };
	else {
		bintree<int> iz = a.left(), dr = a.right();
		tArbol niz = esPareado(iz); //llamada recursiva para encontrar informaci�n del hijo izquierdo
		tArbol ndr = esPareado(dr); //llamada recursiva para encontrar informaci�n del hijo derecho

		return { (a.root() % 2 == 0) ? niz.numPares + ndr.numPares + 1 : niz.numPares + ndr.numPares, 
				 (abs(niz.numPares - ndr.numPares) < 2) && niz.pareado && ndr.pareado };
	}
}

//devuelve si un �rbol es pareado o no
bool pareado(bintree<int> & a) {
	return esPareado(a).pareado;
}

void resuelveCaso() {
	auto arbol = leerArbol(-1);
	if (pareado(arbol))
		cout << "SI\n";
	else
		cout << "NO\n";
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
	//system("PAUSE");
#endif
	return 0;
}
