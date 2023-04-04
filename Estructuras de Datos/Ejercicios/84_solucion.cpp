#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "bintree_eda.h"
#include "list_eda.h"
using namespace std;

typedef struct {
	int nodos;
	int altura;
	int hojas;
	list<int> altura_hojas;
} tArbol;

list<int> unir(tArbol& a, list<int>& iz, list<int> d) {
	list<int> q;
	if (iz.empty() && d.empty()) { q.push_front(a.altura); }
	else {
		while (!iz.empty()) {
			q.push_back(iz.front() + 1);
			iz.pop_front();
		}
		while (!d.empty()) {
			q.push_back(d.front() + 1);
			d.pop_front();
		}
	}
	return q;
}

string completitud(tArbol a) {
	if (a.hojas == pow(2, a.altura - 1)) return "COMPLETO";
	else if (a.nodos < pow(2, a.altura) - pow(2, a.altura - 1)) return "NADA";
	else if (a.altura_hojas.front() != a.altura) return "NADA";
	else {
		bool posicion_rellenar = false; // true cuando se llega a la posición a partir de la cual es necesario rellenar para que sea completo
		auto it = a.altura_hojas.begin();

		while (it != a.altura_hojas.end()) {
			if (!posicion_rellenar && *it == a.altura - 1)
				posicion_rellenar = true;

			if (*it < a.altura - 1 || (posicion_rellenar && *it != a.altura - 1))
				return "NADA";

			++it;
		}

		if (!posicion_rellenar && a.hojas != pow(2, a.altura - 1))
			return "NADA";

		return "SEMICOMPLETO";
	}
}

tArbol infoArbol(bintree<char>& a) { //nodos, altura, nº hojas, pila con la altura de las hojas
	if (a.empty()) return { 0,0,0,list<int>() };
	else {
		bintree<char> iz = a.left();
		bintree<char> dcho = a.right();
		tArbol diz = infoArbol(iz);
		tArbol ddcho = infoArbol(dcho);
		tArbol aa;

		aa.nodos = diz.nodos + ddcho.nodos + 1;
		aa.altura = fmax(diz.altura, ddcho.altura) + 1;
		aa.hojas = (iz.empty() && dcho.empty()) ? 1 : diz.hojas + ddcho.hojas;
		aa.altura_hojas = unir(aa, diz.altura_hojas, ddcho.altura_hojas);
		return aa;
	}
}

bool resuelveCaso() {
	if (!std::cin) return false;
	bintree<char> arbol = leerArbol('.');
	tArbol aa = infoArbol(arbol);
	cout << completitud(aa) << "\n";
	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos != 0) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}



