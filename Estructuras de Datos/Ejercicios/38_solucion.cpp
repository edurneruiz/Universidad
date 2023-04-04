#include <iostream>
#include <vector>
#include <string>
#include "iPud.h"
using namespace std;


void mostrar(vector<string> & v) {
	if (v.empty())
		cout << "No hay canciones recientes \n";
	else 
		cout << "Las " + to_string(v.size()) + " mas recientes \n";

	for (int i = 0; i < v.size(); ++i) {
		cout << "   " << v[i] << "\n";
	}
}

bool resuelveCaso() {
	string orden;

	cin >> orden;
	if (!std::cin) return false;

	iPud i;
	string cancion, artista;
	int duracion;
	while (orden != "FIN") {
		try {
			if (orden == "addSong") {
				cin >> cancion >> artista >> duracion;
				i.addSong(cancion, artista, duracion);
			}
			else if (orden == "addToPlaylist") {
				cin >> cancion;
				i.addToPlayList(cancion);
			}
			else if (orden == "current") {
				cancion = i.current();
			}
			else if (orden == "play") {
				cancion = i.play();
				cout << "Sonando " + cancion << "\n";
			}
			else if (orden == "totalTime") {
				duracion = i.totalTime();
				cout << "Tiempo total " + to_string(duracion) << "\n";
			}
			else if (orden == "recent") {
				cin >> duracion;
				vector<string> v = i.recent(duracion);
				mostrar(v);
			}
			else if (orden == "deleteSong") {
				cin >> cancion;
				i.deleteSong(cancion);
			}
		}
		catch (domain_error e) {
			std::cout << e.what() << '\n';
		}
		cin >> orden;
	}
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}