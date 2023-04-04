#include <iostream>
#include <stdexcept>  // std::domain_error
#include "stack_eda.h"
#include "deque_eda.h"
using namespace std;

template <class T>
class dcola : public deque<T> {
	using Nodo = typename deque<T>::Nodo;
public:

	void print() {
		Nodo * it = this->fantasma->sig;
		while (it != this->fantasma) {
			cout << it->elem << " ";
			it = it->sig;
		}
		cout << "\n";
	}

	void estremecer() {
		if (this->size() > 1) {
			stack<Nodo *> impares;
			Nodo * par = this->fantasma->sig;

			while (par->sig != this->fantasma) {
				impares.push(par->sig);
				par->sig = par->sig->sig;
				if (par->sig != this->fantasma) {
					par->sig->ant = par;
					par = par->sig;
				}
			}
			par->sig = impares.top();
			impares.top()->ant = par;
			while (impares.size() > 1) {
				Nodo * imp = impares.top();
				impares.pop();
				impares.top()->ant = imp; 
				imp->sig = impares.top(); 
			}
			impares.top()->sig = this->fantasma;
			this->fantasma->ant = impares.top();
			impares.pop();
		}
	}

	void entremezclar(dcola<T> & otra) {
		if (this->empty()) {
			this->fantasma->sig = otra.fantasma->sig;
			this->fantasma->sig->ant = this->fantasma;
			this->fantasma->ant = otra.fantasma->ant;
			this->fantasma->ant->sig = this->fantasma;
			this->nelems += otra.nelems;
		}
		else if (otra.empty()) {}
		else {
			bool cambiaUltimo = (this->nelems <= otra.nelems);

			Nodo * itThis = this->fantasma->sig;
			Nodo * itOtra = otra.fantasma->sig;
			Nodo * itThisSig = itThis->sig;
			Nodo * itOtraSig = itOtra->sig;

			while (itThis != this->fantasma && itOtra != otra.fantasma) {
				itThis->sig = itOtra;
				itOtra->ant = itThis;

				if (itThisSig != this->fantasma ) {
					itOtra->sig = itThisSig;
					itThisSig->ant = itOtra;
				}

				itThis = itThisSig;
				itOtra = itOtraSig;
				itThisSig = itThis->sig;
				itOtraSig = itOtra->sig;
			}

			this->nelems += otra.nelems;
			if (cambiaUltimo) {
				this->fantasma->ant = otra.fantasma->ant; 
				otra.fantasma->ant->sig = this->fantasma;
			}

		}
		otra.fantasma->sig = otra.fantasma; otra.fantasma->ant = otra.fantasma; otra.nelems = 0;

	}
};