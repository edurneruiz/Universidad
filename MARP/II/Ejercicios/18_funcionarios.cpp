#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
#include "Matriz.h"
#include "PriorityQueue.h"
using namespace std;

class tNodo {
public:
	vector<int> sol;
	vector<bool> disponibles;
	int k; //nivel
	int t; //tiempo acumulado
	int t_estimado; //cota optimista del tiempo

	tNodo() : k(0), t(0), t_estimado(0) {}
	tNodo(int n) : sol(vector<int>(n + 1, 0)), disponibles(vector<bool>(n + 1, true)), k(0), t(0), t_estimado(0) {}

	//tNodo(tNodo const& other) : k(other.k + 1), sol(other.sol), disponibles(other.disponibles), t(other.t), t_estimado(other.t_estimado) {}

	bool operator<(const tNodo & other) const {
		return t_estimado < other.t_estimado;
	}
};

int tiempoEstimado(int n, vector<int> const& minimos, tNodo const& x) {
	int s = 0;
	for (int i = 0; i <= n; ++i) {
		if (x.disponibles[i])
			s += minimos[i];
	}
	return s;
}

vector<int> minimos(int n, Matriz<int> const& func) {
	vector<int> m(n + 1, INT_MAX);
	
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			m[i] = fmin(m[i], func[i][j]);
		}
	}
	return m;
}

int tiempoMinimo(int n, Matriz<int> const& funcionarios) {
	int tmejor = INT_MAX;
	vector<int> func_minimos = minimos(n, funcionarios);
	PriorityQueue<tNodo> pq;

	//inicializamos y
	tNodo y(n); y.disponibles[0] = false; y.t_estimado = tiempoEstimado(n, func_minimos, y);
	pq.push(y);

	while (!pq.empty() && pq.top().t_estimado < tmejor) {
		y = pq.top(); pq.pop();

		//generamos los hijos de y
		tNodo x; x.k = y.k + 1; x.disponibles = y.disponibles; x.sol = y.sol;
		for (int func = 1; func <= n; ++func) {
			if (x.disponibles[func]) {
				//marcamos
				x.sol[x.k] = func;
				x.disponibles[func] = false;
				x.t = y.t + funcionarios[func][x.k];

				if (x.k == n) {
					if (x.t < tmejor)
						tmejor = x.t;
				}
				else {
					x.t_estimado = x.t + tiempoEstimado(n, func_minimos, x);
					if (x.t_estimado < tmejor)
						pq.push(x);
				}
				
				x.disponibles[func] = true; //desmarcamos
			}
		}
	}

	return tmejor;
}

bool resuelveCaso() {
	int N; cin >> N;

	if (!N)
		return false;

	Matriz<int> funcionarios(N + 1, N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			cin >> funcionarios[i][j];
	}

	cout << tiempoMinimo(N, funcionarios) << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos18.txt");
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