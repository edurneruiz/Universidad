#include <iostream>
#include <string>
#include "fecha.h"
#include "list_eda.h"
#include "hashmap_eda.h"
#include "treemap_eda.h"
using namespace std;

class almacen {
	using producto = string;
	using cliente = string;

	typedef struct {
		map<fecha, int> fp;
		list<cliente> espera; //lista de espera de los clientes que han pedido el producto y aún no lo tienen
		int stock; //nº de unidades de ese producto que hay en almacén
	} info_prod;

	unordered_map<producto, info_prod> productos;

public:

	//constructora vacía
	almacen() : productos() {}

	vector<cliente> adquirir(producto const& pr, fecha const& f, int const& n) {
		auto itP = productos.find(pr);
		if (itP == productos.end()) {
			map<fecha, int> fp; fp.insert({ f,n });
			productos[pr] = { fp , list<cliente>(), n };
			return vector<cliente>();
		}
		else {
			itP->valor.fp[f] += n;
			itP->valor.stock += n;
			if (itP->valor.espera.empty()) {
				return vector<cliente>();
			}
			else {
				vector<cliente> l = listaDeEspera(itP->valor, n);
				return l;
			}
		}
	}

	pair<bool, fecha> vender(producto const& pr, cliente const& cli) {
		auto itP = productos.find(pr);
		if (itP != productos.end()) {
			if (itP->valor.stock > 0) { //hay existencias
				auto itF = itP->valor.fp.begin();
				itF->valor -= 1;
				itP->valor.stock -= 1;
				fecha f = itF->clave;
				if (itF->valor == 0)
					itP->valor.fp.erase(itF->clave);
				return { true, f };
			}
			else {
				itP->valor.espera.push_back(cli);
				return { false, fecha() };
			}
		}
		else {
			list<cliente> l; l.push_back(cli);
			productos[pr] = { map<fecha, int>() , l, 0 };
			return { false, fecha() };
		}
	}

	int cuantos(producto const& pr) {
		auto itP = productos.find(pr);
		if (itP != productos.end())
			return itP->valor.stock;
		else
			return 0;
	}

	bool hay_esperando(producto const& pr) {
		auto itP = productos.find(pr);
		if (itP != productos.end())
			return !itP->valor.espera.empty();
		else
			return false;
	}

private: 
	
	//devuelve la lista de clientes que adquieren el producto
	vector<cliente> listaDeEspera(info_prod & i, int n) {
		vector<cliente> lista;
		auto itF = i.fp.begin();
		while (n > 0 && !i.espera.empty() && itF != i.fp.end()) {
			lista.push_back(i.espera.front());
			i.espera.pop_front();
			--n; --i.stock; --itF->valor;
			if (itF->valor == 0) {
				auto dlt = itF;
				i.fp.erase(dlt->valor);
				++itF;
			}
		}
		return lista;
	}
};
