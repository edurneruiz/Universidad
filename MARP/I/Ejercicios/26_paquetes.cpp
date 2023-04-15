///EDURNE RUIZ, 3ºDG
/*
La oficina de la empresa de transportes que atiende a la comarca est´a situada en una de estas casas. Cada
d´ıa, un ´unico repartidor debe entregar los paquetes recibidos, y para ello cuenta con una moto cuyo compartimento 
de carga es tan peque˜no que solamente puede llevar un paquete cada vez. Con estas restricciones, la
rutina del sufrido repartidor consiste en tomar uno de los paquetes, llevarlo hasta la casa del destinatario,
y volver a la oficina a por el siguiente paquete. Debido a las condiciones de las v´ıas, hay ocasiones en las
que interesa, o es incluso inevitable, que el camino de vuelta siga una ruta distinta al de ida.
Conociendo el esfuerzo que supone para el repartidor viajar por las distintas v´ıas en cada sentido
transitable, y las casas donde debe entregar paquetes un d´ıa concreto, ¿puedes ayudarle a decidir la
mejor forma (la de menor esfuerzo total) de repartir los paquetes? El repartidor tiene total libertad para
elegir en qu´e orden reparte los paquetes y qu´e rutas sigue, tanto para ir como para volver.
*/

/*
Para encontrar las mejores rutas desde la oficina hasta las casas -> algoritmo de Dijkstra en el grafo dado
Para encontrar las mejores rutas desde las casas a la oficina -> algoritmo de Dijkstra en el grafo inverso del dado
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include <queue>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;


class caminosMinimos {
	const int INF = INT_MAX;
	int origen;

public:

	caminosMinimos(int o, DigrafoValorado<int> const& g) : origen(o - 1), dist_ida(g.V(), INF), 
					dist_vuelta(g.V(), INF), pq(g.V()) {
		DigrafoValorado<int> inv = g.inverso();
		dijkstra(g, dist_ida);
		dijkstra(inv, dist_vuelta);
	}

	bool existeCamino(int dest) {
		return dist_ida[dest] != INF && dist_vuelta[dest] != INF;
	}

	int rutaMinima(int dest) {
		return dist_ida[dest] + dist_vuelta[dest];
	}

private:
	vector<int> dist_ida;
	vector<int> dist_vuelta;
	IndexPQ<int> pq;

	void dijkstra(DigrafoValorado<int> const& g, vector<int> & dist) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a, dist);
		}
	}

	//relajar aristas
	void relajar(AristaDirigida<int> a, vector<int> & dist) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}

};

void inicializarGrafo(DigrafoValorado<int> & g) {
	int a, v1, v2, vv; cin >> a;

	while (a--) {
		cin >> v1 >> v2 >> vv;
		g.ponArista({ v1 - 1, v2 - 1, vv });
	}
}

bool resuelveCaso() {
	int v;
	cin >> v;

	if (!std::cin)
		return false;
	else {
		DigrafoValorado<int> g(v); inicializarGrafo(g);

		int o, p, esfuerzo = 0, aux; cin >> o >> p;
		bool posible = true;
		caminosMinimos cm(o, g);

		while (p--) { //aunque se haya encontrado un camino imposible, se sigue leyendo la entrada para consumirla
			cin >> aux;
			if (cm.existeCamino(aux - 1))
				esfuerzo += cm.rutaMinima(aux - 1);
			else
				posible = false;
		}

		if (posible)
			cout << esfuerzo << '\n';
		else
			cout << "Imposible \n";

		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos26.txt");
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