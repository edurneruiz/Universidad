//Edurne Ruiz

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "1_horas.h"
#include"2_peliculas.h"
using namespace std;

bool resuelveCaso() {
	int nPelis;
	cin >> nPelis;
	if (nPelis == 0) return false;
	vector<pelicula> pelis(nPelis);
	
	for (pelicula& p : pelis) cin >> p; //leer peliculas
	sort(pelis.begin(), pelis.end()); //ordena las peliculas por la hora de finalización
	for (pelicula& p : pelis) cout << p << "\n"; //imprimir solucion
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso());
	system("pause");
	return 0;
}