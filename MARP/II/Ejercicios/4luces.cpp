#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <unordered_map>
#include "Matriz.h"
#include <vector>
using namespace std;
using instalacion = pair<int, int>; //first -> coste inst, second -> potencia inst

instalacion minimo(instalacion const& x1, instalacion const& x2) {
	if (x1.first < x2.first)
		return x1;
	else if (x1.first > x2.first)
		return x2;
	else
		return (x1.second < x2.second) ? x1 : x2;
}

instalacion operator +(instalacion const& x1, instalacion const& x2) {
	if (x1.first == INT_MAX || x2.first == INT_MAX)
		return { INT_MAX, INT_MAX };
	else
		return { x1.first + x2.first, x1.second + x2.second };
}

instalacion solucion(int pmin, int pmax, vector<instalacion> const& l) {
	instalacion sol = { INT_MAX,INT_MAX };
	for (int i = pmin; i <= pmax; ++i)
		sol = minimo(sol, l[i]);
	return sol;
}

void inicializar(int pmin, int pmax, vector<instalacion> & l, vector<int> const& P, vector<int> const& C) {
	l[0] = { 0,0 };
	for (int i = 1; i <= pmax; i++)
		l[i] = { INT_MAX, INT_MAX };

	int i = 1;
	while (i*P[0] <= pmax) {
		l[i * P[0]] = { i * C[0], i * P[0] };
		++i;
	}
}

instalacion rellenoTabla(int n, int pmax, int pmin, vector<int> const& P, vector<int> const& C) {
	vector<instalacion> luces(pmax+1, { INT_MAX, INT_MAX });
	inicializar(pmin, pmax, luces, P, C);

	for (int i = 0; i < n; ++i) {
		for (int j = pmax; j >= 1; --j) {
			int k = 0;
			while (k*P[i] <=j) {
				instalacion aux = { k * C[i], k * P[i] };
				luces[j] = minimo(luces[j], luces[j - k*P[i]] + aux);
				++k;
			}
		}
	}

	return solucion(pmin, pmax, luces);
}


bool resuelveCaso() {
	int n, pmax, pmin; cin >> n >> pmax >> pmin;

	if (!std::cin)
		return false;

	vector<int> potencias(n), precios(n);
	for (int i = 0; i < n; ++i) {
		cin >> potencias[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> precios[i];
	}

	instalacion i = rellenoTabla(n, pmax, pmin, potencias, precios);

	if (i.first == INT_MAX)
		cout << "IMPOSIBLE \n"; 
	else
		cout << i.first << " " << i.second << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos4.txt");
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