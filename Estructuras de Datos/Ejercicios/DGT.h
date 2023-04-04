
#ifndef DGT_h
#define DGT_h
#include <string>
#include <vector>
#include "hashmap_eda.h"
#include "queue_eda.h"
using namespace std;

using DNI = string;
using puntos = int;
using par = pair<DNI, int>;

class carnet_puntos : private unordered_map<DNI, puntos> {
	using info_puntos = std::pair<int, unordered_map<DNI, int>>; //clave-> n� de conductores que han tenido o tienen P puntos; 
																 //valor-> cada conductor con P puntos y orden en el que los han obtenido
	unordered_map<puntos, info_puntos> tablaP;

	//A: n� de conductores registrados
	//Pi: n� de conductores con i puntos

public :
	// la constructora llama a la constructora de la superclase

	//a�ade un nuevo conductor con 15 puntos; si ya existe, lanza excepci�n
	///las operaciones tienen coste constante
	void nuevo(DNI const& d) { // O(1)
		auto res = insert({ d, 15 });
		if (!res) {
			throw std::domain_error("Conductor duplicado");
		}
		else {
			tablaP[15].second[d] = tablaP[15].first;
			++tablaP[15].first;
		}
	}

	//a�ade P puntos al conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	void recuperar(DNI const& d, puntos const& p) { // O(log A)
		auto c = find(d);
		if (c == end())
			throw std::domain_error("Conductor inexistente");
		else {
			tablaP[c->valor].second.erase(d);
			c->valor = fmin(c->valor + p, 15);
			tablaP[c->valor].second[d] = tablaP[c->valor].first;
			++tablaP[c->valor].first;
		}
	}

	//quita P puntos al conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	void quitar(DNI const& d, puntos const& p) { // O(log A)
		auto c = find(d);
		if (c == end())
			throw std::domain_error("Conductor inexistente");
		else {
			tablaP[c->valor].second.erase(d);
			c->valor = fmax(c->valor - p, 0);
			tablaP[c->valor].second[d] = tablaP[c->valor].first;
			++tablaP[c->valor].first;
		}
	}

	//devuelve los puntos del conductor con dni D; si no existe el conductor, lanza excepci�n
	/// la operaci�n find() tiene coste logar�tmico en A y las dem�s operaciones tienen coste constante
	int consultar(DNI const& d) { //O(log A)
		auto c = find(d);
		if (c == end())
			throw std::domain_error("Conductor inexistente");
		else
			return c->valor;
	}

	//devuelve el n� de conductores con P puntos; lanza excepci�n si los puntos no est�n en su dominio
	/// las operaciones tienen coste constante 
	int cuantos_con_puntos(puntos const& p) { // O(1)
		if (p < 0 || p > 15)
			throw std::domain_error("Puntos no validos");
		else {
			return tablaP[p].second.size();
		}
	}

	//devuelve la lista de conductores que tienen P puntos; lanza excepci�n si los puntos no est�n en su dominio
	///realizamos un for con Pi iteraciones
	vector<par> lista_por_puntos(puntos const& p) { // O(Pi)
		if (p < 0 || p > 15)
			throw std::domain_error("Puntos no validos");
		else {
			vector<par> lista;
			for (auto it : tablaP[p].second) {
				lista.push_back({ it.clave, it.valor });
			}
			return lista;
		}
	}

};

#endif
