#include <iostream>
#include <string>
#include <vector>
#include "hashmap_eda.h"
#include "list_eda.h"
using namespace std;

using song = string;
using artist = string;
using duration = int;

class iPud {
	using iterator = typename list<song>::iterator;

	typedef struct {
		artist a; //artista que la canta
		duration d; //duracion de la canci�n 
		pair<iterator, iterator> its; //iteradores a la cancion en la lista de reproduccion y la lista de reproducidas
	} info_song;

	unordered_map<song, info_song> canciones; //clave -> titulo cancion, valor -> artista y duracion de la cancion

	pair<duration, list<song>> lista_reproduccion; // first -> duracion total playlist, second -> canciones de la playlist
	list<song> reproducidas;
	pair<iterator, iterator> iteradores; // iteradores al ultimo elemento de cada lista, 
										 // first -> lista_reproduccion, second -> reproducidas

public:

	void addSong(song const& s, artist const& a, duration const& d) {
		auto itS = canciones.find(s);
		if (itS != canciones.end())
			throw domain_error("ERROR addSong");
		else
			canciones[s] = { a, d, { lista_reproduccion.second.end(), reproducidas.end() } };
	}

	void addToPlayList(song const& s) {
		auto itS = canciones.find(s);
		if (itS == canciones.end())
			throw domain_error("ERROR addToPlayList");
		else {
			if (canciones[s].its.first == lista_reproduccion.second.end()) { //si la canci�n NO esta en la lista de reproduccion
				bool empty = lista_reproduccion.second.empty();

				lista_reproduccion.second.push_back(s); //a�adimos a la lista
				if (empty)
					iteradores.first = lista_reproduccion.second.begin();
				else
					++iteradores.first;

				lista_reproduccion.first += canciones[s].d; //a�adimos su duraci�n a la duraci�n total
				canciones[s].its.first = iteradores.first;
			}
		}
	}

	song current() {
		if (lista_reproduccion.second.empty())
			throw domain_error("ERROR current");

		return lista_reproduccion.second.front();
	}

	song play() {
		if (!lista_reproduccion.second.empty()) {
			auto s = current();
			auto & ss = canciones[s];

			eraseSongOfPlaylist(ss);
			actualizarReproducidas(s, ss);

			return s;
		}
		else
			throw domain_error("No hay canciones en la lista");
	}

	int totalTime() {
		return lista_reproduccion.first;
	}

	vector<song> recent(int n) {
		list<song> l(reproducidas);
		int size = l.size();

		vector<song> v;

		while (!l.empty() && size > size - n) {
			v.push_back(l.back());
			l.pop_back();
			++n;
		}
		
		return v;
	}

	void deleteSong(song const& s) {
		auto itS = canciones.find(s);
		if (itS != canciones.end()) { //la cancion existe
			auto & ss = canciones[s];
			if (ss.its.first != lista_reproduccion.second.end()) { //est� en la lista de reproducci�n
				lista_reproduccion.second.erase(ss.its.first);
				lista_reproduccion.first -= ss.d;
			}
			if (ss.its.second != reproducidas.end()) { // esta en la lista de reproducidas
				reproducidas.erase(ss.its.second);
			}
			canciones.erase(s);
		}
	}

private:

	void eraseSongOfPlaylist(info_song & ss) {
		if (ss.its.first != lista_reproduccion.second.end()) { //si pertenece a la playlist
			if (ss.its.first == iteradores.first) { //si es la m�s reciente
				lista_reproduccion.second.erase(ss.its.first); ///la borramos de la �ltima posici�n 

				if (lista_reproduccion.second.empty())
					iteradores.first = lista_reproduccion.second.end();
				else {
					song ant = lista_reproduccion.second.back();
					iteradores.first = canciones[ant].its.first;
				}
			}
			else lista_reproduccion.second.erase(ss.its.first); ///la borramos de la posici�n donde est�

			lista_reproduccion.first -= ss.d; ///restamos su duracion de la duracion total de la playlist
			ss.its.first = lista_reproduccion.second.end();
		}
	}

	void actualizarReproducidas(song const& s, info_song & ss) {
		bool empty = reproducidas.empty();

		if (ss.its.second != reproducidas.end()) { // si ha sido ya reproducida
			if (ss.its.second == iteradores.second) { //si es la m�s reciente
				reproducidas.erase(ss.its.second); ///la borramos de la �ltima posici�n 

				if (reproducidas.empty())
					iteradores.second = reproducidas.end();
				else {
					song ant = reproducidas.back();
					iteradores.second = canciones[ant].its.second;
				}
			}
			else 
				reproducidas.erase(ss.its.second); ///la borramos de la posici�n donde est�
		}
		reproducidas.push_back(s); ///la volvemos a a�adir al final

		if (empty)
			iteradores.second = reproducidas.begin();
		else
			++iteradores.second;
		ss.its.second = iteradores.second;
	}
};
