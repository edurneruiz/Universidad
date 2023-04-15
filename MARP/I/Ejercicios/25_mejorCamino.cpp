///EDURNE RUIZ DG33
/*
Nº de veces que ell camino más corto en distancia sea también el que pasa por menos calles.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include "IndexPQ.h"
#include "GrafoValorado.h"
using namespace std;

typedef struct {
	int dist; //distancia minima a vertice
	int pasos; //vertices visitados antes de llegar a vertice cuando la distancia es mínima
	int minpasos; //el minimo nº de pasos para llegar al vertice
} camino;

class mejorCamino {
	const int INF = INT_MAX;
	int origen, destino;
	vector<camino> c; //en la posición i-ésima, guarda: la dist minima del origen a i, la longitud del camino min,
					  //y el minimo nº de pasos para llegar del origen a i

public:
	mejorCamino(int o, int d, GrafoValorado<int> const& g) : origen(o), destino(d), c(g.V(), { INF, INF, INF }), pq(g.V()) {
		dijkstra(g);
	}

	void print() {
		if (hayCamino()) {
			cout << distMinima() << ' ';
			if (coinciden())
				cout << "SI \n";
			else
				cout << "NO \n";
		}
		else
			cout << "SIN CAMINO \n";
	}

	bool hayCamino() {
		return c[destino].dist != INF;
	}

	bool coinciden() {
		return c[destino].pasos == c[destino].minpasos;
	}

	int distMinima() {
		return c[destino].dist;
	}

private:
	IndexPQ<int> pq;

	void dijkstra(GrafoValorado<int> const& g) {
		c[origen] = { 0,0,0 };
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();

			for (auto a : g.ady(v))
				relajar(a, v);
		}
	}

	void relajar(Arista<int> a, int v) {
		int w = a.otro(v), valor = a.valor();

		c[w].minpasos = fmin(c[w].minpasos, c[v].pasos + 1);

		if (c[w].dist > c[v].dist + valor) {
			c[w].dist = c[v].dist + valor;
			c[w].pasos = c[v].pasos + 1;
			pq.update(w, c[w].dist);
		}
		
	}

};

void consultas(GrafoValorado<int> & g) {
	int k, o, d; cin >> k;
	while (k--) {
		cin >> o >> d;
		mejorCamino mc(o - 1, d - 1, g);
		mc.print();
	}
	cout << "--- \n";
}

void inicializarGrafo(GrafoValorado<int> & g) {
	int a, v1, v2, vv; 
	cin >> a;
	while (a--) {
		cin >> v1 >> v2 >> vv;
		g.ponArista({ v1 - 1,v2 - 1,vv });
	}
}

bool resuelveCaso() {
	int v; cin >> v;

	if (!std::cin)
		return false;
	else {
		GrafoValorado<int> g(v); 
		inicializarGrafo(g);
		consultas(g);

		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos25.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}