#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "lista_enlazada.h"
using namespace std;


bool resuelveCaso() {
	int alumnos, paso;
	list<int> fila;
	cin >> alumnos >> paso;

	if (alumnos == 0 && paso == 0) return false;

	for (int i = 0; i < alumnos; ++i) fila.push(i+1);
	cout << fila.ultimo(paso) << '\n';

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}