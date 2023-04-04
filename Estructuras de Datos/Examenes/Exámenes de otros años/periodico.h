#include <iostream>
#include <string>
#include <algorithm>
#include "hashmap_eda.h"
#include "set_eda.h"
#include "list_eda.h"
using namespace std;

using termino = string;
using tema = string;


class periodico {
	class noticia {
		set<termino> terms;
	public:
		set<termino> tomarPalabras() const {
			return terms;
		}

		bool esta(termino const& t) {
			return terms.count(t);
		}
	};

	using info_termino = unordered_map<termino, list<noticia>>;

	unordered_map<tema, list<noticia>> nxt; //noticias por tema
	unordered_map<tema, info_termino> tyt; //tema y terminos asociados a ese tema

public:

	// Añade una noticia sobre un cierto tema
	void nuevaNoticia(tema const& tem, noticia const& n) {
		nxt[tem].push_front(n);
		for (termino ter : n.tomarPalabras()) {
			tyt[tem][ter].push_front(n);
		}
	}

	//Obtiene las n últimas noticias dadas de alta en el sistema sobre un cierto tema
	vector<noticia> ultimasNoticias(tema const& t, int n) {
		vector<noticia> l;
		auto it = nxt[t].begin();

		while (n > 0 && it != nxt[t].end()) {
			l.push_back(*it);
			++it; --n;
		}

		return l;
	}

	//Obtiene las últimas n noticias de un tema en que aparece una cierta palabra
	vector<noticia> noticiasTermino(tema const& tem, termino const& ter, int n) {
		vector<noticia> l;
		auto it = tyt[tem][ter].begin();

		while (n > 0 && it != tyt[tem][ter].end()) {
			l.push_back(*it);
			++it; --n;
		}

		return l;
	}

	//Crea un nuevo término de búsqueda para un cierto tema.
	void nuevoTerminoBusqueda(tema const& tem, termino const& ter) {
		tyt[tem][ter];
	}

	// Elimina un término de búsqueda, pero no las noticias en las que aparece el término
	void eliminarTerminoBusqueda(termino const& ter) {
		auto it_tema = tyt.begin();

		while (it_tema != tyt.end()) {
			if (it_tema->valor.count(ter)) {
				it_tema->valor.erase(ter);
			}
			++it_tema;
		}
	}

	//Obtiene una lista ordenada alfabéticamente con todos los términos definidos para un cierto tem
	vector<termino> listarTerminos(tema const& tem) {
		vector<termino> v;
		for (auto it : tyt[tem]) {
			v.push_back(it.clave);
		}
		return v;
	}

};
