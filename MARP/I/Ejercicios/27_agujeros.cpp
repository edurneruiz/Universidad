///EDURNE RUIZ, 3ºDG
/*
Susana ha decidido arreglar la manguera tapando los agujeros. Para ello tiene que comprar unos parches rectangulares 
que se colocan a lo largo sobre la manguera y cuyo ancho la envuelve completamente. Un parche puede tapar varios
agujeros (si un parche tiene una longitud L puede llegar a tapar agujeros que est´en separados entre s´ı hasta esa 
distancia) y pueden solaparse.
¿Puedes calcular cu´antos parches como m´ınimo necesita Susana para cubrir todos los agujeros de la manguera?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>
#include <queue>
using namespace std;

int parches(int lg, queue<int> & agujeros) {
	if (agujeros.empty())
		return 0;
	else {
		int p = 0, a = agujeros.front(); 

		agujeros.pop(); ++p;
		while (!agujeros.empty()) {
			int b = agujeros.front(); agujeros.pop();

			if (b - a > lg) {
				++p; a = b;
			}
		}
		return p;
	}
}

bool resuelveCaso() {
	int N,L, aux; cin >> N >> L;

	if (!std::cin)
		return false;
	else {
		queue<int> agujeros;
		while (N--) {
			cin >> aux;
			agujeros.push(aux);
		}
		
		cout << parches(L, agujeros) << '\n';

		return true;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos27.txt");
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