#include <iostream>
#include <fstream>
#include <string>
#include "lista_enlazada.h"
#include "1_horas.h"
using namespace std;

//funciones


bool resuelveCaso() {
	int numElems;
	horas aux;
	list<horas> l;

	cin >> numElems;
	if (numElems == 0) return false;
	for (int i = 0; i < numElems; ++i) {
		cin >> aux;
		l.push(aux);
	}
	l.borrarIntercalados();
	l.print();

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}