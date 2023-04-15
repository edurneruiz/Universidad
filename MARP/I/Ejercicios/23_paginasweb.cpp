///EDURNE RUIZ DG33
/*
Vas a hacer un programa que te ayude a decidir la manera m´as r´apida de navegar. 
Para eso has recopilado todas las p´aginas web que visitas y has hecho una lista de los enlaces que
tiene cada una de ellas. Teniendo en cuenta la p´agina de inicio que tienes en el navegador quieres saber
cu´al es la forma m´as r´apida de llegar a una p´agina determinada utilizando ´unicamente esos enlaces.
Como est´as obsesionado por la velocidad, el programa tendr´a en cuenta que el tiempo de carga de
cada p´agina puede ser distinto y que una vez cargada, encontrar y pinchar en cada enlace depende de lo
lejos que est´e del principio de la p´agina y de lo oculto que est´e. Venga, ¡manos a la obra!

*/

/*
Algoritmo de Dijkstra
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

using namespace std;

class red {
	const int INF = INT_MAX;
	int origen, destino;
	vector<int> dist;
	
	DigrafoValorado<int> dg;
public:
	red(int orig, int dest) : dg(dest + 1), origen(orig), destino(dest), dist(dest + 1, INF), t_carga(dest + 1), pq(dest + 1) {
		inicializar();
		dijkstra();
	}

	bool hayCamino() {
		return dist[destino] != INF;
	}

	int distMinima() {
		return dist[destino];
	}

private:
	vector<int> t_carga; //tiempo de carga de cada página web
	IndexPQ<int> pq;

	void inicializar() {
		for (int i = 0; i < t_carga.size(); ++i) {
			cin >> t_carga[i];
		}
		int m, v1, v2, vv; cin >> m;
		while (m--) {
			cin >> v1 >> v2 >> vv;
			dg.ponArista({ v1 - 1, v2 - 1,vv });
		}
	}

	void dijkstra() {
		dist[origen] = t_carga[origen];
		pq.push(origen, t_carga[origen]);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : dg.ady(v))
				relajar(a);
		}
	}

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor() + t_carga[w]) {
			dist[w] = dist[v] + a.valor() + t_carga[w];
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
	int N;
	cin >> N;

	if (N == 0)
		return false;
	else {
		red r(0, N-1);

		if (r.hayCamino())
			cout << r.distMinima() << '\n';
		else
			cout << "IMPOSIBLE \n";

		return true;
	}

}
int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos23.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}