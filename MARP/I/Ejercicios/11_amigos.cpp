///EDURNE RUIZ DG33
/*
En esta ciudad viven N personas, y sabemos que algunas de ellas son amigas entre s´ı. De acuerdo con el refr´an que dice 
“Los amigos de mis amigos son mis amigos”, sabemos que si A y B son amigos y B y C son amigos, entonces tambi´en son amigos A y C.
Tu misi´on consiste en contar las personas en el grupo de amigos m´as grande.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Grafo.h"
using namespace std;

class AmigosCiudad {
	Grafo amistades;
public:
	
	AmigosCiudad(int n) : amistades(n), visitados(n, false), max(0) {}

	int V() const { return amistades.V(); }

	int A() const { return amistades.A(); }

	void ponArista(int v, int w) {
		amistades.ponArista(v, w);
	}

	int grupoMasGrande() {
		return grupoMayor();
	}

private:
	vector<bool> visitados;
	int max;

	int grupoMayor() {
		for (int v = 0; v < amistades.V(); ++v) {
			if (!visitados[v]) {
				int t = dfs(v);
				max = fmax(max, t);
			}
		}

		return max;
	}

	int dfs(int vertice) {
		visitados[vertice] = true;
		int tam = 1;
		for (int v : amistades.ady(vertice)) {
			if (!visitados[v])
				tam += dfs(v);
		}
		return tam;
	}

	
};

bool resuelveCaso() {
	int n, m;
	cin >> n >> m;

	if (!std::cin)
		return false;
	else {
		AmigosCiudad ac(n);
		
		while (m--) {
			int v1, v2;
			cin >> v1 >> v2;
			ac.ponArista(v1-1, v2-1);
		}

		cout << ac.grupoMasGrande() << '\n';
		return true;
	}
}


int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos--) {
		resuelveCaso();
	}
	return 0;
}

/*
entrada:
2

3 2
1 2
2 3

10 10
1 2
3 1
3 4
5 4
3 5
4 6
5 2
7 10
9 10
8 9

salida:

3

6
*/