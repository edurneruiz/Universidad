#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "lista_enlazada.h"
using namespace std;

//funciones
void print(list<int>& e);

bool resuelveCaso() {
	int nElems, m, pos, aux;
	list<int> principal, secundaria;

	cin >> nElems;
	if (!std::cin) return false;

	while (nElems != 0) { //leer los datos de la lsita principal
		cin >> aux;
		principal.push(aux);
		--nElems;
	}
	cin >> m >> pos;
	while (m != 0) { //leer los datos de la lista a añadir
		cin >> aux;
		secundaria.push(aux);
		--m;
	}
	principal.addList(secundaria, pos);
	print(principal);
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

void print(list<int>& e)  {
	while (!e.empty()) {
		cout << e.front() << " ";
		e.pop();
	}
	cout << '\n';
}