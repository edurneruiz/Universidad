///EDURNE RUIZ DG33
/*
Lucas va todos los d´ıas en bici al cole. Como le cuesta una barbaridad levantarse por las ma˜nanas, 
siempre lleva prisa y tiene que ir por el camino m´as corto.
Pero le aburre ir siempre por el mismo camino, por lo que va alternando, eso s´ı,
recorriendo siempre la misma distancia m´ınima, para no llegar tarde. Como es un
poco temerario, no respeta el sentido de circulaci´on de las calles por lo que es capaz
de recorrer cualquiera de ellas en ambos sentidos. Ahora se pregunta de cu´antas
formas distintas puede ir de su casa al colegio sin recorrer ni un cent´ımetro de m´as
*/

/*
Algoritmo de Dijkstra
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include "IndexPQ.h"
#include "GrafoValorado.h"
using namespace std;

class ciudad {
	const int INF = INT_MAX;
	int origen, destino;
	vector<int> dist;

	GrafoValorado<int> dg;
public:

	ciudad(int v) : dg(v), origen(0), destino(v - 1), dist(v, INF), pq(v), caminos(v) {
		inicializar();
		dijkstra();
	}

	int caminos_distintos() {
		return caminos[destino];
	}

private:
	IndexPQ<int> pq;
	vector<int> caminos; //en la posición i-ésima guarda el nº de caminos que existen con el mínimo coste desde 0 hasta i

	void inicializar() {
		int v1, v2, vv, m;
		cin >> m;
		while (m--) {
			cin >> v1 >> v2 >> vv;
			dg.ponArista( { v1 - 1, v2 - 1, vv });
		}
	}

	void dijkstra() {
		dist[origen] = 0; caminos[origen] = 1;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();

			for (auto a : dg.ady(v))
				relajar(a, v);
		}
	}

	void relajar(Arista<int> a, int v) {
		int w = a.otro(v);
		if (dist[w] > dist[v] + a.valor()) {
			caminos[w] = caminos[v];
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor()) {
			caminos[w] += caminos[v];
		}
	}
};

bool resuelveCaso() {
	int v;
	cin >> v;

	if (!std::cin)
		return false;
	else {
		ciudad c(v);
		cout << c.caminos_distintos() << '\n';
		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos24.txt");
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

