#include <iostream>
#include <fstream>
#include <string>
#include "treemap_eda.h"
using namespace std;
using clave_valor = std::pair<string, int>;

//funciones
map<string, int> leerMapa(int n);
void borrarCeros(map<string, int>& m);
void print(map<string, int>& m);

bool resuelveCaso() {
	int nEjers;

	cin >> nEjers;
	if (nEjers == 0) return false;
	
	map<string, int> m = leerMapa(nEjers);
	borrarCeros(m);
	print(m);
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

map<string, int> leerMapa(int n) {
	map<string, int> m;
	string nombre, ej;
	int punt;
	
	for (int i = 0; i < n; ++i) {
		getline(cin, nombre);
		getline(cin, nombre);
		cin >> ej;
		punt = (ej == "CORRECTO") ? 1 : -1;
		
		m.insert(nombre);
		m[nombre] += punt;
	}

	return m;
}

void borrarCeros(map<string, int>& m) {
	auto it = m.begin();

	while (it != m.end()) {
		if (it->valor == 0) {
			m.erase(it->clave);
			it = m.begin();
		}
		++it;
	}
}

void print(map<string, int>& m) {
	auto it = m.begin();

	while (it != m.end()) {
		cout << it->clave << ", " << it->valor << "\n";
		++it;
	}
	cout << "---\n";
}