#include <iostream>
#include "lista_enlazada.h"
using namespace std;

//funciones 
list<int> leerLista();

bool resuelveCaso() {
	list<int> l1 = leerLista();
	list<int> l2 = leerLista();
	l1.annadirOrdenada(l2);
	l1.print();
	return true;
}

list<int> leerLista() {
	list<int> l;
	int aux;
	cin >> aux;
	while (aux != 0) {
		l.push(aux);
		cin >> aux;
	}
	return l;
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