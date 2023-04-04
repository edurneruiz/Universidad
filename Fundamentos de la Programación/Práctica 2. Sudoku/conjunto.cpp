#include <iostream>
#include "conjunto.h"
#include "checkML.h"

using namespace std;

void cjto_vacio(tConjunto & conjunto) {
	conjunto.numElem = 0;
	for (int i = 0; i < NUM_ELEMENTOS; i++) {
		conjunto.elementos[i] = false;
	}
}

void cjto_lleno(tConjunto & conjunto) {
	conjunto.numElem = NUM_ELEMENTOS;
	for (int i = 0; i < NUM_ELEMENTOS; i++) {
		conjunto.elementos[i] = true;
	}
}

int numElems(const tConjunto & conjunto) {
	int numElems = 0;
	for (int i = 0; i < NUM_ELEMENTOS; i++) {
		if (conjunto.elementos[i] == true) {
			numElems++;
		}
	}
	return numElems;
}

bool pertenece(const tConjunto & conjunto, int valor) {
	int i = 0;
	bool enc = false;
	while ((i < NUM_ELEMENTOS) && !enc) {
		if ((conjunto.elementos[i] == true) && (i+1 == valor)) { enc = true; }
		i++;
	}
	return enc;
}

void addElemento(tConjunto & conjunto, int valor) {
	if (!pertenece(conjunto, valor)) {
		conjunto.elementos[valor-1] = true;
		conjunto.numElem++;
	}
}

void delElemento(tConjunto & conjunto, int valor) {
	if (pertenece(conjunto, valor)) {
		conjunto.elementos[valor - 1] = false;
		conjunto.numElem--;
	}
}

bool esUnitario(const tConjunto & conjunto, int & elemento) {
	int i = 0, cont = 0;
	while (i < NUM_ELEMENTOS) {
		if (conjunto.elementos[i]) { 
			cont++;
			elemento = i + 1;
		}
		i++;
	}
	return (cont == 1);
}

void mostrar(const tConjunto & conjunto) {
	for (int i = 0; i < NUM_ELEMENTOS; i++) {
		if (pertenece(conjunto, i + 1)) { cout << i + 1 << ", "; }
	}
}



