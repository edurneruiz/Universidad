#include<iostream>
#include <vector>
#include <cmath>
#include "bintree_eda.h"
using namespace std;


vector<int> operator+(vector<int> v1, vector<int> v2) {
	if (v1.empty()) return v2;
	else if (v2.empty()) return v1;
	else {
		int min = fmin(v1.size(), v2.size());
		int max = fmax(v1.size(), v2.size());
		vector<int> suma(max); //el vector suma tendrá el tamaño del vector más grande

		for (int i = 0; i < min; ++i) { //sumamos coordenadas
			suma[i] = v1[i] + v2[i];
		}
		for (int j = min; j < max; ++j) { //como en uno de los vectores ya no se llega a esa coordenada, igualamos al otro
			suma[j] = (v1.size() < v2.size()) ? v2[j] : v1[j];
		}

		return suma;
	}
}

//en la posición i-ésima del vector se guarda el nº de hojas del árbol cuya profundidad sea mayor que i
vector<int> profundidad_hojas(int estamosEnProfundidad, bintree<int> & a) {
	if (a.empty())
		return vector<int>(estamosEnProfundidad, 0); //devolvemos un vector de ese tamaño 
	else {
		bintree<int> iz = a.left(), dcho = a.right();

		if (iz.empty() && dcho.empty()) { //estamos en una hoja
			//creamos un vector del mismo tamaño a la profundidad y añadimos a cada coordenada esta hoja
			return vector<int> (estamosEnProfundidad, 1);
		}
		else {
			vector<int> viz = profundidad_hojas(estamosEnProfundidad + 1, iz);
			vector<int> vd = profundidad_hojas(estamosEnProfundidad + 1, dcho);

			return viz + vd; 
		}
	}
}

//devuelve el nº de hojas cuya profundidad es mayor que p
int hojasProfundas(int p, bintree<int> & a) {
	vector<int> ph = profundidad_hojas(1, a);
	return (ph.size() <= p) ? 0 : ph[p];
}

bool resuelveCaso() {
	int prof;
	cin >> prof;
	if (!std::cin) return false;

	bintree<int> arbol = leerArbol(-1);
	cout << "El num de hojas cuya profundidad es mayor que " << prof << " es: " << hojasProfundas(prof, arbol) << "\n---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
0 
1 2 -1 -1 3 4 -1 -1 5 -1 -1
1
1 2 -1 -1 3 4 -1 -1 5 -1 -1
2
1 2 -1 -1 3 4 -1 -1 5 -1 -1
3
1 2 -1 -1 3 4 -1 -1 5 -1 -1

0
10 2 -1 0 -1 -1 4 4 -1 -1 -1
1
10 2 -1 0 -1 -1 4 4 -1 -1 -1
2
10 2 -1 0 -1 -1 4 4 -1 -1 -1
3
10 2 -1 0 -1 -1 4 4 -1 -1 -1
4
10 2 -1 0 -1 -1 4 4 -1 -1 -1

0
1 1 1 -1 -1 -1 -1
1
1 1 1 -1 -1 -1 -1
2
1 1 1 -1 -1 -1 -1
5
1 1 1 -1 -1 -1 -1

0
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
1
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
2
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
3
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
4
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
5
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1
6
3 4 7 -1 -1 5 6 -1 -1 8 9 -1 -1 9 -1 -1 2 -1 -1


*/