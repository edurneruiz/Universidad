#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "Matriz.h"
using namespace std;

using grafo = Matriz<float>;

class tNodo {
public:
	//vector<int> sol;
	vector<bool> usado;
	int k; //nivel
	int ultimo; //ultimo vértice visitado 
	float coste, coste_estimado;

	tNodo() : k(0), coste(0), coste_estimado(0) {}

	tNodo(int n) : usado(n, false), k(0), coste(0), ultimo(-1) {}

	bool operator<(const tNodo & other) const {
		return coste_estimado < other.coste_estimado;
	}

};

class solucionRamificacionPoda {
private:
	const float inf = FLT_MAX;

	int n;
	vector<int> orden;
	float coste, minArista;
public:

	solucionRamificacionPoda(grafo const& G, float min) : n(G.numfils()), orden(n, -1), coste(inf), minArista(min) {
		solucionar(G);
	}

	float getCoste() {
		return coste;
	}

	void print(bool darOrden) {
		if (darOrden) {
			if (coste == inf)
				cout << "No existe un ciclo hamiltoniano en el grafo dado" << '\n';
			else {
				cout << "El orden de recorrido de las ciudades es: ";
				for (int i = 0; i < orden.size(); ++i)
					cout << orden[i] << " ";
				cout << ", con coste " << coste << '\n';
			}
		}
		else
			cout << "El grafo tiene coste " << coste << '\n';
	}

private:
	using info = pair<bool, float>;


	void solucionar(grafo const& G) {
		PriorityQueue<tNodo> pq;
		tNodo x(n), y(n);

		//inicializamos y 
		y.usado[0] = true; y.coste_estimado = n * minArista; y.ultimo = 0;

		pq.push(y);
		while (!pq.empty() && pq.top().coste_estimado < coste) {
			y = pq.top(); pq.pop();

			//generamos los hijos de y
			x.k = y.k + 1; x.usado = y.usado; x.coste = y.coste;
			int anterior = y.ultimo;

			for (int vertice = 1; vertice < n; ++vertice) {
				info i = infoArista(anterior, vertice, G);
				if (!x.usado[vertice] && i.first) {
					x.ultimo = vertice; x.usado[vertice] = true; x.coste += i.second;
					if (x.k == n - 1) {
						info ii = infoArista(x.ultimo, 0, G);
						float cc = x.coste + ii.second;
						if (ii.first && (cc < this->coste)) {
							//orden = x.sol; 
							coste = cc;
						}
					}
					else {
						x.coste_estimado = x.coste + (n - x.k + 1)*minArista;
						if (x.coste_estimado < this->coste)
							pq.push(x);
					}
					x.usado[vertice] = false; x.coste -= i.second;
				}
			}
		}
	}

	//dados dos vértices, ant y vert, devuelve si son adyacentes, y en caso afirmativo, también el coste de la arista
	///O(C), donde C es el número de vértices adyacentes a el vértice 'ant'
	info infoArista(int ant, int vert, grafo const& G) {
		bool existe = false; int i = 0; float coste = inf;

		while (!existe && i < n) {
			if (ant == i && G[vert][i] != inf) {
				existe = true;
				coste = G[vert][i];
			}
			else
				++i;
		}
		return { existe, coste };
	}


};
#pragma once
