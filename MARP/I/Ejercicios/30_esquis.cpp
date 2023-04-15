///EDURNE RUIZ, 3ºDG
/*
El enemigo, armado hasta los dientes con palos y piedras, ha desembarcado en barcas hinchables en las costas de nuestra
patria invadiendo una serie de ciudades. Los servicios de inteligencia est´an informados del n´umero de efectivos enemigos que
se encuentran en cada una de las ciudades invadidas. Para contraatacar, nuestra Unidad de Combate Militar dispone de tantos equipos
listos para intervenir como ciudades invadidas. Cada uno de estos equipos consta de un n´umero de efectivos completamente equipados
y entrenados. Para garantizar el ´exito de la intervenci´on en una ciudad es necesario que contemos al menos con tantos efectivos
de defensa como el enemigo.

¿Puedes ayudarles a decidir la forma en la que repartir los equipos de defensa entre las ciudades
invadidas (un equipo por ciudad) de tal forma que se maximice el n´umero de ´exitos garantizados?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;


int minimaSuma(vector<int> & alturas, vector<int> & esquis) {
	int diferencias = 0, size = alturas.size();

	for (int i = 0; i < size; ++i) {
		diferencias += abs(alturas[i] - esquis[i]);
	}

	return diferencias;
}

void inicializar(vector<int> & v) {
	for (int i = 0; i < v.size(); ++i)
		cin >> v[i];
	sort(v.begin(), v.end()); //ordenamos de menor a mayor
}

bool resuelveCaso() {
	int N; cin >> N;

	if (N == 0)
		return false;
	else {
		vector<int> alturas(N); inicializar(alturas);
		vector<int> esquis(N); inicializar(esquis);

		cout << minimaSuma(alturas, esquis) << '\n';

		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos30.txt");
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