#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "treemap_eda.h"
using namespace std;

//funciones
map<string, int> leerMapa();
vector<vector<string>> cambios(map<string, int>& m, map<string, int>& act);
void print(vector<vector<string>>& c);
string print_type(int i);
bool comp_empty(vector<vector<string>>& c);

bool resuelveCaso() {
	
	map<string, int> m = leerMapa();
	map<string, int> m_act = leerMapa();
	vector<vector<string>> c = cambios(m, m_act);
	print(c);
	return true;
}

int main() {
	string aux;
	int numCasos;
	cin >> numCasos;
	getline(cin, aux);
	while (numCasos != 0) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}

map<string, int> leerMapa() {
	map<string, int> m;
	string linea, clave;
	int valor;

	getline(cin, linea);
	stringstream ss(linea);
	while (ss >> clave) {
		m.insert(clave);
		ss >> valor;
		m[clave] = valor;
	}

	return m;
}

vector<vector<string>> cambios(map<string, int>& m, map<string, int>& act) { // 0-> si se añaden, 1-> si se eliminan, 2-> si se modifican
	vector<vector<string>> v(3);
	auto it_m = m.begin(), it_a = act.begin();
	
	while (it_m != m.end() || it_a != act.end()) {
		if (it_m != m.end() && it_a != act.end()) {
			if (it_m->clave == it_a->clave) { //si tienen la misma clave
				if (it_m->valor != it_a->valor) { //si tienen distinto valor, es que ha sido modificado
					v[2].push_back(it_m->clave);
					++it_m;
					++it_a;
				}
				else {
					++it_m;
					++it_a;
				}
			}
			else {
				if (m.count(it_a->clave)) { //si el mapa original contiene la clave del mapa actualizado, es que se ha eliminado la anterior
					v[1].push_back(it_m->clave);
					++it_m;
				}
				else {
					v[0].push_back(it_a->clave);
					++it_a;
				}
			}
		}
		else if (it_a == act.end()) {
			v[1].push_back(it_m->clave);
			++it_m;
		}
		else {
			v[0].push_back(it_a->clave);
			++it_a;
		}
	}

	

	return v;
}

void print(vector<vector<string>>& c) {
	if (comp_empty(c)) cout << "Sin cambios \n";
	else {
		for (int i = 0; i < c.size(); ++i) {
			if (!c[i].empty()) {
				cout << print_type(i);
				for (int j = 0; j < c[i].size(); ++j) {
					cout << c[i][j] << ' ';
				}
				cout << '\n';
			}
		}
	}
	cout << "---\n";
}

string print_type(int i) {
	return (i == 0) ? "+ " : (i == 1) ? "- " : "* ";
}

bool comp_empty(vector<vector<string>>& c) {
	return c[0].empty() && c[1].empty() && c[2].empty();
}