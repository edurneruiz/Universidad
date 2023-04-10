/*
Dado un vector de n elementos (n ≥ 0), se desea obtener la suma de todos los
productos de valores situados en parejas de posiciones distintas (con una complejidad O(n)).
Ejemplo: para el array con contenido: [1, 3, 5, 7] se debe devolver 1∗3+1∗5+1∗7+3∗5+3∗7+5∗7.
*/
#include<iostream>
#include<vector>
using namespace std;

int suma_productos(int N, vector<int> const& v) {
	int suma = 0;

	for (int i = 0; i < N - 1; ++i) {
		for (int j = i + 1; j < N; ++j) {
			suma += v[i] * v[j];
		}
	}

	return suma;
}

void resuelveCaso() {
	int N;
	cin >> N;
	vector<int> v(N);
	for (int i = 0; i < N; ++i) {
		cin >> v[i];
	}

	cout << suma_productos(N, v) << "\n";
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos) {
		resuelveCaso();
		--numCasos;
	}
	return 0;
}

/*
4
1 3 5 7

6
6 2 5 9 1 2
*/