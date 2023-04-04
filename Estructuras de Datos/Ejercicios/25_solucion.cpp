#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int multiplo;
	int altura;
	bool encontrado;
} tPar;

//funciones
tPar busqueda(bintree<int>& a);
bool esPrimo(int n);
tPar determinarNodo(tPar i, tPar d);

bool resuelveCaso() {

	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	tPar a = busqueda(arbol);
	if (a.encontrado) cout << a.multiplo << " " << a.altura << '\n';
	else cout << "NO HAY \n";

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

tPar busqueda(bintree<int>& a) {
	tPar p = { 0,0,false };

	if (a.empty()) return p;
	else {
		if (esPrimo(a.root())) return p;
		else {
			if (a.root() % 7 == 0) return { a.root(), 1, true };
			else {
				bintree<int> izq = a.left();
				bintree<int> dcha = a.right();

				tPar p_iz = busqueda(izq);
				if (p_iz.encontrado) ++p_iz.altura;
				tPar p_d = busqueda(dcha);
				if (p_d.encontrado) ++p_d.altura;

				p = determinarNodo(p_iz, p_d);

				return p;

			}
		}
	}

}
	
tPar determinarNodo(tPar i, tPar d) {

	if (!i.encontrado && !d.encontrado) return { 0,0,false };
	else if (!i.encontrado && d.encontrado) return d;
	else if (i.encontrado && !d.encontrado) return i;
	else {
		if (d.altura < i.altura) return d;
		else return i;
	}

}


bool esPrimo(int n) {
	bool p = false;
	int i = 2;
	while (i < n && !p) {
		p = (n % i == 0);
		++i;
	}
	return !p;
}