///EDURNE RUIZ DG33
/*
A la vuelta de las vacaciones mi jefe ten´ıa preparada una larga lista de
tareas que tengo que hacer. Las tareas no son totalmente independientes
entre s´ı, por lo que algunas tareas solamente pueden ser realizadas cuando
se hayan terminado ya otras.
Primero he analizado todas las tareas, y he descubierto las relaciones
de precedencia directa entre algunos pares de tareas, es decir, cu´ando una
tarea A tiene que ser realizada antes que otra tarea B.
Ahora me falta decidir un orden en el que hacer todas las tareas de
forma que se respeten esas precedencias. O quejarme a mi jefe si eso es imposible.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Digrafo.h"
#include "TreeSet_AVL.h"
using namespace std;

typedef struct {
	int elem;
	int entrada;
	int salida;
} tGrados;

bool operator< (tGrados const& g1, tGrados const& g2) {
	return (g1.entrada < g2.salida) || (g1.entrada == g2.salida && g1.salida > g2.salida);
}

class tareas {
	Digrafo g;
	Digrafo inv;

	Set<tGrados> grados;

	int numt;

public:

	tareas(int v, int a) : numt(v), g(Digrafo(v)), inv(Digrafo(v)), grados(Set<tGrados>()) {
		int ini, fin;
		while (a--) {
			cin >> ini >> fin;
			g.ponArista(ini, fin);
			inv.ponArista(fin, ini);
		}
	}


};


bool resuelveCaso() {
	int tareas, relaciones;
	cin >> tareas >> relaciones;

	if (!std::cin)
		return false;
	else {
		
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
7
8
1 2
2 3
2 4
3 5
2 5
4 5
5 6
7 4

2
2
1 2
2 1

salida:
1 2 7 3 4 5 6

Imposible

*/