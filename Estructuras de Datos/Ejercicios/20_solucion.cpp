#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
#include "bintree_eda.h"
using namespace std;

//funciones
void calcularFrontera(bintree<int>& a, vector<int>& f);
void print(vector<int> f);


bool resuelveCaso() {
	
	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	vector<int> frontera;
	calcularFrontera(arbol, frontera);
	print(frontera);

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

void calcularFrontera(bintree<int>& a, vector<int>& f) {
	if (!a.empty()) {
		bintree<int> iz = a.left();
		bintree<int> dcha = a.right();

		if (iz.empty() && dcha.empty()) f.push_back(a.root());
		else {
			calcularFrontera(iz, f);
			calcularFrontera(dcha, f);
		}
	}
}

void print(vector<int> f) {
	for (int i = 0; i < f.size(); ++i) {
		cout << f[i] << ' ';
	}
	cout << '\n';
}