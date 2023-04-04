#include <iostream>
#include <fstream>
#include <string>
#include "lista_enlazada.h"
using namespace std;

//funciones


bool resuelveCaso() {
	int numElems, aux;
	list<int> l;

	cin >> numElems;
	if (numElems == 0) return false;
	for (int i = 0; i < numElems; ++i) {
		cin >> aux;
		l.push(aux);
	}
	l.intercambiar();
	l.print();

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}