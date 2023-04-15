///EDURNE RUIZ DG33
/*
Un arbol AVL es un arbol binario de busqueda equilibrado en el sentido de que para todo
subárbol se cumple que la diferencia entre las alturas de sus dos hijos es como mucho 1. Ademas, por ser
de busqueda, tambien se cumple que la clave almacenada en la raız de cualquier subarbol es estrictamente
mayor que todas las claves en su hijo izquierdo y estrictamente menor que todas las claves en su hijo
derecho.
*/
#include <iostream>
#include <climits>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	bool eq; // es equilibrado o no
	int h; //altura del arbol 
	int min; //raiz -> el mayor de los menores
	int max; //menor de los mayores
} info_arbol;

bool compare_sons(info_arbol const& i_l, info_arbol const& i_r, bintree<int> const& a) {
	bool b1 = (i_l.max == INT_MAX) ? true : (i_l.max < a.root());
	bool b2 = (i_r.min == INT_MIN) ? true : (a.root() < i_r.min);
	return b1 && b2;
}

info_arbol es_avl(bintree<int> const& a) {
	if (a.empty())
		return { true, 0, INT_MIN, INT_MAX };
	else {
		bintree<int> l = a.left(), r = a.right();
		info_arbol i_l = es_avl(l);
		info_arbol i_r = es_avl(r);
		int h = fmax(i_l.h, i_r.h) + 1; 

		return { abs(i_l.h - i_r.h) <= 1 && i_l.eq && i_r.eq && compare_sons(i_l, i_r, a), 
			h, 
			(i_l.min == INT_MIN) ? a.root() : i_l.min, 
			(i_r.max == INT_MAX) ? a.root() : i_r.max };
	}
}

bool es_AVL(bintree<int> const& a) {
	return es_avl(a).eq;
}

void resuelveCaso() {
	bintree<int> t = leerArbol(-1);

	if (es_AVL(t))
		cout << "SI \n";
	else
		cout << "NO \n";
}


int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	return 0;
}

/*
3
2 1 -1 -1 3 -1 4 -1 -1
1 -1 3 2 -1 -1 4 -1 -1
4 1 -1 -1 3 -1 2 -1 -1

SI
NO
NO

*/