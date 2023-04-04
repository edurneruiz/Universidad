#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
#include "bintree_eda.h"
using namespace std;

//funciones
vector<int> datosArbol(bintree<char>& a); //0-> nodos, 1-> hojas, 2->altura
void print(vector<int> f);

bool resuelveCaso() {
	int n = 0, h = 0, alt = 0;

	if (!std::cin) return false;
	bintree<char> arbol = leerArbol('.');
	vector<int> d = datosArbol(arbol);
	print(d);

	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos != 0) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}


vector<int> datosArbol(bintree<char>& a) {//0-> nodos, 1-> hojas, 2->altura
	
	if (a.empty()) return vector<int>(3, 0);
	else {
		bintree<char> iz = a.left();
		bintree<char> d = a.right();
		if (iz.empty() && d.empty()) return vector<int>(3, 1);
		else {
			vector<int> izq = datosArbol(iz);
			vector<int> dcha = datosArbol(d);
			vector<int> datos(3);
			datos[0] = izq[0] + dcha[0] + 1; //el numero de nodos del árbol es la suma de el nº a su izq y el nº a su dcha, además de la raíz
			datos[1] = izq[1] + dcha[1]; //el numero de hojas del árbol es la suma del nº a su izq y el nº a su dcha
			datos[2] = (izq[2] > dcha[2]) ? izq[2] + 1 : dcha[2] + 1;
			return datos;
		}
	}
}

void print(vector<int> f) {
	for (int i = 0; i < f.size(); ++i) {
		cout << f[i] << ' ';
	}
	cout << '\n';
}