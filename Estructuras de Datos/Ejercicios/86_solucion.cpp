#include <iostream>
#include <list>
#include "bintree_eda.h"
using namespace std;


void mostrar(vector<int> & v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << "\n";
}

vector<int> crearPerfil(int root, vector<int> & princ, vector<int> sec) {
	vector<int> perfil;
	perfil.push_back(root);
	perfil.insert(perfil.end(), princ.begin(), princ.end());
	if (!sec.empty()) {
		int n = sec.size() - princ.size();
		perfil.insert(perfil.end(), sec.end() - n, sec.end());
	}
	return perfil;
}

vector<int> perfilIzquierdo(bintree<int> & a) {
	if (a.empty())
		return vector<int>();
	else {
		bintree<int> iz = a.left(), dcho = a.right();
		vector<int> p_iz = perfilIzquierdo(iz);
		vector<int> p_d = perfilIzquierdo(dcho);

		if (iz.empty()) 
			return crearPerfil(a.root(), p_d, p_iz);
		else {
			if (p_iz.size() >= p_d.size())
				p_d.clear();
				
			return crearPerfil(a.root(), p_iz, p_d);			
		}
	}
}

bool resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	if (!std::cin) return false;

	vector<int> pIzq = perfilIzquierdo(arbol);
	mostrar(pIzq);
	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos--) {
		resuelveCaso();
	}
	system("pause");
	return 0;
}