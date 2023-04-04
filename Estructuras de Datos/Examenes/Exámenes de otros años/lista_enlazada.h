#include <iostream> 
#include <stdexcept>  // std::domain_error
#include <cmath>
#include <vector>
#include "queue_eda.h"
#include "stack_eda.h"
using namespace std;

template <class T>
class lista : public queue<T> {
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

	//invierte el orden de la lista
	void invierte() {
		stack<Nodo*> ptrs;
		Nodo* aux = this->prim;
		this->prim = this->ult;
		while (aux != this->ult) { //añado los punteros a una pila
			ptrs.push(aux);
			aux = aux->sig;
		}
		while (!ptrs.empty()) {
			aux->sig = ptrs.top(); //cambio el siguiente
			aux = ptrs.top();
			ptrs.pop();
		}
		this->ult = aux;
		if (this->ult != nullptr) this->ult->sig = nullptr;
	}

	//añadir otra lista en la posición indicada
	void addList(lista<T>& a, int pos) { ///en el caso peor, se realizan n-1 iteraciones del bucle while -> O(n)
		int i = 0;
		Nodo* aux = this->prim;

		if (pos == 0) {
			this->prim = a.prim;
			a.ult->sig = aux;
		}
		else if (pos == this->nelems) {
			this->ult->sig = a.prim;
			this->ult = a.ult;
		}
		else {
			while (i < pos - 1) { //buscamos el puntero de la lista dada cuyo siguiente tendra que apuntar al primero de la lista a añadir
				aux = aux->sig;
				++i;
			}
			a.ult->sig = aux->sig; //guardamos el siguiente al auxiliar para más adelante
			aux->sig = a.prim;
		}

		this->nelems += a.nelems;
		a.prim = nullptr; a.ult = nullptr; a.nelems = 0; //eliminar a
	}

	//eliminar hasta que solo quede uno siguiendo un paso
	int ultimo(int paso) {
		Nodo* it = this->ult;

		this->ult->sig = this->prim; //para generar circularidad
		while (1 < this->nelems) {
			for (int i = 0; i < paso; i++) it = it->sig;
			it->sig = it->sig->sig;
			this->nelems--;
		}
		this->prim = it; //cambiar el primero
		this->ult = it; //cambiar el ultimo
		this->prim->sig = nullptr; //para destruir la circularidad

		return this->prim->elem;
	}

	//Intercambiar los elementos de una lista de dos en dos
	void intercambiar() {
		Nodo* ptr = this->prim;
		Nodo* sig;
		Nodo* aux;

		if (this->nelems != 0 && this->nelems != 1) {
			this->prim = this->prim->sig;
			while (ptr != nullptr) {
				aux = (ptr->sig == nullptr) ? ptr->sig : ptr->sig->sig;
				sig = ptr->sig;
				ptr->sig = (sig == nullptr) ? nullptr : (sig->sig == nullptr) ? nullptr : (sig->sig->sig == nullptr) ? sig->sig : sig->sig->sig;
				if (sig != nullptr) sig->sig = ptr;
				ptr = aux;
			}
		}

		if (this->nelems % 2 == 0) this->ult = this->ult->sig;
	}

	//borrar uno de cada dos
	void borrarIntercalados() {
		Nodo * ptr = this->prim;
		Nodo * sig = (this->prim->sig == nullptr) ? nullptr : this->prim->sig->sig;
		Nodo * dlt;

		while (ptr != nullptr) {
			dlt = ptr->sig;
			ptr->sig = sig;
			if (sig == nullptr) this->ult = ptr; //cambiar ultimo
			ptr = sig;
			sig = (sig == nullptr) ? nullptr : (sig->sig == nullptr) ? nullptr : sig->sig->sig;
			delete dlt; //borrar el nodo 
		}

		double n = this->nelems / 2.0;
		this->nelems = ceil(n);
	}

	//eliminar elementos decrecientes
	void eliminarDecrecientes() {
		Nodo * ptr = this->prim;
		Nodo * dlt;

		while (ptr->sig != nullptr) {
			if (ptr->sig->elem < ptr->elem) {
				dlt = ptr->sig;
				if (ptr->sig == this->ult) this->ult = ptr;
				ptr->sig = ptr->sig->sig;
				this->nelems--;
				delete dlt;
			}
			else ptr = ptr->sig;
		}
	}

