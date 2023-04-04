#include <iostream> 
#include <stdexcept>  // std::domain_error
#include <cmath>
#include <vector>
#include "queue_eda.h"
#include "stack_eda.h"
using namespace std;

template <class T>
class eLista : public queue<T> {
	using Nodo = typename queue<T>::Nodo;
public:

	// imprimir por pantalla los elementos de la cola
	void print(std::ostream & o = std::cout) const {
		Nodo* ptr = this->prim;

		while (ptr != nullptr) {
			cout << ptr->elem << " ";
			ptr = ptr->sig;
		}
		cout << '\n';
	}

	//desplaza al elemento que está en la posición pos de la cola un nº dist de posiciones hacia la izquierda
	void desplaza(int pos, int dist) {
		if (pos < 0 || pos > this->size()) {			throw domain_error("Posicion invalida");		}		else {
			Nodo * it = this->prim;
			vector<Nodo *> anteriores;
			int i = pos;
			bool cambiarUltimo = (pos == this->size() && dist > 0);

			while (it != nullptr && i > 0) {
				--i;
				anteriores.push_back(it);
				it = it->sig;
			}

			if (pos > 1 && dist > 0) {
				Nodo * busc = anteriores[anteriores.size() - 1];
				Nodo * ant = anteriores[(anteriores.size() - 1) - 1];
				Nodo * sig = it;
				int nuevaPos = (pos - dist > 0) ? pos - dist - 1 : 0;
				if (nuevaPos == 0) {
					busc->sig = this->prim;
					this->prim = busc;
				}
				else {
					Nodo * nuevoAnterior = anteriores[nuevaPos - 1];
					Nodo * nuevoSiguiente = anteriores[nuevaPos];
					nuevoAnterior->sig = busc;
					busc->sig = nuevoSiguiente;
				}
				ant->sig = sig;
				this->ult = (cambiarUltimo) ? ant : this->ult;
			}
		}
	}
};