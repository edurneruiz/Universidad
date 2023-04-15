#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;

typedef struct {
	int grupos;
	int coste;
} tFestival;


int rellenoTabla(int P, int N, vector<tFestival> const& festivales) {
	vector<int> conciertos(P+1, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = P; j >= 0; --j) {
			if (festivales[i].coste <= j)
				conciertos[j] = fmax(conciertos[j], conciertos[j - festivales[i].coste] + festivales[i].grupos);
		}
	}

	return conciertos[P];
}

bool resuelveCaso() {
	int P, N; cin >> P >> N;

	if (!std::cin)
		return false;

	vector<tFestival> festivales(N);
	for (int i = 0; i < N; ++i)
		cin >> festivales[i].grupos >> festivales[i].coste;
	
	cout << rellenoTabla(P, N, festivales) << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos15.txt");
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