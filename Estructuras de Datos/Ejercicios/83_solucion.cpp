#include <iostream>
#include <fstream>
#include <cmath>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	int alt;
	int max;
} tPar;

//funciones
tPar subarbolMayor(bintree<char>& a);

bool resuelveCaso() {
	if (!std::cin) return false;
	bintree<char> arbol = leerArbol('.');
	tPar p = subarbolMayor(arbol);
	cout << p.max << '\n';
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

tPar subarbolMayor(bintree<char>& a) { //devuelve la altura del arbol completo que forma desde la raíz y la altura de su subarbol mayor
	if (a.empty()) return { 0, 0 };
	else {
		bintree<char> izq = a.left();
		bintree<char> dcho = a.right();
		tPar p_i = subarbolMayor(izq), p_d = subarbolMayor(dcho);

		if (izq.empty() && dcho.empty()) return { 1, 1 }; //si es un árbol hoja, es completo de altura 1
		else if (izq.empty() || dcho.empty()) { //si solo tiene un hijo, es un árbol completo de altura 1
			int max = fmax(p_i.max, p_d.max); //para calcular la altura del subarbol completo mayor
			return { 1, max };
		}
		else { //tiene ambos hijos
			int min = fmin(p_i.alt + 1, p_d.alt + 1); //para calcular la altura del árbol completo que forma con la raíz
			int max = max = fmax(min, fmax(p_i.max, p_d.max)); //para calcular la altura del subarbol completo mayor 
			return { min, max };
		}
	}
}
