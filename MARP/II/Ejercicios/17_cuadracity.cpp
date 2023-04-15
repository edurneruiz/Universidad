#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;


int rellenoTabla(int n, int m, Matriz<char> const& ciudad) {
	vector<int> formas(m, 0); 

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (ciudad[i][j] == 'P')
				formas[j] = 0;
			else {
				if (i == 0) //no hay calles más al norte, entonces solo podemos llegar desde la izquierda (i, j-1)
					formas[j] = (j != 0) ? formas[j - 1] : 1;
				else if (j == 0) //no hay más calles al oeste, entonces solo podemosllegar desde el norte (i-1, j)
					continue;
				else //podemos llegar tanto del norte como del oeste
					formas[j] += formas[j - 1];
			}
		}
	}

	return formas[m - 1];
}

bool resuelveCaso() {
	int N, M; cin >> N >> M;

	if (!std::cin)
		return false;

	Matriz<char> ciudad(N, M, ' ');
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			cin >> ciudad[i][j];
	}

	cout << rellenoTabla(N, M, ciudad) << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos17.txt");
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