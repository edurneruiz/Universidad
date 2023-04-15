#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include "Matriz.h"
#include "PriorityQueue.h"
using namespace std;
//using precio = pair<int, int>;

class tNodo {
public:
	//vector<int> sol; //en la posición iesima, guardamos el camino limpiado por quitanieves i 
	vector<int> compra; // compra[i] = nº de productos q hemos comrpado en el supermercado i
	int k; //nivel
	int c; //puntuacion acumulada
	int c_estimada; //cota optimista de la puntuacion

	tNodo() : k(0), c(0), c_estimada(0) {}
	tNodo(int m, int est) : compra(m+1, 0), k(0), c(0), c_estimada(est) {}

	bool operator<(const tNodo & other) const {
		return c_estimada < other.c_estimada;
	}
};

void precalculoEstimaciones(int n, int m, vector<int> const& max, vector<int> const& min, vector<int> & opt, vector<int> & pes) {
	pes[n] = 0; opt[n] = 0;
	for (int i = n - 1; i >= 0; i--) {
		opt[i] = opt[i + 1] + min[i + 1];
		pes[i] = pes[i + 1] + max[i + 1];
	}
}

int compra_minima(int n, int m, vector<int> const& max, vector<int> const& min, vector<vector<int>> const& precios) {
	//para las estimaciones
	vector<int> opt(n + 1), pes(n + 1); precalculoEstimaciones(n, m, max, min, opt, pes);
	//creamos el nodo padre
	tNodo y(m, opt[0]);
	//cola de prioridad
	PriorityQueue<tNodo> pq; pq.push(y);
	//
	int sol = pes[0];

	while (!pq.empty() && pq.top().c_estimada < sol) {
		y = pq.top(); pq.pop();

		//generamos los hijos de y
		tNodo x; x.k = y.k + 1; x.compra = y.compra;
		for (int sm = 1; sm <= m; ++sm) {
			if (x.compra[sm] < 3) {
				++x.compra[sm];
				x.c = y.c + precios[x.k][sm];
				x.c_estimada = x.c + opt[x.k];

				if (x.c_estimada <= sol) {
					if (x.k == n)
						sol = x.c;
					else {
						pq.push(x);
						sol = fmin(sol, x.c + pes[x.k]);
					}
				}

				--x.compra[sm];
			}
		}
	}

	return sol;
}

void resuelveCaso() {
	int n, m;
	cin >> m >> n;

	vector<vector<int>> precios(n + 1, vector<int>(m + 1));
	vector<int> max(n + 1, INT_MIN), min(n + 1, INT_MAX);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> precios[j][i];
			max[j] = fmax(max[j], precios[j][i]);
			min[j] = fmin(min[j], precios[j][i]);
		}
	}

	cout << compra_minima(n, m, max, min, precios) << '\n';
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos21.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}