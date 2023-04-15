///EDURNE RUIZ DG33
/*
Al archipi´elago Milislotes han llegado las bicicletas. Sus habitantes est´an estusiasmados y no se bajan de la bici en todo el d´ıa, 
yendo de un lado para otro sin descanso. Pero las islas son tan peque˜nas que terminan todos mareados de dar vueltas sin parar, por 
lo que se est´an planteando crear una red de puentes rectos que les permita ir en bici de cualquier isla a cualquier otra.

Han pedido presupuesto al arquitecto, que ha confeccionado una lista con todos los puentes que podr´ıan construirse entre islas del 
archipi´elago y cu´anto costar´ıa construir cada uno de esos puentes. ¿Podr´ıas ayudarles a decidir qu´e puentes construir de tal 
forma que se pueda ir en bici desde cualquier isla a cualquier otra y el coste total de la obra sea lo m´ınimo posible?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
using namespace std;

typedef struct {
	bool existe; //existe un  
	int c_min; //coste
} red_minima;

class Puentes {
	vector<Arista<int>> _ARM;
	int islas, puentes;
	red_minima min;

public:

	Puentes(int i, int p, GrafoValorado<int> const& g) : islas(i), puentes(p), min({ false, 0 }) {
		ARM_Kruskal(g);
	}

	bool existeRed() {
		return min.existe;
	}

	int costeMinimo() {
		return min.c_min;
	}

private:

	void ARM_Kruskal(GrafoValorado<int> const& g) {
		PriorityQueue<Arista<int>> pq(g.aristas()); 
		ConjuntosDisjuntos cjtos(g.V()); 
		while (!pq.empty()) { 
			auto a = pq.top(); pq.pop(); 
			int v = a.uno(), w = a.otro(v); 
			if (!cjtos.unidos(v, w)) { 
				cjtos.unir(v, w); 
				_ARM.push_back(a); min.c_min += a.valor();
				if (_ARM.size() == islas - 1)
					break;
			}
		}
		min.existe = (cjtos.num_cjtos() == 1); //si es conexo
	}
	
};

void inicializarGrafo(int p, GrafoValorado<int> & grafo) {
	int ini, fin, valor;
	while (p--) {
		cin >> ini >> fin >> valor;
		grafo.ponArista({ ini - 1, fin - 1, valor });
	}
}

bool resuelveCaso() {
	int i, p;
	cin >> i >> p;

	if (!std::cin)
		return false;
	else {
		GrafoValorado<int> g(i); inicializarGrafo(p, g);
		Puentes red(i, p, g);

		if (red.existeRed())
			cout << red.costeMinimo() << '\n';
		else
			cout << "No hay puentes suficientes \n";

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
5
1 2 5
1 3 10
2 4 7
1 4 8
3 4 2

4
3
1 2 3
2 4 5
4 1 8

salida:
14

No hay puentes suficientes

*/