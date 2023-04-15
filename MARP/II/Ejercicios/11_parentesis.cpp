#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include "Matriz.h"
using namespace std;

typedef struct {
	bool a, b, c;
} tProducto;


bool A(int i, int k, int j, Matriz<tProducto> const& m) {
	return (m[i][k].a && m[k + 1][j].c) || (m[i][k].b && m[k + 1][j].c) || (m[i][k].c && m[k + 1][j].a);
}
bool B(int i, int k, int j, Matriz<tProducto> const& m) {
	return (m[i][k].a && m[k + 1][j].a) || (m[i][k].a && m[k + 1][j].b) || (m[i][k].b && m[k + 1][j].b);
}
bool C(int i, int k, int j, Matriz<tProducto> const& m) {
	return (m[i][k].b && m[k + 1][j].a) || (m[i][k].c && m[k + 1][j].b) || (m[i][k].c && m[k + 1][j].c);
}

bool rellenoTabla(int n, string const& x) {
	Matriz<tProducto> M(n+1,n+1);

	for (int i = 0; i < n; ++i) {
		M[i+1][i+1] = { x[i] == 'a', x[i] == 'b', x[i] == 'c' };
	}

	for (int d = 1; d < n; ++d) {
		for (int i = 1; i <= n - d; ++i) {
			int j = i + d;
			for (int k = i; k < j; ++k) {
				if (A(i, k, j, M))
					M[i][j].a = true;
				if (B(i, k, j, M))
					M[i][j].b = true;
				if (C(i, k, j, M))
					M[i][j].c = true;
			}
		}
	}

	return M[1][n].a;
}

bool resuelveCaso() {
	string x; cin >> x;

	if (!std::cin)
		return false;

	if (rellenoTabla(x.length(), x))
		cout << "SI \n";
	else
		cout << "NO \n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos11.txt");
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