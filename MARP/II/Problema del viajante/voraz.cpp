#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "Matriz.h"
using namespace std;

using grafo = Matriz<float>;
const float inf = FLT_MAX;

typedef struct {
	vector<int> orden;
	float coste;
} tCiclo;

void print(tCiclo const& sol) {
	if (sol.coste == inf)
		cout << "No existe un ciclo hamiltoniano en el grafo dado" << '\n';
	else {
		cout << "El orden de recorrido de las ciudades es: ";
		for (int i = 0; i < sol.orden.size(); ++i)
			cout << sol.orden[i] << " ";
		cout << ", con coste " << sol.coste << '\n';
	}
}

//devuelve true si existe carretera entre dos ciudades
bool existeCarretera(int c1, int c2, grafo const& G) {
	if (G[c1][c2] == inf)
		return false;
	else
		return true;
}

//dada una ciudad (vértice del grafo), devuelve la ciudad más cercana a ésta que aún no ha sido visitada
int ciudadMasCercana(int n, int v, grafo const& G, vector<bool> const& visitadas) {
	int u = -1; float min = inf;
	for (int i = 0; i < n && i != v; ++i) {
		if (G[v][i] < min && !visitadas[i]) {
			min = G[v][i];
			u = i;
		}
	}

	return u;
}

//Devuelve el orden en el que hay que recorrer los vértices del grafo tal que sea el ciclo hamiltoniano de coste mínimo
tCiclo viajanteRP(grafo const& G) {
	int n = G.numfils(), visit = 0, mc, c = 0; bool si = true;
	tCiclo sol = { vector<int>(n,-1), 0 };
	vector<bool> visitadas(n, false);

	//consideramos la primera ciudad como la ciudad del vértice 1
	sol.orden[0] = c; ++visit;
	while (visit <= n && si) {
		mc = ciudadMasCercana(n, c, G, visitadas);

		if (mc == -1) //no existe ninguna carretera
			si = false;
		else {
			++visit; sol.orden[visit] = mc; visitadas[mc] = true;
			sol.coste += G[c][mc];
			c = mc;
		}
	}

	if (existeCarretera(0, c, G) && si)
		sol.coste += G[sol.orden[0]][sol.orden[n - 1]];
	else
		sol.coste = inf;

	return sol;
}


bool resuelveCaso() {
	int n, m; cin >> n >> m;

	if (!std::cin)
		return false;
	else {
		grafo G(n, n, inf);
		for (int i = 0; i < n; ++i)
			G[i][i] = 0;
		for (int i = 0; i < m; ++i) {
			int v1, v2; float vv;
			cin >> v1 >> v2 >> vv;
			G[v1][v2] = vv; G[v2][v1] == vv;
		}

		tCiclo sol = viajanteRP(G);
		print(sol);
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


/*

auto start_time = high_resolution_clock::now();

	tsp.nodeTraverse(start);

	auto end_time = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(end_time - start_time);

	cout << "Time taken for finding the tour is: "
		 << duration.count() << " micro secs" << endl;
*/