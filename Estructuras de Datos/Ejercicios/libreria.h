#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "hashmap_eda.h"
#include "treemap_eda.h"
using namespace std;

using libro = string;

class libreria {
	using iterator = typename list<libro>::iterator;

	typedef struct {
		int disponibles; //cuantos ejemplares de ese libro hay disponibles 
		int vendidos; // cuantos ejemplares de ese libro han sido vendidos
		iterator it; // iterador a su puesto en la lista de x vendidos
	} info_libro;
	
	unordered_map<libro, info_libro> lib;
	map<int, list<libro>, std::greater<int>> ventas; // en la clave i hay guardada una lista con los libros que han sido vendidos i veces,
												     // ordenados de más reciente a más antiguo

public:

	// Añade n nuevos ejemplares del libro L
	void nuevoLibro(int n, libro const& l) {
		auto itL = lib.find(l);
		if (itL == lib.end()) { // si el libro no está en el sistema
			ventas[0].push_front(l); //lo añadimos a la lista de libros no vendidos 
			lib[l] = { n, 0, ventas[0].begin() };
		}
		else 
			lib[l].disponibles += n;
	}

	//Comprar el libro L
	void comprar(libro const& l) {
		auto itL = lib.find(l);
		if (itL == lib.end()) // si el libro no está en el sistema
			throw invalid_argument("Libro no existente");
		else {
			if (itL->valor.disponibles == 0)
				throw out_of_range("No hay ejemplares");
			else {
				auto & ll = lib[l];

				ventas[ll.vendidos].erase(ll.it); //borramos el libro de su lista de venta anterior
				--ll.disponibles;
				++ll.vendidos;
				ventas[ll.vendidos].push_front(l); //lo añadimos a su nueva lista de venta
				ll.it = ventas[ll.vendidos].begin(); //le asignamos el iterador correspondiente
			}
		}
	}

	//Indica si un libro L está en el sistema
	bool estaLibro(libro const& l) {
		return lib.count(l);
	}

	//Elimina del sistema todo rastro del libro L. Si el libro no existe la operación no tiene efecto.
	void elimLibro(libro const& l) {
		auto itL = lib.find(l);
		if (itL != lib.end()) { //el libro está en el sistema
			auto ll = itL->valor;
			ventas[ll.vendidos].erase(ll.it);
			lib.erase(l);
		}
	}

	//Devuelve el número de ejemplares de un libro L que hay disponibles en el sistema
	int numEjemplares(libro const& l) {
		auto itL = lib.find(l);
		if (itL == lib.end()) // si el libro no está en el sistema
			throw invalid_argument("Libro no existente");
		else
			return itL->valor.disponibles;
	}

	//Obtiene una lista con los 10 libros más vendidos, ordenada por nº ventas y más reciente
	vector<libro> top10() {
		vector<libro> top10;
		int annadidos = 0;

		auto i = ventas.begin();
		auto itL = i->valor.begin();

		while (i != ventas.end() && annadidos < 10 && i->clave > 0) {
			if (itL == i->valor.end()) {
				++i;
				itL = i->valor.begin();
			}
			else {
				top10.push_back(*itL);
				++itL;
				++annadidos;
			}
		}

		return top10;
	}

};
