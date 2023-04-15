#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;

int maximo(int a, int b, int c) {
	return fmax(fmax(a, b), c);
}

int rellenoTabla(int N, vector<int> const& b) {
	Matriz<int> t(N, N, 0);

	for (int d = 1; d < N; ++d) {
		for (int i = 0; i < N - d; ++i) {
			int j = i + d;
			t[i][j] = maximo((i + 1 < j - 1) ? t[i + 1][j - 1] + (b[i] == b[j] && b[i] != 0) : 0,
							 (i < j - 2) ? t[i][j - 2] + (b[j - 1] == b[j] && b[j] != 0) : 0,
							 (i + 2 < j) ? t[i + 2][j] + (b[i] == b[i + 1] && b[i] != 0) : 0);
		}
	}

	return t[0][N-1];
}

bool resuelveCaso() {
	int N; cin >> N;

	if (!std::cin)
		return false;

	vector<int> bizcocho(N);
	for (int i = 0; i < N; ++i)
		cin >> bizcocho[i];

	cout << rellenoTabla(N, bizcocho) << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos16.txt");
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