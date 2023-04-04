#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "treemap_eda.h"
#include "deque_eda.h"
using namespace std;

//funciones
map<string, deque<int>> referenciasTexto(int n);
void annadirRefsLinea(map<string, deque<int>>& m, string linea, int numL);
void tolower(string& s);
void print(map<string, deque<int>>& m);
void print(deque<int>& d);
 
bool resuelveCaso() {
	int n;
	string aux;
	cin >> n;

	if (n == 0) return false;
	getline(cin, aux);
	map<string, deque<int>> ref = referenciasTexto(n);
	print(ref);
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

map<string, deque<int>> referenciasTexto(int n) {
	map<string, deque<int>> m;
	string linea;

	for (int i = 1; i <= n; ++i) {
		getline(cin, linea);
		annadirRefsLinea(m, linea, i);
	}

	return m;
}

void annadirRefsLinea(map<string, deque<int>>& m, string linea, int numL) {
	stringstream ss(linea);
	string palabra;

	while (ss >> palabra) {
		if (palabra.length() > 2) { //solo se tienen en cuenta palabras con más de dos letras
			tolower(palabra); // no se tendran en cuenta las mayúsculas
			if (m.count(palabra)) {
				if (m[palabra].back() != numL) m[palabra].push_back(numL); //si la palabra no ha aparecido todavía en esa linea, se añade a la pila
			}
			else { //si la palabra no esta en el diccionario
				m.insert(palabra); //se añade la palabra
				m[palabra].push_back(numL); //se añade la línea en que aparece
			}
		}
	}
}

void print(map<string, deque<int>>& m) {
	auto it = m.begin();

	while (it != m.end()) {
		cout << it->clave;
		print(it->valor);
		cout << "\n";
		++it;
	}
	cout << "---\n";

}

void print(deque<int>& d) {
	int size = d.size();
	for (int i = 0; i < size; ++i) {
		cout << " " << d.front();
		d.pop_front();
	}
}

void tolower(string& s) {
	for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
}