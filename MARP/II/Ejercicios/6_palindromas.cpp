#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include "Matriz.h"
using namespace std;

void rellenoTabla(int n, string const& x) {
	Matriz<string> M(n+1, n+1, "");

	for (int i = 1; i <= n; i++) {
		M[i][i] = x[i-1];
	}

	//Rellenar la tabla
	for (int d = 1; d <= n - 1; d++) {
		for (int i = 1; i <= n - d; i++) {
			int j = i + d;
			if (x[i-1] == x[j - 1]) {
				M[i][j] = x[i-1] + M[i + 1][j - 1] + x[j - 1];
			}
			else {
				M[i][j] = (M[i + 1][j].size() <= M[i][j - 1].size()) ?
					x[i-1] + M[i + 1][j] + x[i-1] :
					x[j - 1] + M[i][j - 1] + x[j - 1];
			}
		}
	}

	cout << M[1][n].size() - n << " " << M[1][n] << '\n';
}

bool resuelveCaso() {
	string x; cin >> x;

	if (!std::cin)
		return false;

	rellenoTabla(x.length(), x);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos6.txt");
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