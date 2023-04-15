#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include "Matriz.h"
#include <vector>
using namespace std;


int maximo(int n, int i, int j, Matriz<int> const& s, Matriz<int> const& tablero) {
	if (j == 0)
		return fmax(s[i-1][j], s[i-1][j + 1]) + tablero[i][j];
	else if (j == n - 1)
		return fmax(s[i-1][j], s[i-1][j - 1]) + tablero[i][j];
	else
		return fmax(fmax(s[i-1][j], s[i-1][j - 1]), s[i-1][j + 1]) + tablero[i][j];
}

void rellenoTabla(int n, int & max, int & col, Matriz<int> const& tablero) {
	Matriz<int> s(n, n, 0);
	for (int i = 0; i < n; ++i) {
		int aux = -1;
		for (int j = 0; j < n; ++j) {
			s[i][j] = (i == 0) ? tablero[i][j] : maximo(n, i, j, s, tablero);
			if (s[i][j] > aux) {
				col = j + 1;
				aux = s[i][j];
			}
		}
		max = aux;
	}
}

bool resuelveCaso() {
	int n; cin >> n;

	if (!std::cin)
		return false;

	int max = -1, col = -1;
	Matriz<int> tablero(n, n, 0);
	for (int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> tablero[i][j];

	rellenoTabla(n, max, col, tablero);
	cout << max << " " << col << '\n';

	return true;
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