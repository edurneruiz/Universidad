#include <iostream>
#include <vector>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int n; //nº de nodos singulares que hay en ese árbol
	int sumaDescendientes; //suma total de sus descendientes 
} tNodo;


bool nodoSingular(int sumaAntepasados, bintree<int> & a, int sumaDescendientes) {
	return sumaAntepasados + a.root() == sumaDescendientes;
}

//devuelve el nº de nodos singulares del árbol A y la suma total de sus hijos (la raíz inclusive)
tNodo nodosSingulares(int sumaAntepasados, bintree<int> & a) {
	if (a.empty())
		return { 0,0 };
	else {
		bintree<int> iz = a.left(), dcho = a.right();
		tNodo niz = nodosSingulares(sumaAntepasados + a.root(), iz);
		tNodo nd = nodosSingulares(sumaAntepasados + a.root(), dcho);
		int sumaDescendientes = niz.sumaDescendientes + nd.sumaDescendientes, nodos = niz.n + nd.n;

		return { (nodoSingular(sumaAntepasados, a, sumaDescendientes)) ? nodos + 1 : nodos,
				sumaDescendientes + a.root() };
	}
}

int numNodosSingulares(bintree<int> & a) {
	return nodosSingulares(0, a).n;
}

bool resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	if (!std::cin) return false;

	tNodo n = nodosSingulares(0, arbol);
	cout << "El arbol tiene " << numNodosSingulares(arbol) << " nodo(s) singular(es)" << "\n---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
14 4 2 -1 -1 2 -1 -1 3 1 -1 -1 2 -1 -1   
5 4 6 -1 -1 3 -1 -1 3 1 -1 -1 7 -1 -1	
1 1 1 -1 -1 1 -1 -1 -1					
1 1 -1 -1 1 -1 -1						

--> 1 nodo singular (14)
--> 2 nodos singulares(4,3)
--> 1 nodo singular (1)
--> 0 nodos singulares
*/