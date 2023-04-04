#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "bintree_eda.h"
using namespace std;

//funciones
bintree<int> crearArbol(vector<int>& v);
vector<int> leerVector();
vector<vector<int>> hijos(vector<int>& v);
void print(vector<int>& v);

bool resuelveCaso() {

	if (!std::cin) return false;
	vector<int> preorden = leerVector();
	bintree<int> arbol = crearArbol(preorden);
	vector<int> postorden = arbol.postorder();
	print(postorden);

	return true;
}

int main() {
	while (resuelveCaso()){}
	system("pause");
	return 0;
}

bintree<int> crearArbol(vector<int>& v) {

	if (v.empty()) return bintree<int>(); //si el vector en preorden es vacío, se trata de un arbol vacío
	else {
		vector<vector<int>> h = hijos(v);
		bintree<int> izq = crearArbol(h[0]); 
		bintree<int> dcho = crearArbol(h[1]);

		bintree<int> a(izq, v[0], dcho); //crea árbol con raíz el primer elemento del vector, hijos izq y dcho los calculados

		return a;
	}
}

vector<int> leerVector() {
	vector<int> v;
	string linea;
	int x;

	getline(cin, linea);
	stringstream ss(linea);
	while (ss >> x) {
		v.push_back(x);
	}

	return v;
}

vector<vector<int>> hijos(vector<int>& v) { // 0-> vector con los nodos del hijo izq, 1-> vector con los nodos del hijo dcho

	if (v.size() == 1) return vector<vector<int>>(2, vector<int>()); //si es árbol hoja, sus hijos son los arboles vacíos
	else {
		vector<vector<int>> hijos(2);
		int i = 1;
		while (i < v.size() && v[i] < v[0]) { //mientras los nodos siguientes sean menores a la raíz, se trata del hijo izq
			hijos[0].push_back(v[i]);
			++i;
		}
		while (i < v.size()) { //los demás nodos que quedan guardados en el vector pertenecen al hijo derecho
			hijos[1].push_back(v[i]);
			++i;
		}
		return hijos;
	}
}

void print(vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << '\n';
}