#include <iostream>
#include "treemap_eda.h"
using namespace std;

typedef struct {
	int linea;
	string instruccion;
	int* sig_linea;
} tLinea;

void renum(map<int, tLinea>& m) { //el tamaño es lineal respecto al número de líneas
	int i = 1;
	for (auto it : m) {
		m[it.clave].linea = i*10;
		++i;
	}
}

void print(map<int, tLinea>& m) {
	for (auto it : m) {
		cout << m[it.clave].linea << " " << m[it.clave].instruccion << " ";
		if (m[it.clave].sig_linea != nullptr) cout << *m[it.clave].sig_linea << "\n";
		else cout << "\n";
	}
	cout << "---\n";
}

bool resuelveCaso() {
	int linea, sig;
	map<int, tLinea> codigo;

	cin >> linea;
	while (linea != 0) { //el código acaba con un 0
		codigo[linea].linea = linea;
		cin >> codigo[linea].instruccion; //asociamos a dicha linea la instrucción
		if (codigo[linea].instruccion != "RETURN") {
			cin >> sig;
			codigo[sig].linea = sig; //añadimos nueva línea
			codigo[linea].sig_linea = &codigo[sig].linea; //la siguiente linea a la que estamos tratando es la que acabamos de añadir
		}
		else codigo[linea].sig_linea = nullptr; //si es RETURN no salta a otra instrucción
		cin >> linea;
	}

	renum(codigo);
	print(codigo);
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