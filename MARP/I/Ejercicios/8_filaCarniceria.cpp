///EDURNE RUIZ DG33
/*
En la carnicer´ıa de mi pueblo tienen un sistema muy particular para decidir el orden en el que los clientes que est´an
esperando son atendidos. Cuando un cliente llega a la tienda recoge un n´umero que es distinto a todos los dem´as repartidos
ese d´ıa y espera pacientemente a ser atendido.
Cuando el carnicero, que estudia matem´aticas los fines de semana, puede atender a otro cliente, grita “¿El mediano, por
favor?”, esperando que aquel cliente cuyo n´umero sea la mediana en ese momento d´e un paso al frente y empiece a comprar.
M´as formalmente, la mediana de N elementos es el elemento que ocupar´ıa la posici´on b(N + 1)/2c si estos se ordenaran
crecientemente.
Como el proceso en ocasiones produce un gran alboroto entre la clientela, quiere un programa que le muestre cada vez eln´umero del siguiente cliente que debe ser atendido. ¿Puedes ayudarle?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>
using namespace std;

template <class T, class Comparator = std::less<T>>
class Fila {
protected:

	struct TreeNode;
	using Link = TreeNode * ;
	struct TreeNode {
		T elem;
		Link iz, dr;
		int altura;

		int tam_i; //nº de nodos en hijo izquierdo + 1 -> posición del nodo si su subárbol se ordenara

		TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
			int alt = 1, int i_tam = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(i_tam) {}
	};

	// puntero a la raíz de la estructura jerárquica de nodos
	Link raiz;

	// número de elementos (cardinal del conjunto)
	int nelems;

	// objeto función que compara elementos (orden total estricto)
	Comparator menor;
public:

	// constructor (conjunto vacío)
	Fila(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

	// constructor por copia
	Fila(Fila const& other) {
		copia(other);
	}

	// operador de asignación
	Fila & operator=(Fila const& that) {
		if (this != &that) {
			libera(raiz);
			copia(that);
		}
		return *this;
	}

	~Fila() {
		libera(raiz);
	};

	bool insert(T const& e) {
		return inserta(e, raiz);
	}

	bool empty() const {
		return raiz == nullptr;
	}

	int size() const {
		return nelems;
	}

	bool contains(T const& e) const {
		return pertenece(e, raiz);
	}

	bool erase(T const& e) {
		return borra(e, raiz);
	}

	T const& kesimo(int k) const {
		return k_esimo(k, raiz);
	}


protected:

	T const& k_esimo(int k, Link a) const {
		if (k < 1 || k > this->nelems)
			throw std::domain_error("k no valido");
		if (a->tam_i == k)
			return a->elem;
		else if (a->tam_i > k)
			return k_esimo(k, a->iz);
		else
			return k_esimo(k - a->tam_i, a->dr);
	}


	void copia(Fila const& other) {
		raiz = copia(other.raiz);
		nelems = other.nelems;
		menor = other.menor;
	}

	static Link copia(Link a) {
		if (a == nullptr) return nullptr;
		else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura, a->tam_i);
	}

	static void libera(Link a) {
		if (a != nullptr) {
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	bool pertenece(T const& e, Link a) const {
		if (a == nullptr) {
			return false;
		}
		else if (menor(e, a->elem)) {
			return pertenece(e, a->iz);
		}
		else if (menor(a->elem, e)) {
			return pertenece(e, a->dr);
		}
		else { // e == a->elem
			return true;
		}
	}

	bool inserta(T const& e, Link & a) {
		bool crece;
		if (a == nullptr) { // se inserta el nuevo elemento e
			a = new TreeNode(e);
			++nelems;
			crece = true;
		}
		else if (menor(e, a->elem)) {

			++a->tam_i;

			crece = inserta(e, a->iz);
			if (crece) reequilibraDer(a);
			else --a->tam_i; //si no crece es porque el elemento ya estaba en el árbol, deshacemos lo de antes
		}
		else if (menor(a->elem, e)) {
			crece = inserta(e, a->dr);
			if (crece) reequilibraIzq(a);
		}
		else // el elemento e ya está en el árbol
			crece = false;
		return crece;
	}

	int altura(Link a) {
		if (a == nullptr) return 0;
		else return a->altura;
	}

	void rotaDer(Link & r2) {

		Link r1 = r2->iz;

		r2->tam_i = r2->tam_i - r1->tam_i;

		r2->iz = r1->dr;
		r1->dr = r2;
		r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
		r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
		r2 = r1;
	}

	void rotaIzq(Link & r1) {
		Link r2 = r1->dr;

		r2->tam_i = r1->tam_i + r2->tam_i;

		r1->dr = r2->iz;
		r2->iz = r1;
		r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
		r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
		r1 = r2;
	}

	void rotaIzqDer(Link & r3) {
		rotaIzq(r3->iz);
		rotaDer(r3);
	}

	void rotaDerIzq(Link & r1) {
		rotaDer(r1->dr);
		rotaIzq(r1);
	}

	void reequilibraIzq(Link & a) {
		if (altura(a->dr) - altura(a->iz) > 1) {
			if (altura(a->dr->iz) > altura(a->dr->dr))
				rotaDerIzq(a);
			else rotaIzq(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

	void reequilibraDer(Link & a) {
		if (altura(a->iz) - altura(a->dr) > 1) {
			if (altura(a->iz->dr) > altura(a->iz->iz))
				rotaIzqDer(a);
			else rotaDer(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

	// devuelve y borra el mínimo del árbol con raíz en a
	T borraMin(Link & a) {
		if (a->iz == nullptr) {
			T min = a->elem;
			a = a->dr;
			--nelems;
			return min;
		}
		else {
			T min = borraMin(a->iz);
			reequilibraIzq(a);
			return min;
		}
	}

	bool borra(T const& e, Link & a) {
		bool decrece = false;
		if (a != nullptr) {
			if (menor(e, a->elem)) {
				decrece = borra(e, a->iz);
				if (decrece) reequilibraIzq(a);
			}
			else if (menor(a->elem, e)) {
				decrece = borra(e, a->dr);
				if (decrece) reequilibraDer(a);
			}
			else { // e == a->elem
				if (a->iz == nullptr || a->dr == nullptr) {
					Link aux = a;
					a = (a->iz == nullptr) ? a->dr : a->iz;
					--nelems;
					delete aux;
				}
				else { // tiene dos hijos
					T min = borraMin(a->dr);
					a->elem = min;
					reequilibraDer(a);
				}
				decrece = true;
			}
		}
		return decrece;
	}
};


void sucesion_eventos(Fila<int> & f) {
	int c;
	cin >> c;

	if (c == 0) {
		if (f.empty())
			cout << "ECSA ";
		else {
			int m = (f.size() + 1) / 2;
			int mediana = f.kesimo(m);

			cout << mediana << " ";
			f.erase(mediana);
		}
	}
	else {
		f.insert(c);
	}

}

bool resuelveCaso() {
	int eventos;
	cin >> eventos;

	if (!std::cin)
		return false;
	else {
		Fila<int> f;
		while (eventos--) {
			sucesion_eventos(f);
		}
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
7
1 15 7 0 20 0 0

6
0 14 8 2 23 0

salida:
7 15 1

ECSA 8

*/