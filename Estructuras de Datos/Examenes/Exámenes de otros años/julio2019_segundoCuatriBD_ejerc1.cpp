#include<iostream>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int nSum; //nodos internos sumativos en el árbol
	int sumaTotal; //suma total de sus descendientes
} tArbol;

tArbol nodos(bintree<int> & a) {
	if (a.empty())
		return { 0,0 };
	else {
		bintree<int> iz = a.left(), dcho = a.right();
		if (iz.empty() && dcho.empty()) //un nodo hoja tiene 0 nodos internos sumativos
			return { 0, a.root() };
		else {
			tArbol iiz = nodos(iz);
			tArbol id = nodos(dcho);

			return { (a.root() == iiz.sumaTotal + id.sumaTotal) ? iiz.nSum + id.nSum + 1 : iiz.nSum + id.nSum,
					iiz.sumaTotal + id.sumaTotal + a.root() };
		}
	}
}

int numNodosSumativos(bintree<int> & a) {	if (a.empty()) return 0;	else return nodos(a).nSum;}
bool resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	if (!std::cin) return false;

	cout << numNodosSumativos(arbol) << "\n --- \n";
	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}

/*

2 1 -1 -1 1 -1 -1
10 2 -1 0 -1 -1 4 4 -1 -1 -1

*/