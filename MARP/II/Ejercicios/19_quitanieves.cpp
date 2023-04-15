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
	//vector<int> sol; //en la posición iesima, guardamos el camino limpiado por quitanieves i 
	vector<bool> usadas; //en la posición iésima, guardamos si la quitanieves i se usa
	int k; //nivel
	int c; //calidad acumulada
	int estimado; //cota optimista de la calidad

	tNodo() : k(0), c(0), estimado(0) {}
	tNodo(int n, int m) : usadas(n+1, false), k(0), c(0), estimado(0) {}
	//tNodo(tNodo const& padre) : k(padre.k + 1), usadas(padre.usadas), c(padre.c) {}

	bool operator<(const tNodo & other) const {
		return estimado < other.estimado;
	}
};


int calidadEstimada(int n, int m, Matriz<int> const& calidades, tNodo const& x) {
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			s = fmax(s, calidades[i][j]);
			
	}
	return (m - x.k)*s;
}


int calidad_Maxima(int n, int m, vector<int> const& quitanieves, vector<int> const& calles, Matriz<int> const& calidades) {
	int cmejor = INT_MIN;
	PriorityQueue<tNodo> pq;

	tNodo y(n, m), x; y.estimado = calidadEstimada(n, m, calidades, y);
	pq.push(y);

	while (!pq.empty()) {
		y = pq.top(); pq.pop();

		//generamos los hijos de y
		x.k = y.k + 1; x.usadas = y.usadas; x.c = y.c;
		for (int qn = 0; qn <= n; ++qn) {
			if (qn == 0 || (!x.usadas[qn] && quitanieves[qn] <= calles[x.k])) {
				x.usadas[qn] = (qn != 0); 
				x.c += calidades[qn][x.k];
				x.estimado = x.c + calidadEstimada(n, m, calidades, x);
				
				if (cmejor <= x.estimado) {
					if (x.k == m)
						cmejor = x.c;
					else {
						pq.push(x);
						cmejor = fmax(cmejor, x.c);
					}
				}

				x.usadas[qn] = false; x.c -= calidades[qn][x.k]; //desmarcar
			}
		}
	}

	return cmejor;
}

void resuelveCaso() {
	int n, m; cin >> n >> m;

	vector<int> carros(n+1), calles(m+1);
	for (int i = 1; i <= n; ++i)
		cin >> carros[i];
	for (int i = 1; i <= m; ++i)
		cin >> calles[i];

	Matriz<int> calidades(n+1, m+1, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			cin >> calidades[i][j];
	}

	cout << calidad_Maxima(n, m, carros, calles, calidades) << '\n';
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos19.txt");
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