	void annadirOrdenada(lista<T>& otra) {
		Nodo* aux = this->prim;
		Nodo* ot = otra.prim;
		Nodo* saux;
		Nodo* sot;

		if (this->nelems == 0) {
			this->prim = otra.prim;
			this->ult = otra.ult;
			this->nelems = otra.nelems;
			otra.prim = nullptr; otra.ult = nullptr; otra.nelems = 0; //eliminar otra
		}
		else if (otra.nelems == 0) {}
		else if (this->ult->elem < otra.prim->elem)
			addList(otra, this->nelems);
		else if (otra.ult->elem < this->prim->elem)
			addList(otra, 0);
		else {
			bool primeroMenor = otra.prim->elem < this->prim->elem;
			bool ultimoMayor = otra.ult->elem > this->ult->elem;

			while (aux != nullptr && ot != nullptr) {
				sot = ot->sig;
				if (buscarPosicion(ot, aux)) { ///devuelve true -> aux ha cambiado
					saux = (aux == nullptr) ? nullptr : aux->sig;
					aux->sig = ot;

					if (sot == nullptr && saux == nullptr) ot->sig = nullptr;
					else if (sot == nullptr) ot->sig = saux;
					else if (saux == nullptr) ot->sig = sot;
					else ot->sig = (sot->elem < saux->elem) ? sot : saux;

					ot = sot;
					aux = saux;
				}
				else { ///devuelve false -> ot ha cambiado
					sot = ot->sig;
					ot->sig = aux;
					ot = sot;
				}
			}
			this->nelems += otra.nelems;
			this->prim = (primeroMenor) ? otra.prim : this->prim;
			this->ult = (ultimoMayor) ? otra.ult : this->ult;
			otra.prim = nullptr; otra.ult = nullptr; otra.nelems = 0; //eliminar otra
		}
	}

	//que mueve al elemento b de su posición a la posición inmediatamente detrás del elemento a.
	void cuela(T const& a, T const& b) {
		Nodo * it = this->prim;
		Nodo * itA = nullptr;
		Nodo * aSig = nullptr;
		Nodo * bAnt = nullptr;
		Nodo * itB = nullptr;
		Nodo * bSig = nullptr;

		while (it != nullptr && itB == nullptr) {
			if (it->elem == a && itA == nullptr) { //si es el primer elemento a que encontramos
				itA = it;
				aSig = it->sig;
			}
			if (it->sig != nullptr && it->sig->elem == b && itA != nullptr) { //si el elemento siguiente es b, cuando ya hemos encontrado un a
				bAnt = it;
				itB = it->sig;
				bSig = it->sig->sig;
			}
			it = it->sig;
		}

		if (itA != nullptr && itB != nullptr) { //si hemos encontrado tanto a como b
			itA->sig = itB;
			itB->sig = aSig;
			bAnt->sig = bSig;
		}
	}

	//lleva el elemento que está en la posición pos de la cola a la primera posición de la misma
	void llevarAlPrincipio(int pos) {		if (pos < 0 || pos > this->size()) {			throw domain_error("Posicion invalida");		}		else {			Nodo * it = this->prim;			Nodo * ant = nullptr;			Nodo * busc = nullptr;			Nodo * sig = nullptr;			bool ultimo = (pos == this->size());			while (it != nullptr && pos > 1) {				--pos;				if (pos == 1) {					ant = it;					busc = (it->sig == nullptr) ? nullptr : it->sig;					sig = (it->sig == nullptr) ? nullptr : it->sig->sig;				}				it = it->sig;			}			if (busc != nullptr) {				busc->sig = this->prim;				ant->sig = sig;				this->prim = busc;				this->ult = (ultimo) ? ant : this->ult;			}		}	}	
	//desplaza al elemento que está en la posición pos de la cola un nº dist de posiciones hacia la izquierda
	void desplaza(int pos, int dist) {
		if (pos < 0 || pos > this->size()) {			throw domain_error("Posicion invalida");		}		else {
			Nodo * it = this->prim;
			Nodo * sig = nullptr;
			vector<Nodo *> anteriores;

			bool cambiarUltimo = (pos == this->size() && dist > 0);

			while (it->sig != nullptr && pos > 0) {
				--pos;
				anteriores.push_back(it);
				it = it->sig;
			}

			if (it != nullptr) {
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


private:
	bool buscarPosicion(Nodo*& ot, Nodo*& ptr) {
		if (ot->elem < ptr->elem) {
			while (ot->sig != nullptr && ot->sig->elem < ptr->elem) {
				ot = ot->sig;
			}
			return false;
		}
		else {
			while (ptr->sig != nullptr && ot->elem > ptr->sig->elem) {
				ptr = ptr->sig;
			}
			return true;
		}
	}

};

