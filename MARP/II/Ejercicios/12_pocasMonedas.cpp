#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include "Matriz.h"
using namespace std;

void rellenoTabla(int N, int C, vector<int> const& valores, vector<int> & cantidades, Matriz<int> & monedas) {
	for (int j = 1; j <= C; ++j)
		monedas[0][j] = INT_MAX;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= C; ++j) {
			int k = 0, aux = INT_MAX;
			while (k <= cantidades[i] &&  k*valores[i] <= j) {
				if (monedas[i - 1][j - k * valores[i]] != INT_MAX)
					aux = fmin(aux, monedas[i - 1][j - k * valores[i]] + k);
				++k;
			}
			monedas[i][j] = aux;
		}
	}
}

bool resuelveCaso() {
	int N; cin >> N;

	if (!std::cin)
		return false;

	vector<int> valores(N + 1), cantidades(N + 1); int C;
	for (int i = 1; i <= N; ++i)
		cin >> valores[i];
	for (int i = 1; i <= N; ++i)
		cin >> cantidades[i];
	cin >> C;

	Matriz<int> monedas(N+1, C + 1, 0);
	rellenoTabla(N, C, valores, cantidades, monedas);

	if (monedas[N][C] == INT_MAX)
		cout << "NO \n";
	else
		cout << "SI " << monedas[N][C] << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos12.txt");
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