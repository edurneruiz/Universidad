// EDURNE RUIZ HUGUET, DG28

/*
Para entremezclar dos listas doblemente enlazadas, podemos distinguir tres casos:
-> la lista secundaria es vacía: no se realiza ningún cambio 
-> la lista en la que vamos a añadir los elementos es vacía: modificamos el fantasma de la lista principal para que su siguiente y su 
anterior coincidan con los del fantasma de la lista secundaria.
-> ninguna de las dos listas es vacía: se realiza un bucle en el cual se van modificando los punteros de los elementos.

En el caso mejor (una de las listas es vacía o tiene un elemento), la operación será constante O(1).

En el caso de que una de las listas tenga más elementos que otra, el bucle realizará n iteraciones.
n = nº de elementos de la lista más pequeña.

En el caso peor (ambas listas tienen el mismo nº de elementos), este bucle debe realizar N iteraciones. Como en el cuerpo del bucle se
realizan operaciones de coste constante, concluimos que tiene un coste de O(N).
N = nº de elementos de las listas.


*/


#include <iostream>                              
#include <fstream>               
#include <algorithm>
using namespace std;

#include "deque_eda.h"

class EntremezclarListas : public deque<int> {
public:
	// imprime la lista
	void print(std::ostream& o = std::cout) const {
		Nodo * it = this->fantasma->sig;
		while (it != this->fantasma) {
			cout << it->elem << " ";
			it = it->sig;
		}
		cout << "\n";
	}

	// modifica this para entremezclar sus elementos con los de other
	void entremezclar(EntremezclarListas & other) {
		if (this->empty()) { // si this es vacía, debemos modificar solamente lo que influye en su fantasma
			this->fantasma->sig = other.fantasma->sig;
			this->fantasma->sig->ant = this->fantasma;
			this->fantasma->ant = other.fantasma->ant;
			this->fantasma->ant->sig = this->fantasma;
		}
		else if (other.empty()) {} //si other es vacía, no se realiza ninguna modificación
		else {
			Nodo * itThis = this->fantasma->sig; //apunta al primer elemento de this 
			Nodo * itOther = other.fantasma->sig; //apunta al primer elemento de other
			Nodo * itThisSig;
			Nodo * itOtherSig;
			Nodo * itOtherAnt = other.fantasma; 

			bool cambiaUltimo = (this->size() <= other.size()); //si other es mayor o igual en tamaño que this, 
																//el anterior del fantasma debe ser modificado

			while (itThis != this->fantasma || itOther != other.fantasma) {
				if (itThis == this->fantasma) //hemos llegado al final de this, pero no al final de other
					itOther = other.fantasma;
				else if (itOther == other.fantasma) { //hemos llegado al final de other, pero no al final de this
					itThis->ant = itOtherAnt;
					itThis = this->fantasma;
				}
				else {
					itThisSig = itThis->sig; //el elemento de this siguiente
					itOtherSig = itOther->sig; //el elemento de other siguiente

					itThis->sig = itOther; //cambiamos el siguiente del elemento actual de this
					itOther->ant = itThis; //cambiamos el anterior del elemento actual de other
					itThis->ant = (itThis->ant == this->fantasma) ? this->fantasma : itOtherAnt; //cambiamos el anterior del elemento actual de this
					itOther->sig = (itThisSig != this->fantasma) ? itThisSig : itOther->sig; //cambiamos el siguiente del elemento actual de other

					itOtherAnt = itOther; //guardamos el elemento actual de other, pues lo necesitaremos para relacionarlo con el siguiente
										  // a modificar de this	
					itThis = itThisSig; // avanzamos en la lista this
					itOther = itOtherSig; //avanzamos en la lista other
				}
			}
			if (cambiaUltimo) {
				this->fantasma->ant = other.fantasma->ant;
				other.fantasma->ant->sig = this->fantasma;
			}
		}
		this->nelems += other.nelems; //modificamos el nº de elementos para que coincida con el real
		other.fantasma->sig = other.fantasma; other.fantasma->ant = other.fantasma; other.nelems = 0; //eliminamos deque other
	}

};


/////////////////////////////////////////////////////////
// de aquí hacia abajo NO se puede modificar nada

inline std::ostream& operator<<(std::ostream & o, EntremezclarListas const& a) {
	a.print(o);
	return o;
}

EntremezclarListas leerLista() {
	EntremezclarListas lista;
	int n, val;
	cin >> n; // tamaño
	while (n--) {
		cin >> val;
		lista.push_back(val);
	}
	return lista;
}

void resuelveCaso() {
	auto lista1 = leerLista();
	auto lista2 = leerLista();

	lista1.entremezclar(lista2);

	cout << lista1 << '\n';
}


int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int casos;
	cin >> casos;
	for (int i = 0; i < casos; ++i) {
		resuelveCaso();
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//  system("PAUSE");
#endif
	return 0;
}
