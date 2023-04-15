#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include "Matriz.h"
using namespace std;

int rellenoTabla(int n, vector<int> const& cubos) {
	Matriz<int> vacas(n, n, 0);
	int a, b;

	for (int i = 0; i < n; i++) {
		vacas[i][i] = cubos[i];
		if (i != n - 1) 
			vacas[i][i + 1] = fmax(cubos[i], cubos[i + 1]);
	}

	for (int d = 2; d < n; d++) {
		for (int i = 0; i < n - d; i++) {
			int j = i + d;
			if (cubos[j] > cubos[i + 1])
				a = cubos[i] + vacas[i + 1][j - 1];
			if (cubos[i + 1] > cubos[j])
				a = cubos[i] + vacas[i + 2][j];
			if (cubos[i] > cubos[j - 1])
				b = cubos[j] + vacas[i + 1][j - 1];
			if (cubos[j - 1] > cubos[i])
				b = cubos[j] + vacas[i][j - 2];
			vacas[i][j] = fmax(a, b);
		}
	}

	return vacas[0][n - 1];
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (N == 0)
		return false;

	vector<int> cubos(N);
	for (int i = 0; i < N; i++)
		cin >> cubos[i];

	cout << rellenoTabla(N, cubos) << '\n';
	return true;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos13.txt");
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