///EDURNE RUIZ DG33
/*


*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <deque>
#include "GrafoValorado.h"
using namespace std;

class Ciudad {
	int intersecciones, calles;
	GrafoValorado<int> grafo;

public:
	Ciudad(int i, int ca) : intersecciones(i), calles(ca), grafo(i) {
		int ini, fin, valor;
		while (ca--) {
			cin >> ini >> fin >> valor;
			grafo.ponArista(Arista<int>(ini - 1, fin - 1, valor));
		}
	}

	bool puedeCircular(int desde, int hasta, int anchura) {
		return circula(desde, hasta, anchura);
	}

private:

	bool circula(int desde, int hasta, int anchura) {
		bool puede = false;
			
		for (auto ady : grafo.ady(desde)) {
			if (ady.valor() <= anchura) {
				if (ady.uno() == hasta)
					puede = true;
				else
					circula(ady.uno(), hasta, anchura);
			}	
		}
		return puede;
	}
};

bool resuelveCaso() {
	int v, a;
	cin >> v >> a;

	if (!std::cin)
		return false;
	else {
		Ciudad c(v, a);
		int k, ini, fin, anch; cin >> k;

		while (k--) {
			cin >> ini >> fin >> anch;
			if (c.puedeCircular(ini - 1, fin - 1, anch))
				cout << "SI \n";
			else
				cout << "NO \n";
		}
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
5
5
1 2 10
1 3 30
2 4 20
3 4 15
4 5 12
3
1 5 8
1 4 12
2 5 15


salida:
SI
SI
NO
*/