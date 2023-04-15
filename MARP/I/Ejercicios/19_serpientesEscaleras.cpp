///EDURNE RUIZ DG33
/*
El tablero est´a formado por una cuadr´ıcula de N ×N casillas numeradas de forma consecutiva desde 1 hasta NxN, comenzando por la 
esquina inferior izquierda y continuando fila por fila de abajo arriba, alternando en cada fila el ir hacia la izquierda o hacia 
la derecha, como aparece en el dibujo. Algunos pares de casillas, siempre en filas diferentes, pueden estar conectados mediante 
serpientes (que bajan, naranjas en el dibujo) o escaleras (que suben, azules en el dibujo). Cada casilla puede ser extremo de
como mucho una serpiente o una escalera. La primera y la ´ultima casilla nunca son extremos de una serpiente o escalera.

Todas las fichas comienzan en la casilla n´umero 1. Los jugadores van altern´andose para mover su ficha. Para ello, tiran un dado 
con K caras numeradas desde 1 hasta K, y avanzan su ficha siguiendo la numeraci´on del tablero tantas casillas como indique el dado. 
Si la ficha termina en el extremo superior de una serpiente, se deslizar´a hasta su extremo inferior. En cambio, si termina en el 
extremo inferior de una escalera, ascender´a hasta su extremo superior. Gana la partida el jugador que antes alcance la ´ultima casilla.
El juego as´ı planteado no requiere ninguna destreza. Pero supongamos que has trucado el dado y tienes el poder de elegir la cara
que saldr´a cada vez que lo tiras. ¿Sabes cu´antos movimientos tendr´ıas que hacer para ganar la partida si comienzas moviendo t´u?

*/

#include <iostream>
#include "Digrafo.h"
#include <fstream>
#include <string>
#include <cmath>
#include <deque>
using namespace std;


class Tablero {

	Digrafo tablero;
	deque<int> visitadas;
	int casillas, serpientes, escaleras;

	int dado;

public :

	//inicializamos un grafo con NxN vértices y determinamos las esacleras y serpientes del juego
	Tablero(int c, int d, int s, int e) : tablero(c), dado(d), casillas(c), serpientes(s), escaleras(e), visitadas(deque<int>()) {
		annadirSerpientes();
		annadirEscaleras();
	}


private:


	void annadirSerpientes() {
		int s = serpientes, ini, fin;
		while (s--) {
			cin >> ini >> fin;
			tablero.ponArista(ini, fin);
		}
	}

	void annadirEscaleras() {
		int e = escaleras, ini, fin;
		while (e--) {
			cin >> ini >> fin;
			tablero.ponArista(ini, fin);
		}
	}


};

bool resuelveCaso() {
	int dim, k, serp, escal;
	cin >> dim >> k >> serp >> escal;

	if (dim == 0 && k == 0 && serp == 0 && escal == 0)
		return false;
	else {
		dim = dim * dim;
		Tablero t(dim, k, serp, escal);
		//cout << t.minimo_tiradas() << '\n';

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
10 6 5 6
50 13
68 55
81 16
93 43
98 36
3 60
6 47
32 53
45 86
51 94
61 83

0 0 0 0

salida:
3 ->

*/