#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "lista_enlazada.h"
using namespace std;

bool resuelveCaso() {
	int aux;
	list<int> q;

	cin >> aux;
	while (aux != 0) { //leer los datos
		q.push(aux);
		cin >> aux;
	}
	q.invierte();
	q.print();


	if (!std::cin) return false;
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

