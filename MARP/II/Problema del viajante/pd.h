#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "Matriz.h"
using namespace std;
using grafo = Matriz<float>;
using conjunto = pair<int, int>;


class indices {
public:
	PriorityQueue<conjunto> ind;

	indices(int m) {
		for (int i = 0; i < m; ++i) {
			if (i % 2 == 1) {
				int tam = 0, c = i;
				while (c) {
					if (c % 2)
						++tam;
					c = c / 2;
				}
				ind.push({ tam,i });
			}
		}
	}

	bool empty() {
		return ind.empty();
	}
	void pop() {
		ind.pop();
	}
	int top() {
		return ind.top().second;
	}

};

class solucionProgramacionDinamica {
private:
	const float inf = FLT_MAX;
	int n, m, todasVisitadas;
	float coste;

public:

	solucionProgramacionDinamica(grafo const& G) : n(G.numfils()), m(pow(2,n)), coste(inf), todasVisitadas(pow(2, n)-1),
												   cicloHM(m, n, inf), ind(m) {
		rellenarTabla2(G);
		solucion(G);
	}

	float getCoste() {
		return coste;
	}

	void print() {
		cout << "El coste es de " << coste << '\n';
	}

private:
	Matriz<float> cicloHM;
	indices ind;

	void rellenarTabla2(grafo const& G) {
		inicializar(G);
		
		while (!ind.empty()) {
			int cjto = ind.top(); ind.pop();

			for (int ciudad = 0; ciudad < n; ++ciudad) {
				if (visitada(cjto, ciudad)) {
					int cjtoAnterior = cjto & ~(1 << ciudad);
					for (int ciudadAnterior = 0; ciudadAnterior < n; ++ciudadAnterior) {
						if (ciudadAnterior != ciudad && visitada(cjto,ciudadAnterior)) {
							cicloHM[cjto][ciudad] = fmin(cicloHM[cjto][ciudad],
								cicloHM[cjtoAnterior][ciudadAnterior] + G[ciudad][ciudadAnterior]);
						}
					}
				}
			}
		}
	}

	void inicializar(grafo const& G) {
		cicloHM[1][0] = 0; //si únicamente puedes pasar por 1 -> no hay que moverse -> coste 0
		for (int i = 1; i < n; ++i) {
			cicloHM[1][i] = G[1][i];
		}
	}

	void solucion(grafo const& G) {
		for (int ciu = 1; ciu < n; ++ciu)
			coste = fmin(coste, cicloHM[todasVisitadas][ciu] + G[ciu][0]);
	}

	//nos dice si, dado un conjunto de ciudades y una ciudad especifica, esta pertenece
	bool visitada(int cjto, int ciudad) {
		return (!(cjto & (1 << ciudad)) == 0);
	}

};