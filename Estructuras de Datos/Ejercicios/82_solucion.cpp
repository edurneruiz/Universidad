#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int caudal;
	int navegables;
} tPar;

//funciones
tPar tramosNavegables(bintree<int>& a);

bool resuelveCaso() {
	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	tPar n = tramosNavegables(arbol);
	cout << n.navegables << '\n';
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

tPar tramosNavegables(bintree<int>& a) { // caudal, navegables hasta ese embalse

	if (a.empty()) return { 0,0 };
	else {
		bintree<int> izq = a.left();
		bintree<int> dcho = a.right();

		if (izq.empty() && dcho.empty()) return { 1,0 }; //afluentes que nacen de los manantiales llevan un caudal de 1
		else {
			tPar p_iz = tramosNavegables(izq), p_d = tramosNavegables(dcho);
			int caudal, navegables;
			caudal = (p_iz.caudal + p_d.caudal - a.root() < 0) ? 0 : p_iz.caudal + p_d.caudal - a.root(); //el caudal del tramo como la suma de los caudales de sus afluentes menos lo retenido en el embalse
			navegables = p_iz.navegables + p_d.navegables; 
			if (p_iz.caudal >= 3) ++navegables; //un tramo es navegable si contiene un caudal mayor o igual a 3 
			if (p_d.caudal >= 3) ++navegables; 
			return { caudal,navegables };
		}
	}
}