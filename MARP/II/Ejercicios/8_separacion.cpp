#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;

void inicializar(int r, Matriz<int> & c) {
	int cont = 0; string x, y;
	unordered_map<string, int> personas;

	for (int i = 0; i < r; ++i) {
		cin >> x >> y;
		if (!personas.count(x)) {
			personas.insert({ x, cont });
			++cont;
		}
		if (!personas.count(y)) {
			personas.insert({ y, cont });
			++cont;
		}
		c[personas[x]][personas[y]] = 1;
		c[personas[y]][personas[x]] = 1;
	}
}

void rellenoTabla(int N, int r, Matriz<int> & c) {
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			c[i][i] = 0;
			for (int j = 0; j < N; ++j) {
				if (c[i][k] != INT_MAX && c[k][j] != INT_MAX)
					c[i][j] = fmin(c[i][k] + c[k][j], c[i][j]);
			}
		}
	}
}

void print(int N, Matriz<int> const& c) {
	int max = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			max = fmax(c[i][j], max);
		}
	}

	if (max == INT_MAX)
		cout << "DESCONECTADA \n";
	else
		cout << max << '\n';
}

bool resuelveCaso() {
	int N, r; cin >> N >> r;

	if (!std::cin)
		return false;

	Matriz<int> c(N, N, INT_MAX);
	inicializar(r, c);
	rellenoTabla(N, r, c);
	print(N, c);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos8.txt");
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