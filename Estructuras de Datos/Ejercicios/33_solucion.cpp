#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "treemap_eda.h"
#include "queue_eda.h"
using namespace std;

typedef struct {
	string nombre;
	int problemas_correctos;
	int tiempo_total;
} tEquipo;

typedef struct {
	int pc; //nº de problemas correctos
	int tt; //tiempo total de resolución de problemas correctos
} tDatosEquipo;

typedef struct {
	bool resuelto;
	int intentos;
	int tiempo;
} tDatosProblema;


//funciones
map<string, tDatosEquipo> crearMapa();
void print(map<string, tDatosEquipo>& r);
void print(vector<tEquipo>& v);
bool tratarProblema(string eq, string pr, string res, int t, map<string, tDatosProblema>& problemas);
bool myfunction(tEquipo e1, tEquipo e2);


bool resuelveCaso() {
	string aux;
	getline(cin, aux);

	map<string, tDatosEquipo> ranking = crearMapa();
	print(ranking);
	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos!=0){
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}


map<string, tDatosEquipo> crearMapa() {
	map<string, tDatosEquipo> ranking; //equipos 
	map<string, map<string, tDatosProblema>> eq_pr; //problemas intentados por cada equipo
	string equipo, problema, resultado;
	int t;

	cin >> equipo;
	while (equipo != "FIN") {
		cin >> problema >> t >> resultado;
		if (!ranking.count(equipo)) { //el equipo no pertenece al ranking
			ranking.insert(equipo); //añado el equipo 
			eq_pr.insert(equipo);
			eq_pr[equipo].insert(problema); //añado el problema
		}
		else { //el equipo ya está en el ránking
			if (!eq_pr[equipo].count(problema)) { //se trata de un problema que el equipo no ha intentado resolver anteriormente
				eq_pr[equipo].insert(problema);
			}
		}
		if (tratarProblema(equipo, problema, resultado, t, eq_pr[equipo])) {
			if (eq_pr[equipo][problema].resuelto) {
				++ranking[equipo].pc;
				ranking[equipo].tt += eq_pr[equipo][problema].tiempo;
			}
		}
		cin >> equipo;
	}

	return ranking;
}

//devuelve true si lo trata, false si ya estaba resuelto anteriormente
bool tratarProblema(string eq, string pr, string res, int t, map<string, tDatosProblema>& problemas) {
	if (!problemas[pr].resuelto) { //si ya esta bien se ignora
		if (res == "AC") {
			problemas[pr].resuelto = true;
			problemas[pr].tiempo = t + problemas[pr].intentos * 20;
		}
		else {
			problemas[pr].resuelto = false;
			++problemas[pr].intentos;
		}
		return true;
	}
	return false;
}

void print(map<string, tDatosEquipo>& r) {
	vector<tEquipo> v;
	auto it = r.begin();

	while (it != r.end()) {
		v.push_back({ it->clave, it->valor.pc, it->valor.tt });
		++it;
	}
	sort(v.begin(), v.end(), myfunction);
	print(v);
}

void print(vector<tEquipo>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i].nombre << " " << v[i].problemas_correctos << " " << v[i].tiempo_total << "\n";
	}
	cout << "---\n";
}

bool myfunction(tEquipo e1, tEquipo e2) {
	if (e1.problemas_correctos > e2.problemas_correctos) return true;
	else if (e1.problemas_correctos < e2.problemas_correctos) return false;
	else {
		if (e1.tiempo_total < e2.tiempo_total) return true;
		else if (e1.tiempo_total > e2.tiempo_total) return false;
		else {
			if (e1.nombre < e2.nombre) return true;
			else return false;
		}
	}
}
