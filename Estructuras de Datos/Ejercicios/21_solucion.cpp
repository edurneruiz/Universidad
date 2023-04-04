#include <iostream>
#include <string>
#include <fstream>

#include "bintree_eda.h"
using namespace std;

//funciones
template<class T>
T menor(bintree<T> a);

bool resuelveCaso() {
	char tipo;
	string fin = "#";

	cin >> tipo;
	if (!std::cin) return false;
	if (tipo == 'N') {
		bintree<int> arbol = leerArbol(-1);
		cout << menor(arbol) << '\n';
	}
	else {
		bintree<string> arbol = leerArbol(fin);
		cout << menor(arbol) << '\n';
	}

	return true;
}

int main() {
	
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

template<class T>
T menor(bintree<T> a) {
	auto it = a.begin();
	T menor = *it;

	while (it != a.end()) {
		menor = (menor < *it) ? menor : *it;
		++it;
	}

	return menor;
}