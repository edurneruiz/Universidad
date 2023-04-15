#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;

void print(int N, Matriz<int> & e) {
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j)
			cout << e[i][j] << " ";
		cout << '\n';
	}
}

void rellenoTabla(int N, Matriz<int> & e) {
	for (int d = 1; d < N; ++d) {
		for (int i = 0; i < N - d; ++i) {
			int j = i + d, min = INT_MAX;
			e[i][j] = INT_MAX;
			for (int k = i + 1; k < j; ++k) {
				min = fmin(min, e[i][k] + e[k][j]);
			}
			e[i][j] = fmin(min, e[j][i]);
		}
	}
}

bool resuelveCaso() {
	int N; cin >> N;

	if (!std::cin)
		return false;

	Matriz<int> puertos(N, N, 0);
	for (int j = 0; j < N; ++j) {
		for (int i = j + 1; i < N; ++i)
			cin >> puertos[i][j];
	}
	rellenoTabla(N, puertos);
	print(N, puertos);


	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos14.txt");
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