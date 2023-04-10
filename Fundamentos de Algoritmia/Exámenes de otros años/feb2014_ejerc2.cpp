/*
precondición: { 0 <= n && lng = 2^n && positivo(V) }
caucasico(V[0...lng) de ent, ini, fin : ent) dev c : bool
postcondición: { b = diferencia(V) && caucasico(primeraMitad) && caucasico(segundaMitad) }

*/


#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//funciones
int diferencia(int ini, int fin, vector<int> & v);

bool caucasico(int ini, int fin, vector<int>& v) {
	if (ini >= fin) return true;
	else {
		int mitad = (ini + fin) / 2, dif;
		dif = diferencia(ini, fin, v);
		return (dif <= 2) && caucasico(ini, mitad - 1, v) && caucasico(mitad, fin - 1, v);
	}
}

bool resuelveCaso() {
	int n, lng;

	cin >> n;
	if (n == 0) return false;
	lng = pow(2, n);
	vector<int> vec(lng);

	for (int i = 0; i < vec.size(); i++) { cin >> vec[i]; }
	if (caucasico(0, lng, vec)) { cout << "CAUCASICO" << endl; }
	else { cout << "NO CAUCASICO" << endl; }
	
	return true;
}

int main() {
	while (resuelveCaso());

	return 0;
}

int diferencia(int ini, int fin, vector<int>& v) {
	int pares1 = 0, pares2 = 0, m = (ini + fin)/2;

	for (int i = ini; i < fin - m; i++) {
		pares1 = (v[i] % 2 == 0) ? pares1 + 1 : pares1;
		pares2 = (v[m + i] % 2 == 0) ? pares2 + 1 : pares2;
	}

	return abs(pares1 - pares2);
}