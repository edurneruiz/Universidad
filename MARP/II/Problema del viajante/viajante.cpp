#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include "Matriz.h"
#include "voraz.h"
#include "RyP.h"
#include "pd.h"
using namespace std;
using namespace std::chrono;
using lli = long long int;
using sol = pair<lli, float>;
const float inf = FLT_MAX;

void resolverVoraz(grafo const& G) {
	auto start_time = high_resolution_clock::now();

	solucionVoraz v(G);

	auto end_time = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end_time - start_time);

	cout << "El tiempo tomado para resolver problema mediante METODO VORAZ: "
		<< duration.count() << " micro secs" << endl;
}

sol resolverRamificacionPoda(grafo const& G, float min) {
	auto start_time = high_resolution_clock::now();

	solucionRamificacionPoda rp(G, min);

	auto end_time = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end_time - start_time);

	//cout << "El tiempo tomado para resolver problema mediante RAMIFICACION Y PODA es de "
		//<< duration.count() << " micro secs" << endl;
	return { duration.count(), rp.getCoste() };
}

sol resolverProgramacionDinamica(grafo const& G) {
	auto start_time = high_resolution_clock::now();

	solucionProgramacionDinamica pd(G);

	auto end_time = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end_time - start_time);

	//pd.print();
	//cout << "El tiempo tomado para resolver problema mediante PROGRAMACION DINAMICA es de "
		//<< duration.count() << " micro secs" << endl;
	return { duration.count(), pd.getCoste() };
}

void leerGrafo(int n, int m, grafo & G, float & min) {
	for (int i = 0; i < n; ++i)
		G[i][i] = 0;
	for (int i = 0; i < m; ++i) {
		int v1, v2; float vv;
		cin >> v1 >> v2 >> vv;
		min = fmin(min, vv);
		G[v1][v2] = vv; G[v2][v1] = vv;
	}
}

void leerGrafo2(int n, grafo & G, float & min) {
	int aux = 0;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		min = fmin(min, aux);
		for (int j = i + 1; j < n; ++j) {
			G[i][j] = aux; G[j][i] = aux;
		}
	}
}

void leerGrafo3(int n, grafo & G) {
	for (int i = 0; i < n - 1; ++i) {
		G[i][i + 1] = 1; G[i + 1][i];
	}
	G[0][n - 1] = 1; G[n - 1][0] = 1;
}

void print(int it, lli rp, lli pd, float coste) {
	cout << "Tras ejecutar " << it << " veces, " << '\n';
	cout << "    el algoritmo de Ramificacion y Poda ha tardado de media " << rp << " microsegundos" << '\n';
	cout << "    el algoritmo de Programacion Dinamica ha tardado de media " << pd << " microsegundos" << '\n';

	if (coste == inf)
		cout << "No existe ciclo hamiltoniano \n";
	else
		cout << "El ciclo hamiltoniano de menor coste es de coste " << coste << '\n';
}

void resolver(grafo const& G, float const& min) {
	lli rp = 0, pd = 0; int it = 100;

	auto dRP = resolverRamificacionPoda(G, min);
	auto dPD = resolverProgramacionDinamica(G);
	rp += dRP.first; 
	pd += dPD.first;

	for (int i = 0; i < it - 1; ++i) {
		auto _dRP = resolverRamificacionPoda(G, min);
		auto _dPD = resolverProgramacionDinamica(G);
		rp += _dRP.first; 
		pd += _dPD.first;
	}
	rp /= it; pd /= it;
	
	print(it, rp, pd, dRP.second);
}

bool resuelveCaso() {
	int n, m; cin >> n >> m;

	if (!std::cin)
		return false;
	else {
		grafo G(n, n, inf); float min = inf;
		leerGrafo(n, m, G, min);
		//leerGrafo2(n, G, min);
		//leerGrafo3(n, G); min = 1;

		resolver(G, min);
		cout << "---------------------------------------------------------------------------------" << '\n';
		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casoFallo.txt");
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
