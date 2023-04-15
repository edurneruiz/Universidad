#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;

void rellenoTabla(int N, vector<int> const& cortes, Matriz<int> & e) {
	int NN = N + 2;
	for(int d = 2; d < NN; ++d) {
		for (int i = 0; i < NN - d; ++i) {
			int j = i + d, l = cortes[j] - cortes[i];
			e[i][j] = INT_MAX;
			for(int k = i + 1; k < j; ++k) {
				int aux = e[i][k] + e[k][j] + 2 * l;
				e[i][j] = fmin(e[i][j], aux);
			}
		}
	}
}

bool resuelveCaso() {
	int N, L; cin >> L >> N;

	if (L == 0 && N == 0)
		return false;
	
	vector<int> cortes(N + 2); cortes[0] = 0; cortes[N + 1] = L;
	for (int i = 1; i <= N; ++i)
		cin >> cortes[i];

	int k = 0;
	Matriz<int> esfuerzo(N + 2, N + 2, 0);
	rellenoTabla(N, cortes, esfuerzo);

	cout << esfuerzo[0][N+1] << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos9.txt");
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