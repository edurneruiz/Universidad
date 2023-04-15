#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "Matriz.h"
using namespace std;

using grafo = Matriz<float>;


class solucionVoraz {	
private:
	const float inf = FLT_MAX;

	int n;
	vector<int> orden;
	float coste;
public:

	solucionVoraz(grafo const& G) : n(G.numfils()), orden(n, -1), coste(0), visit(0), c(0), mc(-1), si(true), 
								visitadas(vector<bool>(n,false)) {
		solucionar(G);
	}

	void print() {
		if (coste == inf)
			cout << "No existe un ciclo hamiltoniano en el grafo dado" << '\n';
		else {
			cout << "El orden de recorrido de las ciudades es: ";
			for (int i = 0; i < orden.size(); ++i)
				cout << orden[i] << " ";
			cout << ", con coste " << coste << '\n';
		}
	}

private:
	int visit, c, mc; bool si;
	vector<bool> visitadas;
	
	void solucionar(grafo const& G) {
		//consideramos la primera ciudad como la ciudad del vértice 0
		orden[0] = c; ++visit;
		while (visit <= n && si) {
			mc = ciudadMasCercana(G);

			if (mc == -1) //no existe ninguna carretera
				si = false;
			else {
				++visit; orden[visit] = mc; visitadas[mc] = true;
				coste += G[c][mc];
				c = mc;
			}
		}

		if (si && existeCarreteraFinal(G))
			coste += G[0][c];
		else
			coste = inf;
	}

	//dada una ciudad (vértice del grafo), devuelve la ciudad más cercana a ésta que aún no ha sido visitada
	int ciudadMasCercana(grafo const& G) {
		int u = -1; float min = inf;
		for (int i = 0; i < n && i != c; ++i) {
			if (G[c][i] < min && !visitadas[i]) {
				min = G[c][i];
				u = i;
			}
		}
		return u;
	}

	//devuelve true si existe carretera entre dos ciudades
	bool existeCarreteraFinal(grafo const& G) {
		if (G[0][c] == inf)
			return false;
		else
			return true;
	}

};
