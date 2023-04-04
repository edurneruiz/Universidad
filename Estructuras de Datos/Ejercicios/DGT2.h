#pragma once
#include <string>
#include <vector>
#include "hashmap_eda.h"
#include "list.h"

using namespace std;

using DNI = string;
using puntos = int;
using it = list<DNI>::iterator;
const int PUNTOS = 16;

class carnet_puntos {
	using c_info = pair<puntos, it>;

	unordered_map<DNI, c_info> conds; //clave->DNI del conductor, valor-> puntos quue tiene (first) e iterador a suposici�n en la lista(Second)
	vector<list<DNI>> pts; // vector que guarda en la posici�n i a todos los conductores que tienen i puntos

public:

	carnet_puntos() : pts(PUNTOS) {}

	//a�ade un nuevo conductor con 15 puntos; si ya existe, lanza excepci�n
	///las operaciones tienen coste constante
	void nuevo(DNI const& d) { // O(1)
		auto res = conds.insert({ d, {15, pts[15].begin()} }); // .end() devolver� null 
		if (!res) {
			throw std::domain_error("Conductor duplicado");
		}
		else {
			pts[15].push_back(d);
		}
	}
	
	//a�ade P puntos al conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	void recuperar(DNI const& d, puntos const& p) { // O(log A)
		auto c = conds.find(d);
		if (c == conds.end())
			throw std::domain_error("Conductor inexistente");
		else {
			pts[c->valor.first].erase(c->valor.second); //borramos al conductor de la lista de puntos P(ANTERIORES)
			c->valor.first = fmin(c->valor.first + p, 15); //actualizamos puntos
			pts[c->valor.first].push_back(d); //a�adimos al conductor a la lista de puntos P(ACTUALIZADOS)
		}
	}

	//quita P puntos al conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	void quitar(DNI const& d, puntos const& p) { // O(log A)
		auto c = conds.find(d);
		if (c == conds.end())
			throw std::domain_error("Conductor inexistente");
		else {
			pts[c->valor.first].erase(c->valor.second); //borramos al conductor de la lista de puntos P(ANTERIORES)
			c->valor.first = fmax(c->valor.first - p, 0); //actualizamos puntos
			pts[c->valor.first].push_back(d); //a�adimos al conductor a la lista de puntos P(ACTUALIZADOS)
		}
	}

	//devuelve los puntos del conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	int consultar(DNI const& d) { //O(log A)
		auto c = conds.find(d);
		if (c == conds.end())
			throw std::domain_error("Conductor inexistente");
		else
			return c->valor.first;
	}

	//devuelve el n� de conductores con P puntos; lanza excepci�n si los puntos no est�n en su dominio
	/// las operaciones tienen coste constante 
	int cuantos_con_puntos(puntos const& p) { // O(1)
		if (p < 0 || p > 15)
			throw std::domain_error("Puntos no validos");
		else {
			return pts[p].size();
		}
	}

	//devuelve la lista de conductores que tienen P puntos; lanza excepci�n si los puntos no est�n en su dominio
	///realizamos un for con Pi iteraciones
	vector<DNI> lista_por_puntos(puntos const& p) { // O(Pi)
		if (p < 0 || p > 15)
			throw std::domain_error("Puntos no validos");
		else {
			vector<DNI> lista;
			auto i = pts[p].begin();
			while (i != pts[p].end()) {
				lista.push_back(*i);
				++i;
			}
			return lista;
		}
	}

	
};