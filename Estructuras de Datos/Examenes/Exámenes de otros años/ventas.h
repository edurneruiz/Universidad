#include <iostream>
#include <string>
#include "hashmap_eda.h"
#include "treemap_eda.h"
#include <list>
using namespace std;



class ventas {
	using cliente = string;
	using producto = string;
	using iterador = typename list<cliente>::iterator;
	using info_cliente = unordered_map<producto, iterador>; 

	typedef struct {
		list<cliente> espera;
		int unidades;
		int vendidos;
	} info_producto;

	map<producto, info_producto> productos;
	unordered_map<cliente, info_cliente> clientes;

public:

	//constructora vacía
	ventas() {}

	//Crea una nueva oferta para el producto P con N unidades disponibles
	void annadir_oferta(producto const& p, int n) {
		if (n <= 0)
			throw domain_error("El numero de unidades disponibles debe ser positivo");
		else {
			auto itP = productos.find(p);
			if (itP != productos.end())
				throw domain_error("Al producto " + p + " ya se le aplica oferta");
			else
				productos[p] = { list<cliente>(), n,0};
		}
	}

	// Añade al cliente C a la lista de espera para la compra del producto P
	void poner_en_espera(cliente const&c, producto const& p) {
		auto itP = productos.find(p);
		if (itP == productos.end())
			throw domain_error("Dicho producto no existe");
		else {
			auto itC = clientes.find(c);
			if (itC != clientes.end()) { //ya existe el cliente
				auto itCP = clientes[c].find(p);
				if (itCP == clientes[c].end()) {//el cliente no esta esperando a comprar dicho producto
					productos[p].espera.push_front(c);
					clientes[c][p] = productos[p].espera.begin();
				}
			}
			else { //no existe el cliente
				productos[p].espera.push_front(c);
				clientes[c][p] = productos[p].espera.begin();
			}
		}
	}

	//Elimina al cliente C de la lista de espera del producto P
	void cancelar_espera(cliente const& c, producto const& p) {
		auto itP = productos.find(p);
		if (itP == productos.end())
			throw domain_error("Dicho producto no existe");
		else {
			auto itC = clientes.find(c);
			if (itC != clientes.end()) {
				auto itCP = clientes[c].find(p);
				if (itCP != clientes[c].end()) { //está esperando ese producto
					productos[p].espera.erase(itCP->valor);
					clientes[c].erase(p);
				}
				if (clientes[c].empty()) clientes.erase(c);
			}
		}
	}

	//Devuelve el número de clientes que están esperando para comprar el producto P
	int num_en_espera(producto const& p) {
		auto itP = productos.find(p);
		if (itP == productos.end())
			throw domain_error("Dicho producto no existe");
		else
			return productos[p].espera.size();
	}

	//Registra una venta de num_unidades unidades del producto P al primer cliente de la lista de espera
	void vender(producto const& p, int num_unidades) {
		auto itP = productos.find(p);
		if (itP == productos.end())
			throw domain_error("Dicho producto no existe");
		else {
			if (productos[p].espera.empty())
				throw domain_error("No hay lista de espera para el producto " + p);
			if (productos[p].unidades < num_unidades)
				throw domain_error("el número de unidades solicitado sobrepasa el número de unidades disponibles");

			productos[p].unidades -= num_unidades;
			productos[p].vendidos += num_unidades;
			auto c = productos[p].espera.back();
			productos[p].espera.pop_back(); //lo eliminamos de la lista de espera
			clientes[c].erase(p);

			if (clientes[c].empty()) clientes.erase(c);
			if (productos[p].unidades == 0) productos[p].espera.clear();
		}
	}

	//Devuelve el nombre del primer cliente que está esperando para comprar el producto P
	cliente primero_en_espera(producto const& p) {
		auto itP = productos.find(p);
		if (itP == productos.end())
			throw domain_error("Dicho producto no existe");
		else {
			if (productos[p].espera.empty())
				throw domain_error("No hay lista de espera para el producto " + p);

			return productos[p].espera.back();
		}
	}

	vector<pair<producto, int>> lista_ventas() {
		vector<pair<producto, int>> lista;
		for (auto it : productos) {
			lista.push_back({ it.clave, it.valor.vendidos });
		}
		return lista;
	}
	
};
