#include <iostream>
#include <vector>
#include "treemap_eda.h"
#include "queue_eda.h"
using namespace std;

typedef struct {
	string pelicula;
	int emisiones;
} tPelicula;

typedef struct {
	string actor;
	int mins;
} tActor;

//funciones
map<string, map<string, int>> crearMapa(int nPelis);
void emisiones(int mEmisiones, map<string, map<string, int>>& m);
tPelicula peliculaMasEmitida(map<string, int>& peliculas, stack<string>& p);
pair<int, queue<string>> actoresPreferidos(map<string, int>& actores);
void printDatos(tPelicula p, pair<int, queue<string>>& a);
bool resuelveCaso();

int main() {
	while (resuelveCaso()) {}
	return 0;
}

bool resuelveCaso() {
	int nPelis, mEmisiones;
	cin >> nPelis;
	if (nPelis == 0) return false;

	map<string, map<string, int>> peliculas = crearMapa(nPelis);
	cin >> mEmisiones;
	emisiones(mEmisiones, peliculas);
	return true;
}

map<string, map<string, int>> crearMapa(int nPelis) {
	map<string, map<string, int>> m; // clave-> nombre pelicula, valor-> mapa que recoge los actores que aparecen y sus minutos correspondientes
	int nActores, mins;
	string peli, actor;

	for (int i = 0; i < nPelis; ++i) {
		cin >> peli >> nActores;
		m[peli]; //añadimos peli
		for (int j = 0; j < nActores; ++j) {
			cin >> actor >> mins;
			m[peli].insert(actor); //añadimos el actor
			m[peli][actor] = mins; //añadimos los minutos correspondientes de ese actor en esa película
		}
	}
	return m;
}

void emisiones(int mEmisiones, map<string, map<string, int>>& m) {
	map<string, int> peliculas; //clave nombre pelicula, valor veces emitida
	map<string, int> actores; //clave nombre actor, valor minutos que aparece
	stack<string> p;
	string peli;

	for (int i = 0; i < mEmisiones; ++i) {
		cin >> peli;
		++peliculas[peli]; //sumamos una repeticion más de dicha película
		p.push(peli); //añadimos la película a la pila
		for (auto it : m[peli]) {
			actores[it.clave] += it.valor; //sumamos a cada actor los minutos que ha aparecido en esa película a sus minutos totales en tv
		}
	}

	tPelicula masEmitida = peliculaMasEmitida(peliculas, p);
	pair<int, queue<string>> as = actoresPreferidos(actores);
	printDatos(masEmitida, as);
}

void printDatos(tPelicula p, pair<int, queue<string>>& a) {
	cout << p.emisiones << " " << p.pelicula << "\n";
	cout << a.first;
	while (!a.second.empty()) {
		cout << " " << a.second.front();
		a.second.pop();
	}
	cout << "\n";
}

tPelicula peliculaMasEmitida(map<string, int>& peliculas, stack<string>& p) {
	vector<tPelicula> pelis;
	for (auto it : peliculas) {
		pelis.push_back({ it.clave, it.valor }); 
	}
	//ordenamos las películas según las veces que se han emitido
	sort(pelis.begin(), pelis.end(), [](tPelicula p1, tPelicula p2) { return (p1.emisiones > p2.emisiones); });

	while (!p.empty()) { 
		if (peliculas[p.top()] == pelis[0].emisiones) //si la ultima película es tb la más emitida, es la que estamos buscando
			return { p.top(), peliculas[p.top()] };
		else p.pop();
	}
}

pair<int, queue<string>> actoresPreferidos(map<string, int>& actores) {
	vector<tActor> act;
	queue<string> a;
	for (auto it : actores) {
		act.push_back({ it.clave, it.valor });
	}
	//ordenamos a los actores según los minutos en antena (de mayor a menor)
	sort(act.begin(), act.end(), [](tActor a1, tActor a2) { return (a1.mins > a2.mins) || ((a1.mins == a2.mins) && (a1.actor < a2.actor)); });

	int i = 0, max_mins = act[0].mins;
	while (act[i].mins == max_mins) { //buscamos todos los actores que hayan estado en antena el máximo de minutos
		a.push(act[i].actor);
		++i;
	}
	return pair<int, queue<string>>(max_mins, a);
}