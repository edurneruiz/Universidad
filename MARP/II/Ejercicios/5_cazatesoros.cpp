#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include "Matriz.h"
#include <vector>
using namespace std;

typedef struct {
	int profundidad;
	int t;
	int oro;
} tCofre;

typedef struct {
	int tesoro;
	int n;
} tSolucion;

void print(int N, int T, Matriz<tSolucion> const& sol, vector<tCofre> & elegidos) {
	cout << sol[N][T].tesoro << '\n' << sol[N][T].n << '\n';
	int size = elegidos.size();
	for (int i = size - 1; i >= 0; --i)
		cout << elegidos[i].profundidad << " " << elegidos[i].oro << '\n';
	cout << "--- \n";
}

void reconstruirSolucion(int N, int T, vector<tCofre> const& cofres, Matriz<tSolucion> const& sol, vector<tCofre> & elegidos) {
	int i = N, j = T;
	while (i >= 1 && j > 0) {
		if (j - cofres[i].t >= 0 && sol[i][j].tesoro == sol[i - 1][j - cofres[i].t].tesoro + cofres[i].oro) {
			elegidos.push_back(cofres[i]);
			j -= cofres[i].t;
		}
		--i;
	}
}

void rellenoTabla(int N, int T, vector<tCofre> const& cofres, Matriz<tSolucion> & sol) {
	for (int i = 1; i <= N; ++i) {
		for (int j = T; j >= 0; --j) {
			if (j >= cofres[i].t && sol[i - 1][j].tesoro < sol[i - 1][j - cofres[i].t].tesoro + cofres[i].oro)
				sol[i][j] = { sol[i - 1][j - cofres[i].t].tesoro + cofres[i].oro, sol[i - 1][j - cofres[i].t].n + 1 };
			else
				sol[i][j] = sol[i - 1][j];
		}
	}
}

bool resuelveCaso() {
	int T, N; cin >> T >> N;

	if (!std::cin)
		return false;

	vector<tCofre> cofres( N + 1, { 0,0 }), elegidos;
	for (int i = 1; i <= N; ++i) {
		cin >> cofres[i].profundidad >> cofres[i].oro;
		cofres[i].t = 3 * cofres[i].profundidad;
	}

	Matriz<tSolucion> sol(N+1, T + 1, { 0,0 });
	rellenoTabla(N, T, cofres, sol);
	reconstruirSolucion(N, T, cofres, sol, elegidos);
	print(N, T, sol, elegidos);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos5.txt");
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