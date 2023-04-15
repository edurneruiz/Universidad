#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
using namespace std;

const float inf = FLT_MAX;
using info = pair<bool, float>;

class tNodo {
public:
	vector<int> sol;
	vector<bool> usado;
	int k; //nivel
	float coste, coste_estimado;

	tNodo(int n) : sol(vector<int>(n, 1)), usado(vector<bool>(n, false)), k(1), coste(0) {}

	bool operator<(const tNodo & other) const {
		return coste_estimado < other.coste_estimado;
	}

};

typedef struct {
	vector<int> sol;
	float coste_mejor;
} tSolucion;


//Calcular el mínimo valor de las aristas
///O(A), donde A es el número de aristas del grafo
float calculo_minimo(GrafoValorado<float> const& G) { 
	float min = inf;
	for (auto a : G.aristas()) {
		min = fmin(min, a.valor());
	}
	return min;
}

//dados dos vértices, ant y vert, devuelve si son adyacentes, y en caso afirmativo, también el coste de la arista
///O(C), donde C es el número de vértices adyacentes a el vértice 'ant'
info infoArista(int ant, int vert, GrafoValorado<float> const& G) {
	bool existe = false; float coste = inf;
	for (auto ady : G.ady(ant)) {
		if (ady.otro(ant) == vert) {
			existe = true; coste = ady.valor();
		}
	}
	return { existe, coste };
}

//Devuelve el orden en el que hay que recorrer los vértices del grafo tal que sea el ciclo hamiltoniano de coste mínimo
tSolucion viajanteRP(GrafoValorado<float> const& G) {
	int n = G.V(), minG = calculo_minimo(G), anterior; 
	float coste_mejor = inf;
	PriorityQueue<tNodo> pq; 
	tNodo x(n), y(n);
	tSolucion s;

	//inicializamos y 
	y.sol[0] = true; y.coste_estimado = n * minG;

	pq.push(y);
	while (!pq.empty() && pq.top().coste_estimado < coste_mejor) {
		y = pq.top(); pq.pop();

		//generamos los hijos de y
		x.k = y.k + 1; x.sol = y.sol; x.usado = y.usado;
		anterior = x.sol[x.k - 1];

		for (int vertice = 2; vertice < n; ++vertice) {
			info i = infoArista(anterior, vertice, G);
			if (!x.usado[vertice] && i.first) {
				x.sol[x.k] = vertice; x.usado[vertice] = true; x.coste = y.coste + i.second;
				if (x.k == n) {
					info ii = infoArista(s.sol[n], 1, G);
					float cc = x.coste + ii.second;
					if (i.first && cc < coste_mejor)
						s.sol = x.sol; s.coste_mejor = cc;
				}
				else {
					x.coste_estimado = x.coste + (n - x.k + 1)*minG;
					if (x.coste_estimado < coste_mejor)
						pq.push(x);
				}
				x.usado[vertice] = false;
			}
		}
	}

	return s;
}


bool resuelveCaso() {
	int n; cin >> n;

	if (!n)
		return false;
	else {
		GrafoValorado<float> G(n);
		for (int i = 0; i < n; ++i) {
			int v1, v2, vv;
			cin >> v1 >> v2 >> vv;
			G.ponArista({ v1,v2,vv });
		}

		tSolucion s = viajanteRP(G);
		cout << s.coste_mejor << '\n';

		return true;
	}
}


int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {}
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
