#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
#include "bintree_eda.h"
using namespace std;

//funciones
vector<int> rescate(bintree<int>& a);

bool resuelveCaso() {

	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	vector<int> r = rescate(arbol);
	cout << r[0] << " " << r[1] << "\n";
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

vector<int> rescate(bintree<int>& a) {

	if (a.empty()) return vector<int>(2, 0);
	else {
		vector<int> r(2, 0); //0-> nº grupos de rescate; 1-> mayor nº de excursionistas atrapados en misma ruta
		bintree<int> iz = a.left();
		bintree<int> dcha = a.right();
		vector<int> v_iz = rescate(iz), v_d = rescate(dcha);

		//si sus hijos no necesitan grupos de rescate y en esta intersección hay un grupo de alpinistas, necesitamos un grupo de rescate
		if (v_iz[0] == 0 & v_d[0] == 0 && a.root() != 0) r[0] = 1; 
		//si alguno de los hijos necesita grupo de rescate, entonces a esta intersección llegan la suma de los necesitados en cada hijo
		else r[0] = v_iz[0] + v_d[0];
		//determinar desde qué hijo llega un mayor nº de excursionistas y sumarles los que hay en esta intersección
		r[1] = (v_iz[1] > v_d[1]) ? v_iz[1] + a.root() : v_d[1] + a.root();

		return r;
	}
}