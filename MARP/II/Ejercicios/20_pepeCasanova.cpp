#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include "Matriz.h"
#include "PriorityQueue.h"
using namespace std;
using cambioCara = pair<bool, int>;

class tNodo {
public:
	//vector<int> sol; //en la posición iesima, guardamos el camino limpiado por quitanieves i 
	vector<bool> usadas; //en la posición iésima, guardamos si hemos añadido la cancion i
	int k; //nivel
	int p; //puntuacion acumulada
	int d_a; //duracion acumulada en la cara A
	int d_b;
	int p_estimada; //cota optimista de la puntuacion

	tNodo() : k(0), p(0), p_estimada(0) {}
	tNodo(int n) : usadas(n+1, false), k(0), p(0), p_estimada(0), d_a(0), d_b(0) {}

	bool operator<(const tNodo & other) const {
		return p_estimada > other.p_estimada;
	}
};


int estimar(int n, int d, tNodo const& x, vector<int> const& dd, vector<int> const& pp, vector<double> const& rend) {
	int cota = 0, hueco = 2 * d - x.d_a - x.d_b;
	int k = x.k + 1;

	while (k < n && dd[k] <= hueco) {
		hueco -= dd[k];
		cota += pp[k];
		++k;
	}

	cota = (k < n) ? cota + pp[k] / dd[k] : cota;
	return cota;
}

int puntuacion_maxima(int n, int d, vector<int> const& dd, vector<int> const& pp, vector<double> const& rr) {
	int pmejor = INT_MIN;
	PriorityQueue<tNodo> pq;

	tNodo y(n); y.p_estimada = estimar(n, d, y, dd, pp, rr);
	pq.push(y);

	while (!pq.empty() && pq.top().p_estimada > pmejor) {
		y = pq.top(); pq.pop();

		//generamos hijos de y
		tNodo x; x.k = y.k + 1; x.usadas = y.usadas; x.d_a = y.d_a; x.d_b = y.d_b; x.p = y.p;
		for (int c = 0; c <= n; ++c) {
			if (!x.usadas[c]) {
				if (dd[c] <= d - x.d_a) { //añadimos la canción a la cara A
					x.p += pp[c]; x.usadas[c] = (c != 0); x.d_a += dd[c];
					x.p_estimada = x.p + estimar(n, d, x, dd, pp, rr);

					if (pmejor <= x.p_estimada) {
						if (x.k == n)
							pmejor = x.p;
						else {
							pq.push(x);
							pmejor = fmax(pmejor, x.p);
						}
					}

					/*if (x.k == n - 1)
						pmejor = fmax(x.p, pmejor);
					else {
						x.p_estimada = x.p + estimar(n, d, x, dd, pp, rr);
						if (x.p_estimada > pmejor)
							pq.push(x);
					}*/

					x.p -= pp[c]; x.usadas[c] = false; x.d_a -= dd[c];
				}

				if (dd[c] <= d - x.d_b) { //añadimos la canción a la cara A
					x.p += pp[c]; x.usadas[c] = (c != 0); x.d_b += dd[c];
					x.p_estimada = x.p + estimar(n, d, x, dd, pp, rr);

					if (pmejor <= x.p_estimada) {
						if (x.k == n)
							pmejor = x.p;
						else {
							pq.push(x);
							pmejor = fmax(pmejor, x.p);
						}
					}

					/*if (x.k == n - 1)
						pmejor = fmax(x.p, pmejor);
					else {
						x.p_estimada = x.p + estimar(n,d,x,dd,pp,rr);
						if (x.p_estimada > pmejor)
							pq.push(x);
					}*/

					x.p -= pp[c]; x.usadas[c] = false; x.d_b -= dd[c];
				}

				x.p_estimada = x.p + estimar(n, d, x, dd, pp, rr);
				if (pmejor <= x.p_estimada) {
					if (x.k == n)
						pmejor = x.p;
					else {
						pq.push(x);
						pmejor = fmax(pmejor, x.p);
					}
				}

				/*if (x.k == n - 1) //no añadimos la canción
					pmejor = fmax(x.p, pmejor);
				else {
					if (estimar(n, d, x, dd, pp, rr) > pmejor)
						pq.push(x);
				}*/
			}
		}
	}

	return pmejor;
}

bool resuelveCaso() {
	int n; cin >> n;

	if (n == 0)
		return false;
	else {
		int d, maxp = INT_MIN; cin >> d;
		vector<int> duracion(n+1, 0), puntuacion(n+1, 0); vector<double> rendimiento(n+1, 0);
		for (int i = 1; i <= n; ++i) {
			cin >> duracion[i] >> puntuacion[i];
			rendimiento[i] = (puntuacion[i] + 0.0) / duracion[i];
			maxp = fmax(puntuacion[i], maxp);
		}

		cout << puntuacion_maxima(n, d, duracion, puntuacion, rendimiento) << '\n';

		return true;
	}

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos20.txt");
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