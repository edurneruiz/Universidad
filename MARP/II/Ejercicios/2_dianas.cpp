#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include "Matriz.h"
using namespace std;


void solucion(int n, int P, vector<int> const& sect, Matriz<int> & dianas) {
	cout << dianas[n][P] << ": ";

	int i = n, j = P;
	while (j > 0 && i >= 1) {
		if (sect[i] <= j && dianas[i][j] == dianas[i][j - sect[i]] + 1) {
			cout << sect[i] << " ";
			j -= sect[i];
		}
		else
			--i;
	}

	cout << "\n";
}

void rellenoTabla(int n, int P, vector<int> const& sect, Matriz<int> & dianas) {
	dianas[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		dianas[i][0] = 0;
		for (int j = 1; j <= P; ++j) {
			dianas[i][j] = (sect[i] > j) ? dianas[i - 1][j] : 
				fmin(dianas[i - 1][j], (dianas[i][j - sect[i]] == INT_MAX) ? INT_MAX : dianas[i][j - sect[i]] + 1);
		}
	}
}

bool resuelveCaso() {
	int punt, sect; cin >> punt >> sect;

	if (!std::cin)
		return false;

	vector<int> sectores(sect + 1);
	for (int i = 1; i <= sect; ++i)
		cin >> sectores[i];
	Matriz<int> dianas(sect + 1, punt + 1, INT_MAX);
	rellenoTabla(sect, punt, sectores, dianas);

	if (dianas[sect][punt] == INT_MAX)
		cout << "Imposible \n";
	else
		solucion(sect, punt, sectores, dianas);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while(resuelveCaso()) {}
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}