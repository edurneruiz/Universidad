#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>
#include <stdexcept>  // invalid_argument
#include <cmath>
#include <string>
#include <vector>
#include "Matriz.h"
using namespace std;

void print(vector<char> const& sol) {
	for (int i = sol.size() - 1; i >= 0; i--)
		cout << sol[i];
	cout << '\n';
}

void reconstruir(string const& x, string const& y, Matriz<int> const& m, vector<char> & sol) {
	int i = m.numfils() - 1, j = m.numcols() - 1;
	
	while (j > 0 && i > 0) {
		if (x[i - 1] == y[j - 1]) {
			sol.push_back(x[i - 1]);
			i--; j--;
		}
		else {
			if (m[i - 1][j] > m[i][j - 1])
				i--;
			else
				j--;
		}
	}
}

void rellenoTabla(string const& x, string const& y, vector<char> & sol) {
	int n = x.length(), m = y.length();
	Matriz<int> M(n + 1, m + 1);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (x[i - 1] == y[j - 1]) {
				M[i][j] = 1 + M[i - 1][j - 1];
			}
			else {
				M[i][j] = fmax(M[i - 1][j], M[i][j - 1]);
			}
		}
	}
	
	reconstruir(x, y, M, sol);
}

bool resuelveCaso() {
	string x, y; cin >> x >> y;

	if (!std::cin)
		return false;

	vector<char> solucion;
	rellenoTabla(x, y, solucion);
	print(solucion);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos7.txt");
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
