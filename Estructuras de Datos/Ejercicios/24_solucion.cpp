#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
#include "bintree_eda.h"
using namespace std;

void mostrar(vector<int> & v) {
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << '\n';
}

vector<int> leer() {
	vector<int> v;
	string linea;
	int coord;

	getline(cin, linea);
	stringstream ss(linea);
	while (ss >> coord) {
		v.push_back(coord);
	}

	return v;
}


bintree<int> arbol(vector<int> & pre, vector<int> & in, int & p, int & i, int tope) {
	if (p == pre.size() || in[i] == tope)
		return {};
	else {
		int raiz = pre[p];
		bintree<int> iz = arbol(pre, in, ++p, i, raiz);
		bintree<int> dr = arbol(pre, in, p, ++i, tope);

		return { iz, raiz, dr };
	}
}

bool resuelveCaso() {
	vector<int> preorden = leer();
	vector<int> inorden = leer();
	if (!std::cin) return false;
	
	int p = 0, i = 0;
	bintree<int> a = arbol(preorden, inorden, p, i, -1);
	vector<int> postorden = a.postorder();
	mostrar(postorden);

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

