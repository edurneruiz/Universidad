#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
#include "bintree_eda.h"
using namespace std;

//funciones
vector<int> diametro(bintree<char>& a);

bool resuelveCaso() {

	if (!std::cin) return false;
	bintree<char> arbol = leerArbol('.');
	vector<int> a = diametro(arbol);
	cout << a[1] << '\n';

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

//vector; 0-> alt, 1->diam 
vector<int> diametro(bintree<char>& a) {
	if (a.empty()) return vector<int>(4, 0);
	else {
		vector<int> datos(4);
		bintree<char> iz = a.left();
		bintree<char> dcha = a.right();
		vector<int> v_iz = diametro(iz), v_d = diametro(dcha);

		datos[0] = (v_iz[0] > v_d[0]) ? v_iz[0] + 1 : v_d[0] + 1;
		
		int d = v_iz[0] + v_d[0] + 1;
		if (v_iz[1] > v_d[1]) {
			if (d > v_iz[1]) datos[1] = d;
			else datos[1] = v_iz[1];
		}
		else {
			if (d > v_d[1]) datos[1] = d;
			else datos[1] = v_d[1];
		}

		return datos;
	}
}
