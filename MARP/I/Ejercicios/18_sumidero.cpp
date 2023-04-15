///EDURNE RUIZ DG33
/*
Un v´ertice s de un grafo dirigido se llama sumidero si para cualquier otro v´ertice v del grafo existe
una arista de v a s pero no de s a v, es decir, su grado de salida es 0 y su grado de entrada es V − 1
siendo V el n´umero de v´ertices del grafo.
El problema consiste en, dado un grafo dirigido, determinar si tiene sumidero o no, y en caso de
tenerlo, indicar qu´e v´ertice es sumidero.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Digrafo.h"
#include "TreeSet_AVL.h"
using namespace std;


class dig {
	Digrafo g;
	int vertices;
public:

	dig(int v, int a) : g(v), vertices(v) {
		while (a--) {
			int ini, fin;
			cin >> ini >> fin;
			g.ponArista(ini, fin);
		}
	}

	int tiene_Sumidero() {
		Digrafo inv = g.inverso();

		int v = 0; bool si = false;
		while (v < vertices && !si) {
			si = (g.ady(v).size() == 0) && (inv.ady(v).size() == vertices - 1);
			++v;
		}

		return (si) ? v - 1 : -1;
	}

};


bool resuelveCaso() {
	int v, a;
	cin >> v >> a;

	if (!std::cin)
		return false;
	else {
		dig _grafo(v, a);
		int sum = _grafo.tiene_Sumidero();

		if (sum == -1)
			cout << "NO";
		else
			cout << "SI " << sum;

		cout << "\n";
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
4
4
1 0
0 2
3 2
1 2

4
5
0 1
0 2
1 2
1 3
2 3
salida:

SI 2

NO

*/