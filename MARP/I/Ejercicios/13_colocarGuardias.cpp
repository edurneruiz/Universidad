///EDURNE RUIZ DG33
/*
En el peque˜no pa´ıs de Abudajh hay algunas calles y cruces. Cada calle conecta dos cruces. El rey de Abudajh quiere colocar 
guardias en algunos cruces de forma que todas las calles queden custodiadas por ellos. Un guardia en un cruce puede
vigilar todas las calles adyacentes a ´el.
Pero los guardias no son muy gentiles. Si una calle est´a custodiada por dos guardias, estos terminar´an pele´andose. Y el rey 
no quiere que los guardias se peleen.
Dada la informaci´on sobre las calles y cruces de Abudajh, ayuda al rey a encontrar la cantidad m´ınima de guardias necesarios 
para proteger todas las calles de su pa´ıs sin que haya peligro de peleas.
*/

/*
Se trata de averiguar si el grafo es bipartito : se puede encontrar una partición en dos de los vértices t.q los vértices de un mismo
cjto no son adyacentes. Para ello, defino dos colores (0 azul y 1 rojo) y tomo un vértice origen. Lo pinto de un color y sus adyacentes 
del otrocolor, y los adyacentes de sus adyacentes del primer color, así etc... si encuentro un vertice ya marcado cuyo color coincida
con su adyacente, el grafo no es bipartito. 

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>
#include "Grafo.h"
using namespace std;

typedef struct {
	int azul;
	int rojo;
	bool si;
} es_bipartito;

class cruces_calles {
	int cruces, calles, min_guardias;
	Grafo mapa;

	es_bipartito bipartito;

public:
	
	cruces_calles(int cr, int cl) : cruces(cr), calles(cl), min_guardias(0), mapa(Grafo(cr)), bipartito({ 0,0,true }) {
		while (cl--) {
			int v1, v2;
			cin >> v1 >> v2;
			mapa.ponArista(v1 - 1, v2 - 1);
		}

		bfs();
	}

	bool bp() {
		return bipartito.si;
	}

	int guardias() {
		return min_guardias;
	}

private:
	
	void bfs() {
		vector<bool> marcados(cruces);
		vector<int> colores(cruces);
		for (int cr = 0; cr < cruces; ++cr) {
			if (!marcados[cr]) {
				es_bipartito bpt = b_fs(cr, marcados, colores);
				min_guardias += fmin(bpt.azul, bpt.rojo);
				bipartito.azul += bpt.azul; bipartito.rojo += bpt.rojo; bipartito.si = bipartito.si && bpt.si;
			}
		}
	}

	//entra al encontrar nueva comp conexa
	es_bipartito b_fs(int cruce, vector<bool> & marcados, vector<int> & colores) {
		queue<int> cola; int azules = 0, rojos = 0; bool si = true;

		marcados[cruce] = true; 
		colores[cruce] = 0; ++azules; //vertice origen de comp conexa lo pintamos azul
		cola.push(cruce);

		while (!cola.empty()) {
			int v = cola.front(); cola.pop();

			for (int ad : mapa.ady(v)) {
				if (!marcados[ad]) {
					marcados[ad] = true;
					colores[ad] = 1 - colores[v]; //el adyacente lo pintamos del otro color

					if (1 - colores[v] == 0)
						++azules;					
					else
						++rojos;

					cola.push(ad);
				}
				else
					si = si && (colores[v] != colores[ad]);
			}
		}

		return { azules, rojos, si };
	}
	
};

bool resuelveCaso() {
	int cruces, calles;
	cin >> cruces >> calles;

	if (!std::cin)
		return false;
	else {
		cruces_calles cc(cruces, calles);
		if (cc.bp())
			cout << cc.guardias() << '\n';
		else
			cout << "IMPOSIBLE \n";
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
8
6
1 3
2 3
3 4
4 5
6 4
7 8

3
1
1 2

3
3
1 2
2 3
3 1


salida:
4

1

IMPOSIBLE
*/