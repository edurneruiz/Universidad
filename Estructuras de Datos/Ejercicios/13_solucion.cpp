//EDURNE RUIZ, DG28

#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
using namespace std;

//funciones
void reordenar(queue<int>& e);
void print(queue<int>& e);

bool resuelveCaso() {
	int nElems, aux;
	cin >> nElems;

	if (nElems == 0) return false;
	queue<int> e;
	for (int i = 0; i < nElems; ++i) { //leer los elementos 
		cin >> aux;
		e.push(aux);
	}
	reordenar(e);
	print(e);

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

void reordenar(queue<int>& e) {
	stack<int> negativos;
	queue<int> positivos;
	int size = e.size();

	for (int i = 0; i < size; ++i) {
		if (e.front() < 0) negativos.push(e.front());
		else positivos.push(e.front());
		e.pop();
	}
	while (!negativos.empty()) { //añadir los negativos a la cola
		e.push(negativos.top());
		negativos.pop();
	}
	while (!positivos.empty()) { //añadir los positivos
		e.push(positivos.front());
		positivos.pop();
	}
}

void print(queue<int>& e) {
	while (!e.empty()) {
		cout << e.front() << " ";
		e.pop();
	}
	cout << '\n';
}