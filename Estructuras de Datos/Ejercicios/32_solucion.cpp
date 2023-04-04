#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "hashmap_eda.h"
#include "queue_eda.h"
using namespace std;

typedef struct {
	string deporte;
	int apuntados;
} tDeporte;

typedef struct {
	string d;
	bool apunt;
} tDatos;

//funciones
unordered_map<string, int> crearMapa();
void print(unordered_map<string, int>& m);
void print(vector<tDeporte>& v);
bool comp(tDeporte d1, tDeporte d2);

bool resuelveCaso() {
	unordered_map<string, int> dep = crearMapa();
	if (!std::cin) return false;
	print(dep);
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}


unordered_map<string, int> crearMapa() {
	unordered_map<string, int> deportes; // clave deporte, valor nº de alumnos apuntados
	unordered_map<string, tDatos> alumnos; // clave alumno, valor deporte al cual se ha apuntado
	string s, deporte_actual;

	cin >> s;
	if (!std::cin) return deportes;
	while (s != "_FIN_") {
		if (!islower(s[0])) { //si está en mayúsculas es deporte
			deportes[s];
			deporte_actual = s;
		}
		else { // es alumno
			if (!alumnos.count(s)) {//si no se ha apuntado en algun deporte 
				alumnos[s].d = deporte_actual;
				alumnos[s].apunt = true;
				++deportes[deporte_actual];
			}
			else if (deporte_actual != alumnos[s].d && alumnos[s].apunt) { // el alumno se había apuntado a algún deporte anterior
				--deportes[alumnos[s].d];
				alumnos[s].apunt = false;
			}
		}
		cin >> s;
	}
	return deportes;
}

void print(unordered_map<string, int>& m) {
	vector<tDeporte> v;
	for (auto it : m) v.push_back({ it.clave, it.valor });
	sort(v.begin(), v.end(), comp);
	print(v);
}

bool comp(tDeporte d1, tDeporte d2) {
	if (d1.apuntados > d2.apuntados) return true;
	else if (d1.apuntados < d2.apuntados) return false;
	else {
		if (d1.deporte < d2.deporte) return true;
		else return false;
	}
}

void print(vector<tDeporte>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i].deporte << " " << v[i].apuntados << "\n";
	}
	cout << "---\n";
}