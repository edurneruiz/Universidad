///EDURNE RUIZ DG33
/*
Dado un bitmap de p´ıxeles blancos y negros, queremos saber el n´umero de manchas negras que
contiene y el tama˜no (n´umero de p´ıxeles) de la mancha negra m´as grande. Dos p´ıxeles negros pertenecen
a la misma mancha si se puede pasar de uno a otro atravesando solamente p´ıxeles negros y movi´endonos
p´ıxel a p´ıxel solamente en horizontal o vertical.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Grafo.h"
using namespace std;
using c_map = vector<vector<char>>;
using b_map = vector<vector<bool>>;

typedef struct {
	int fila;
	int columna;
} celda;

class Bitmap {
	c_map mapa;
	int F, C;
public:

	Bitmap(int filas, int cols) : F(filas), C(cols), mapa(filas, vector<char>(cols, ' ')), visitados(filas, vector<bool>(cols, false)) {
		for (int f = 0; f < filas; ++f) {
			for (int c = 0; c < cols; ++c) {
				cin >> mapa[f][c];
			}
		}
	}

	std::pair<int, int> manchas() {
		return detectarManchas();
	}
	
private:
	vector<celda> direcciones = { {1,0}, {0,1}, {-1, 0}, {0, -1} };
	b_map visitados;

	bool celdaDentro(celda c) {
		return 0 <= c.fila && c.fila < F && 0 <= c.columna && c.columna < C;
	}

	bool esMancha(celda c) {
		return mapa[c.fila][c.columna] == '#';
	}

	std::pair<int, int> detectarManchas() {
		int manchas = 0, mayor= 0;
		for (int f = 0; f < F; ++f) {
			for (int c = 0; c < C; ++c) {
				celda cc = { f,c };
				if (esMancha(cc) && !visitados[cc.fila][cc.columna]) {
					++manchas;
					int t = dfs(cc);
					mayor = fmax(mayor, t);
				}
			}
		}

		return { manchas, mayor };
	}

	int dfs(celda c) {
		visitados[c.fila][c.columna] = true;
		int tam = 1;
		for (celda d : direcciones) {
			celda cc = { c.fila + d.fila, c.columna + d.columna };
			if (celdaDentro(cc) && esMancha(cc) && !visitados[cc.fila][cc.columna])
				tam += dfs(cc);
		}
		return tam;
	}


};

bool resuelveCaso() {
	int f, c;
	cin >> f >> c;

	if (!std::cin)
		return false;
	else {
		Bitmap bm(f,c);
		std::pair<int, int> mc = bm.manchas();

		cout << mc.first << " " << mc.second << '\n';

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
8 8
-#-#---#
-###---#
----####
-#------
-#-#----
-###-##-
###--##-
--#-----

4 10
#-#-#-###-
#-#-#-#-#-
#-#-#-#-#-
#-#-#-#-#-


salida: 
4 10

4 9
*/