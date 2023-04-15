#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include "Matriz.h"
#include <vector>
using namespace std;

using lli = long long int;

typedef struct {
	lli potencia;
	lli precio;
} tBombilla;

typedef struct {
	bool posible;
	lli coste;
	lli potencia;
} tSolucion;


void print(tSolucion const& sol) {
	if (!sol.posible)
		cout << "Imposible \n";
	else
		cout << sol.coste << " " << sol.potencia << '\n';
}


int indice(int j, int k, vector<tSolucion> & sol) {
	if (sol[j].coste == sol[k].coste)
		return (sol[j].potencia < sol[k].potencia) ? j : k;
	else if (sol[j].coste < sol[k].coste)
		return j;
	else
		return k;
}

void determinar(int i, int j, int k, lli pmax, vector<tBombilla> const& bombillas, vector<tSolucion> & sol) {
	if (k < 0) {
		if (sol[j].coste > bombillas[i].precio || (sol[j].coste == bombillas[i].precio && sol[j].potencia > bombillas[i].potencia))
			sol[j] = { true, bombillas[i].precio, bombillas[i].potencia };
	}
	else {
		int l = indice(j, k, sol);
		sol[j] = { sol[j].posible || (sol[l].posible && sol[l].potencia + bombillas[i].potencia <= pmax),
						   sol[l].coste + bombillas[i].precio,
						   sol[l].potencia + bombillas[i].potencia };
	}
}

void rellenoTabla(int n, int pmax, lli pmin, vector<tBombilla> const& bombillas) {
	vector<tSolucion> sol(pmin+1, { false, LLONG_MAX, LLONG_MAX });
	sol[0] = { true, 0, 0 };

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= pmin; ++j) {
			int k = j - bombillas[i].potencia;
			determinar(i, j, k, pmax, bombillas, sol);
		}
	}

	print(sol[pmin]);
}

bool resuelveCaso() {
	int n; lli pmax, pmin; 
	cin >> n >> pmax >> pmin;

	if (!std::cin)
		return false;

	vector<tBombilla> bombillas(n+1, { 0,0 });
	for (int i = 1; i <= n; ++i)
		cin >> bombillas[i].potencia;
	for (int i = 1; i <= n; ++i)
		cin >> bombillas[i].precio;

	rellenoTabla(n, pmax, pmin, bombillas);

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