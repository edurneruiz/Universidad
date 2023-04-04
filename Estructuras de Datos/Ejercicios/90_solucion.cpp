#include <iostream>
#include<vector>
#include "hashmap_eda.h"
using namespace std;

//funciones
void crearMapa(int n);
void print(unordered_map<int, int>& m, vector<int>& v);

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!std::cin) return false;
	crearMapa(n);
	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}

void crearMapa(int n) {
	unordered_map<int, int> m; //clave el numero, valor sus repeticiones
	vector<int> v;
	int aux;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		++m[aux];
		if (m[aux] == 1) { v.push_back(aux); }
	}
	print(m, v);
}

void print(unordered_map<int, int>& m, vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " " << m[v[i]] << "\n";
	}
	cout << "---\n";
}
