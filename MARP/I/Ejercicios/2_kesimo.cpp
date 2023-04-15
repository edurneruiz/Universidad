///EDURNE RUIZ DG33
/*Extender el TAD  de TreeSetAVL con una nueva operacion que devuelva el k-ésimo menor del conjunto.*/

#include <iostream>
#include "TreeSet_AVL.h"
#include <fstream>
using namespace std;

bool resuelveCaso() {
	int nelems;
	cin >> nelems;

	if (nelems == 0)
		return false;
	else {
		Set<int> cjto; int aux;
		for (int i = 0; i < nelems; ++i) { //insertar en el conjunto
			cin >> aux;
			cjto.insert(aux);
		}
		cin >> nelems; //numero de posiciones k a consultar
		for (int i = 0; i < nelems; ++i) {
			cin >> aux; //k
			try {
				cout << cjto.kesimo(aux) << "\n";
			}
			catch (domain_error e) {
				cout << "?? \n";
			}
		}
		cout << "--- \n";

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada 

4
15 20 25 30
2
1 3
5
16 8 4 4 32
3
2 4 5
0

salida

15
25
---
8
32
??
---
*/