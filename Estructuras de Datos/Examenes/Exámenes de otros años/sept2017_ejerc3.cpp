#include <iostream>
#include "lista_enlazada.h"
using namespace std;


bool resuelveCaso() {
	int aux;

	cin >> aux;
	if (aux == -1) return false;

	list<int> l;
	int a, b;

	while (aux != -1) {
		l.push(aux);
		cin >> aux;
	}
	cin >> a >> b;
	l.cuela(a, b);
	l.print();
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}